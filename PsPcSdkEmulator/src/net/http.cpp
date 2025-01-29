/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "http.h"

#include <algorithm>
#include <sstream>
#include <string_view>

void HttpResponse::send_response(SOCKET client_socket) {
	std::ostringstream response_stream;
	response_stream << "HTTP/1.1 " << status << "\r\n";
	for (const auto& [key, value] : headers) {
		if (key != "Content-Length") {
			response_stream << key << ": " << value << "\r\n";
		}
	}
	response_stream << "Content-Length: " << body.size() << "\r\n\r\n" << body;
	std::string response = response_stream.str();
	send(client_socket, response.c_str(), static_cast<int>(response.size()), 0);
}

int HttpServer::server_count = 0;

bool HttpServer::wsa_init() {
	if (server_count == 0) {
		WSADATA wsa_data;
		if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
			return false;
		}
	}
	server_count++;
	return true;
}

void HttpServer::wsa_cleanup() {
	if (--server_count == 0) {
		WSACleanup();
	}
}

std::unordered_map<std::string, std::string> HttpServer::parse_headers(const std::string& request) {
	std::unordered_map<std::string, std::string> headers;
	std::istringstream stream(request);
	std::string line;
	std::getline(stream, line);
	while (std::getline(stream, line) && line != "\r") {
		size_t colon_pos = line.find(':');
		if (colon_pos != std::string::npos) {
			std::string_view key = std::string_view(line).substr(0, colon_pos);
			std::string_view value = std::string_view(line).substr(colon_pos + 1);
			auto trim = [](std::string_view str) {
				auto start = str.find_first_not_of(" \t\r\n");
				auto end = str.find_last_not_of(" \t\r\n");
				return start == std::string_view::npos ? "" : str.substr(start, end - start + 1);
			};
			key = trim(key);
			value = trim(value);
			headers[std::string(key)] = std::string(value);
		}
	}
	return headers;
}

HttpServer::HttpParseResult HttpServer::parse_request(const std::string& request, std::string& method, std::string& uri, std::unordered_map<std::string, std::string>& headers) {
	size_t method_end = request.find(' ');
	if (method_end == std::string::npos) return HttpParseResult::MALFORMED;
	method = request.substr(0, method_end);
	if (method != "GET" && method != "POST" && method != "PUT" && method != "DELETE") return HttpParseResult::METHOD_UNSUPPORTED;
	size_t uri_end = request.find(' ', method_end + 1);
	if (uri_end == std::string::npos) return HttpParseResult::MALFORMED;
	uri = request.substr(method_end + 1, uri_end - method_end - 1);
	if (uri.empty()) return HttpParseResult::MALFORMED;
	std::string_view version = std::string_view(request).substr(uri_end + 1, 8);
	if (version != "HTTP/1.1") return HttpParseResult::PROTO_UNSUPPORTED;
	size_t header_end = request.find("\r\n\r\n");
	if (header_end == std::string::npos) return HttpParseResult::MALFORMED;
	headers = parse_headers(request);
	if (headers.find("Content-Length") != headers.end()) {
		try {
			int content_length = std::stoi(headers["Content-Length"]);
			if (content_length < 0) return HttpParseResult::MALFORMED;
		}
		catch (...) {
			return HttpParseResult::MALFORMED;
		}
	}
	return HttpParseResult::OK;
}

bool HttpServer::check_and_adjust_time(const std::chrono::time_point<std::chrono::steady_clock>& start_time, SOCKET client_socket) {
	auto elapsed_time = std::chrono::steady_clock::now() - start_time;
	long long elapsed_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count();
	int remaining_time = static_cast<int>(timeout - elapsed_time_ms);
	int socket_time = remaining_time < 1 ? 1 : remaining_time;
	setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&socket_time, sizeof(socket_time));
	setsockopt(client_socket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&socket_time, sizeof(socket_time));
	return remaining_time > 0;
}

void HttpServer::send_400_response(SOCKET client_socket) {
	HttpResponse response;
	response.status = "400 Bad Request";
	response.body = "Malformed request.";
	response.send_response(client_socket);
}

void HttpServer::send_404_response(SOCKET client_socket) {
	HttpResponse response;
	response.status = "404 Not Found";
	response.body = "Resource not found.";
	response.send_response(client_socket);
}

void HttpServer::send_405_response(SOCKET client_socket) {
	HttpResponse response;
	response.status = "405 Method Not Allowed";
	response.body = "Method not allowed.";
	response.send_response(client_socket);
}

void HttpServer::send_413_response(SOCKET client_socket) {
	HttpResponse response;
	response.status = "413 Payload Too Large";
	response.body = "Request body is too large.";
	response.send_response(client_socket);
}

void HttpServer::send_503_response(SOCKET client_socket) {
	HttpResponse response;
	response.status = "503 Service Unavailable";
	response.body = "Server is busy.";
	response.send_response(client_socket);
}

