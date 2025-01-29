/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#pragma once

#include <string>
#include <unordered_map>
#include <atomic>
#include <chrono>
#include <mutex>
#include <thread>
#include <optional>
#include <functional>
#include <WinSock2.h>
#include <WS2tcpip.h>

struct HttpResponse {
	std::string status;
	std::string body;
	std::unordered_map<std::string, std::string> headers;

	void send_response(SOCKET client_socket);
};

using HttpReuestHandler = std::function<void(const std::string& method, const std::string& uri, const std::unordered_map<std::string, std::string>& headers, const std::string& body, HttpResponse& response)>;

#include <condition_variable>

class HttpServer {
	private:
		enum HttpParseResult {
			OK,
			MALFORMED,
			METHOD_UNSUPPORTED,
			PROTO_UNSUPPORTED,
		};;

		static constexpr int max_connections = 20;
		static constexpr int max_headers_size = 8192;
		static constexpr int max_body_size = 10 * 1024 * 1024;
		static constexpr int timeout = 5000;
		
		static int server_count;

		static bool wsa_init();
		static void wsa_cleanup();

		SOCKET server_socket;
		std::string address;
		uint16_t port;
		std::atomic<bool> server_running;
		std::atomic<int> active_connections;
		std::mutex connection_mutex;
		std::condition_variable connection_cv;
		std::thread listener;
		std::optional<HttpReuestHandler> request_handler;

		std::unordered_map<std::string, std::string> parse_headers(const std::string& request);
		HttpParseResult parse_request(const std::string& request, std::string& method, std::string& uri, std::unordered_map<std::string, std::string>& headers);
		bool check_and_adjust_time(const std::chrono::time_point<std::chrono::steady_clock>& start_time, SOCKET client_socket);

		void send_400_response(SOCKET client_socket);
		void send_404_response(SOCKET client_socket);
		void send_405_response(SOCKET client_socket);
		void send_413_response(SOCKET client_socket);
		void send_503_response(SOCKET client_socket);
		void send_505_response(SOCKET client_socket);

		void client_handler(SOCKET client_socket);
		void client_thread(SOCKET client_socket);
		void listener_thread();
	public:
		HttpServer(const std::string& address, uint16_t port);
		~HttpServer();
		void start();
		void stop();

		void set_request_handler(HttpReuestHandler handler);
		void remove_request_handler();
};
