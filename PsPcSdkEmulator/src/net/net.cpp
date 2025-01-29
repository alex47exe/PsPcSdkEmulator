/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "net.h"

#include "../utils.h"
#include "psscloud.h"
#include <winhttp.h>
#include <unordered_set>
#include <mutex>

static decltype(WinHttpOpen)* OriginalWinHttpOpen = nullptr;
static decltype(WinHttpConnect)* OriginalWinHttpConnect = nullptr;
static decltype(WinHttpOpenRequest)* OriginalWinHttpOpenRequest = nullptr;
static decltype(WinHttpCloseHandle)* OriginalWinHttpCloseHandle = nullptr;

static HMODULE g_winhttp_dll = nullptr;

static std::unordered_set<HINTERNET> g_tracked_handles;
static std::mutex g_tracked_handles_mutex;

static HINTERNET WINAPI HookWinHttpOpen(LPCWSTR pszAgentW, DWORD dwAccessType, LPCWSTR pszProxyW, LPCWSTR pszProxyBypassW, DWORD dwFlags) {
	if (pszAgentW && wcscmp(pszAgentW, L"PSNAccountLinking") == 0) {
		if (dwFlags & WINHTTP_FLAG_SECURE_DEFAULTS) {
			dwFlags = WINHTTP_FLAG_ASYNC;
		}
	}
	return OriginalWinHttpOpen(pszAgentW, dwAccessType, pszProxyW, pszProxyBypassW, dwFlags);
}

static HINTERNET WINAPI HookWinHttpConnect(HINTERNET hSession, LPCWSTR pswzServerName, INTERNET_PORT nServerPort, DWORD dwReserved) {
	HINTERNET result = 0;
	if (pswzServerName && wcscmp(pswzServerName, L"pss-cloud.net") == 0) {
		result = OriginalWinHttpConnect(hSession, L"localhost", PSSCLOUD_SERVER_PORT, dwReserved);
		{
			std::lock_guard<std::mutex> lock(g_tracked_handles_mutex);
			g_tracked_handles.insert(result);
		}
	} else {
		result = OriginalWinHttpConnect(hSession, pswzServerName, nServerPort, dwReserved);
	}
	return result;
}

static HINTERNET WINAPI HookWinHttpOpenRequest(HINTERNET hConnect, LPCWSTR pwszVerb, LPCWSTR pwszObjectName, LPCWSTR pwszVersion, LPCWSTR pwszReferrer, LPCWSTR FAR* ppwszAcceptTypes, DWORD dwFlags) {
	bool is_tracked = false;
	{
		std::lock_guard<std::mutex> lock(g_tracked_handles_mutex);
		is_tracked = g_tracked_handles.find(hConnect) != g_tracked_handles.end();
	}
	if (is_tracked) {
		dwFlags &= ~WINHTTP_FLAG_SECURE;
	}
	return OriginalWinHttpOpenRequest(hConnect, pwszVerb, pwszObjectName, pwszVersion, pwszReferrer, ppwszAcceptTypes, dwFlags);
}

static BOOL WINAPI HookWinHttpCloseHandle(HINTERNET hInternet) {
	{
		std::lock_guard<std::mutex> lock(g_tracked_handles_mutex);
		g_tracked_handles.erase(hInternet);
	}
	return OriginalWinHttpCloseHandle(hInternet);
}

void pspcsdk_net_setup() {
	if (g_winhttp_dll) {
		return;
	}

	g_winhttp_dll = LoadLibrary(L"winhttp.dll");

	if (!g_winhttp_dll) {
		return;
	}

	OriginalWinHttpOpen = (decltype(OriginalWinHttpOpen))GetProcAddress(g_winhttp_dll, "WinHttpOpen");
	OriginalWinHttpConnect = (decltype(OriginalWinHttpConnect))GetProcAddress(g_winhttp_dll, "WinHttpConnect");
	OriginalWinHttpOpenRequest = (decltype(OriginalWinHttpOpenRequest))GetProcAddress(g_winhttp_dll, "WinHttpOpenRequest");

	HookFunction(&OriginalWinHttpOpen, HookWinHttpOpen);
	HookFunction(&OriginalWinHttpConnect, HookWinHttpConnect);
	HookFunction(&OriginalWinHttpOpenRequest, HookWinHttpOpenRequest);

	psscloud_server_start();
	g_tracked_handles.clear();
}

void pspcsdk_net_cleanup() {
	if (!g_winhttp_dll) {
		return;
	}

	psscloud_server_stop();
	g_tracked_handles.clear();

	UnhookFunction(&OriginalWinHttpOpen, HookWinHttpOpen);
	UnhookFunction(&OriginalWinHttpConnect, HookWinHttpConnect);
	UnhookFunction(&OriginalWinHttpOpenRequest, HookWinHttpOpenRequest);

	FreeLibrary(g_winhttp_dll);
	g_winhttp_dll = nullptr;
}