void HttpServer::send_505_response(SOCKET client_socket) {
	HttpResponse response;
	response.status = "505 HTTP Version Not Supported";
	response.body = "This server only supports HTTP/1.1.";
	response.send_response(client_socket);
}

void HttpServer::client_handler(SOCKET client_socket) {
	char buffer[4096];
	std::string request;
	std::string method;
	std::string uri;
	std::unordered_map<std::string, std::string> headers;
	int content_length = 0;
	size_t remaining_bytes = 0;
	size_t bytes_received = 0;
	size_t bytes_to_read = 0;
	std::string body;
	auto start_time = std::chrono::steady_clock::now();
	setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	setsockopt(client_socket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));
	while (true) {
		bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
		if (bytes_received <= 0 || !check_and_adjust_time(start_time, client_socket)) {
			return;
		}
		if (request.size() + bytes_received > max_headers_size) {
			send_413_response(client_socket);
			return;
		}
		request.append(buffer, bytes_received);
		if (request.find("\r\n\r\n") != std::string::npos) {
			break;
		}
		
	}
	HttpParseResult parse_result = parse_request(request, method, uri, headers);
	switch (parse_result) {
		case HttpParseResult::MALFORMED:
			send_400_response(client_socket);
			return;
		case HttpParseResult::METHOD_UNSUPPORTED:
			send_405_response(client_socket);
			return;
		case HttpParseResult::PROTO_UNSUPPORTED:
			send_505_response(client_socket);
			return;
		default:
			break;
	}
	if (headers.find("Content-Length") != headers.end()) {
		content_length = std::stoi(headers["Content-Length"]);
		if (content_length > max_body_size) {
			send_413_response(client_socket);
			return;
		}
		size_t request_body_start = request.find("\r\n\r\n") + 4;
		bytes_to_read =  request.size() - request_body_start;
		if (bytes_to_read > content_length) bytes_to_read = content_length;
		body.append(request, request_body_start, bytes_to_read);
		remaining_bytes = content_length - body.size();
		while (remaining_bytes > 0) {
			bytes_to_read = remaining_bytes;
			if (bytes_to_read > sizeof(buffer)) bytes_to_read = sizeof(buffer);
			bytes_received = recv(client_socket, buffer, static_cast<int>(bytes_to_read), 0);
			if (bytes_received <= 0 || !check_and_adjust_time(start_time, client_socket)) {
				return;
			}
			if (body.size() + bytes_received > max_body_size) {
				send_413_response(client_socket);
				return;
			}
			body.append(buffer, bytes_received);
			remaining_bytes -= bytes_received;
		}
	}
	if (request_handler) {
		HttpResponse response;
		(*request_handler)(method, uri, headers, body, response);
		response.send_response(client_socket);
	} else {
		send_404_response(client_socket);
	}
}

void HttpServer::client_thread(SOCKET client_socket) {
	client_handler(client_socket);
	closesocket(client_socket);
	{
		std::lock_guard<std::mutex> lock(connection_mutex);
		active_connections--;
		connection_cv.notify_one();
	}
}

void HttpServer::listener_thread() {
	while (server_running) {
		sockaddr_in client_addr{};
		int client_addr_size = sizeof(client_addr);
		SOCKET client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_addr_size);
		if (client_socket == INVALID_SOCKET) {
			continue;
		}
		{
			std::lock_guard<std::mutex> lock(connection_mutex);
			if (active_connections >= max_connections) {
				send_503_response(client_socket);
				closesocket(client_socket);
				continue;
			}
			active_connections++;
		}
		std::thread client_thread(&HttpServer::client_thread, this, client_socket);
		client_thread.detach();
	}
}

HttpServer::HttpServer(const std::string& address, uint16_t port) : server_socket{}, address(address), port(port) {}

HttpServer::~HttpServer() {
	if (server_running) {
		stop();
	}
}

void HttpServer::start() {
	if (server_running) return;
	if (!wsa_init()) return;
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == INVALID_SOCKET) {
		wsa_cleanup();
		return;
	}
	sockaddr_in server_addr{};
	server_addr.sin_family = AF_INET;
	if (inet_pton(AF_INET, address.c_str(), &server_addr.sin_addr) != 1) {
		closesocket(server_socket);
		wsa_cleanup();
		return;
	}
	server_addr.sin_port = htons(port);
	if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
		closesocket(server_socket);
		wsa_cleanup();
		return;
	}
	if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
		closesocket(server_socket);
		wsa_cleanup();
		return;
	}
	server_running = true;
	listener = std::thread(&HttpServer::listener_thread, this);
}

void HttpServer::stop() {
	if (!server_running) return;
	server_running = false;
	closesocket(server_socket);
	if (listener.joinable()) {
		listener.join();
	}
	std::unique_lock<std::mutex> lock(connection_mutex);
	connection_cv.wait(lock, [this] { return active_connections == 0; });
	wsa_cleanup();
}

void HttpServer::set_request_handler(HttpReuestHandler handler) {
	request_handler = handler;
}

void HttpServer::remove_request_handler() {
	request_handler.reset();
}
