/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "psscloud.h"

#include "../sdk/service/user.h"
#include "pssresponses.h"
#include "http.h"
#include <string>
#include <optional>
#include <unordered_map>
#include <string_view>
#include <sstream>

static HttpServer g_psscloud_server("127.0.0.1", PSSCLOUD_SERVER_PORT);

static std::optional<std::string> get_response_string(const std::string_view uri) {
	if (uri.find("config/v1/ns/") == 0 && uri.rfind("/config/main:data") != std::string_view::npos) {
		return PSSCLOUD_RESPONSE_CONFIG_MAIN_DATA;
	}
	size_t pos = uri.find("accounts/v1/ns/");
	if (pos == 0) {
		size_t colon = uri.find(':', pos + 15);
		std::string_view product_id = uri.substr(pos + 15, colon - pos - 15);
		std::string_view action = uri.substr(colon + 1);
		if (action == "auth") {
			std::ostringstream ss;
			ss << PSSCLOUD_RESPONSE_AUTH_PART1;
			ss << product_id;
			ss << PSSCLOUD_RESPONSE_AUTH_PART2;
			return ss.str();
		} else if (action == "registrationProduct") {
			std::ostringstream ss;
			ss << PSSCLOUD_RESPONSE_REGISTRATION_PRODUCT_PART1;
			ss << product_id;
			ss << PSSCLOUD_RESPONSE_REGISTRATION_PRODUCT_PART2;
			return ss.str();
		} else if (action == "registeredAccount") {
			// Use the custom account ID instead of the default one
			auto account = get_fake_account(0); // Get the first account
			uint64_t accountId = account ? account->account_id : DEFAULT_FAKE_ACCOUNT_ID;
			
			std::ostringstream ss;
			ss << PSSCLOUD_RESPONSE_REGISTERED_ACCOUNT_PART1;
			ss << accountId;
			ss << PSSCLOUD_RESPONSE_REGISTERED_ACCOUNT_PART2;
			return ss.str();
		} else if (action == "newRegistrationURL") {
			std::ostringstream ss;
			ss << PSSCLOUD_RESPONSE_NEW_REGISTRATION_URL_PART1;
			ss << product_id;
			ss << PSSCLOUD_RESPONSE_NEW_REGISTRATION_URL_PART2;
			return ss.str();
		} else if (action == "link") {
			// Use the custom account ID instead of the default one
			auto account = get_fake_account(0); // Get the first account
			uint64_t accountId = account ? account->account_id : DEFAULT_FAKE_ACCOUNT_ID;
			
			std::ostringstream ss;
			ss << PSSCLOUD_RESPONSE_LINK_PART1;
			ss << accountId;
			ss << PSSCLOUD_RESPONSE_LINK_PART2;
			return ss.str();
		}
	}
	return std::nullopt;
}

static void psscloud_request_handler(const std::string& method, const std::string& uri, const std::unordered_map<std::string, std::string>& headers, const std::string& body, HttpResponse& response) {
	std::optional<std::string> responseString = get_response_string(uri);
	if (responseString) {
		response.status = "200 OK";
		response.body = *responseString;
		return;
	}
	response.status = "404 Not Found";
	response.body = "Resource not found.";
}

void psscloud_server_start() {
	g_psscloud_server.set_request_handler(psscloud_request_handler);
	g_psscloud_server.start();
}

void psscloud_server_stop() {
	g_psscloud_server.stop();
}
