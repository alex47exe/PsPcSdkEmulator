/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "hooks.h"
#include "../utils.h"
#include <Windows.h>
#include <SoftPub.h>
#include <Shlwapi.h>

/////////////////////////////////////////
// Hooked functions
/////////////////////////////////////////

static decltype(FindFirstFileExA)* OriginalFindFirstFileExA = nullptr;
static decltype(FindNextFileA)* OriginalFindNextFileA = nullptr;
static decltype(FindClose)* OriginalFindClose = nullptr;
static decltype(PathFileExistsA)* OriginalPathFileExistsA = nullptr;
static decltype(CreateFileA)* OriginalCreateFileA = nullptr;
static decltype(GetFileVersionInfoSizeA)* OriginalGetFileVersionInfoSizeA = nullptr;
static decltype(GetFileVersionInfoA)* OriginalGetFileVersionInfoA = nullptr;
static decltype(WinVerifyTrust)* OriginalWinVerifyTrust = nullptr;
static decltype(WTHelperProvDataFromStateData)* OriginalWTHelperProvDataFromStateData = nullptr;
static decltype(WTHelperGetProvSignerFromChain)* OriginalWTHelperGetProvSignerFromChain = nullptr;
static decltype(LoadLibraryExA)* OriginalLoadLibraryExA = nullptr;

static HMODULE g_wintrust_dll = nullptr;

#define FAKE_HANDLE_MAGIC 0x12345438
static DWORD g_fake_handle = FAKE_HANDLE_MAGIC;

static HANDLE WINAPI HookFindFirstFileExA(LPCSTR lpFileName, FINDEX_INFO_LEVELS fInfoLevelId, LPVOID lpFindFileData, FINDEX_SEARCH_OPS fSearchOp, LPVOID lpSearchFilter, DWORD dwAdditionalFlags) {
	// We need to tell the game that the SDK is installed
	WIN32_FIND_DATAA& data = *reinterpret_cast<WIN32_FIND_DATAA*>(lpFindFileData);
	const char* sdk_path_start = "C:\\ProgramData\\Sony Interactive Entertainment Inc\\PSPC_SDK";

	// Check both the start of the path and the wildcard (the "S22" part may change in the future)
	if (!lpFileName || strncmp(lpFileName, sdk_path_start, strlen(sdk_path_start)) != 0 || lpFileName[strlen(lpFileName) - 1] != '*') {
		return OriginalFindFirstFileExA(lpFileName, fInfoLevelId, lpFindFileData, fSearchOp, lpSearchFilter, dwAdditionalFlags);
	}

	// We need to return a handle to the SDK directory
	memset(&data, 0, sizeof(WIN32_FIND_DATAA));
	data.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;

	// We set the what would be the SDK directory
	strncpy_s(data.cFileName, sizeof(data.cFileName), lpFileName, _TRUNCATE);
	strncpy_s(data.cFileName + strlen(data.cFileName) - 1, sizeof(data.cFileName) - strlen(data.cFileName) + 1, "3.50.00.11", _TRUNCATE);
	GetShortPathNameA(data.cFileName, data.cAlternateFileName, sizeof(data.cAlternateFileName));

	return reinterpret_cast<HANDLE>(&g_fake_handle);
}

static BOOL WINAPI HookFindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData) {
	DWORD* info = reinterpret_cast<DWORD*>(hFindFile);
	if (!info || info != &g_fake_handle || *info != FAKE_HANDLE_MAGIC) {
		return OriginalFindNextFileA(hFindFile, lpFindFileData);
	}
	
	// Only one file in the SDK directory
	SetLastError(ERROR_NO_MORE_FILES);
	return FALSE;
}

static BOOL WINAPI HookFindClose(HANDLE hFindFile) {
	DWORD* info = reinterpret_cast<DWORD*>(hFindFile);
	if (!info || info != &g_fake_handle || *info != FAKE_HANDLE_MAGIC) {
		return OriginalFindClose(hFindFile);
	}

	return TRUE;
}

static BOOL WINAPI HookPathFileExistsA(LPCSTR pszPath) {
	if (strendswith(pszPath, "PsPcSdk.dll")) {
		return TRUE;
	}
	return OriginalPathFileExistsA(pszPath);
}

static DWORD APIENTRY HookGetFileVersionInfoSizeA(LPCSTR lptstrFilename, LPDWORD lpdwHandle) {
	if (strendswith(lptstrFilename, "PsPcSdk.dll")) {
		// We include the same version info as PsPcSdk.dll
		return OriginalGetFileVersionInfoSizeA("version.dll", lpdwHandle);
	}
	return OriginalGetFileVersionInfoSizeA(lptstrFilename, lpdwHandle);
}

static BOOL APIENTRY HookGetFileVersionInfoA(LPCSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) {
	if (strendswith(lptstrFilename, "PsPcSdk.dll")) {
		// We include the same version info as PsPcSdk.dll
		return OriginalGetFileVersionInfoA("version.dll", dwHandle, dwLen, lpData);
	}
	return OriginalGetFileVersionInfoA(lptstrFilename, dwHandle, dwLen, lpData);
}

static HANDLE WINAPI HookCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
	if (strendswith(lpFileName, "PsPcSdk.dll")) {
		// Used to obtain the cerificate from PsPcSdk.dll. We use a self signed certificate.
		return OriginalCreateFileA("version.dll", dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	}
	return OriginalCreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

static LONG WINAPI HookWinVerifyTrust(HWND hwnd, GUID* pgActionID, LPVOID pWVTData) {
	const GUID generic_action_v2 = WINTRUST_ACTION_GENERIC_VERIFY_V2;
	if (pgActionID && memcmp(pgActionID, &generic_action_v2, sizeof(GUID)) == 0) {
		WINTRUST_DATA* data = reinterpret_cast<WINTRUST_DATA*>(pWVTData);
		if (data->dwUnionChoice == WTD_CHOICE_FILE && wstrendswith(data->pFile->pcwszFilePath, L"PsPcSdk.dll")) {
			data->hWVTStateData = reinterpret_cast<HANDLE>(&g_fake_handle);
			return ERROR_SUCCESS;
		}
	}
	return OriginalWinVerifyTrust(hwnd, pgActionID, pWVTData);
}

static CRYPT_PROVIDER_DATA* WINAPI HookWTHelperProvDataFromStateData(HANDLE hStateData) {
	DWORD* info = reinterpret_cast<DWORD*>(hStateData);
	if (info && info == &g_fake_handle && *info == FAKE_HANDLE_MAGIC) {
		return reinterpret_cast<CRYPT_PROVIDER_DATA*>(info);
	}
	return OriginalWTHelperProvDataFromStateData(hStateData);
}

static CRYPT_PROVIDER_SGNR* WINAPI HookWTHelperGetProvSignerFromChain(CRYPT_PROVIDER_DATA* pProvData, DWORD idxSigner, BOOL fCounterSigner, DWORD idxCounterSigner) {
	DWORD* info = reinterpret_cast<DWORD*>(pProvData);
	if (info && info == &g_fake_handle && *info == FAKE_HANDLE_MAGIC) {
		return nullptr;
	}
	return OriginalWTHelperGetProvSignerFromChain(pProvData, idxSigner, fCounterSigner, idxCounterSigner);
}

static HMODULE WINAPI HookLoadLibraryExA(LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags) {
	if (strendswith(lpLibFileName, "PsPcSdk.dll")) {
		// The game may pass the handle to FreeLibrary
		pspcsdk_hooks_cleanup();
		return LoadLibraryA("version.dll");
	}
	return OriginalLoadLibraryExA(lpLibFileName, hFile, dwFlags);
}

/////////////////////////////////////////
// Initialization
/////////////////////////////////////////

void pspcsdk_hooks_setup() {
	if (g_wintrust_dll) {
		return;
	}

	g_wintrust_dll = LoadLibraryA("wintrust.dll");
	if (!g_wintrust_dll) {
		MessageBoxA(nullptr, "Failed to load wintrust.dll. PsPcSdkEmulator will not be initialized.", "PsPcSdkEmulator error", MB_ICONERROR);
		return;
	}

	OriginalFindFirstFileExA = &FindFirstFileExA;
	OriginalFindNextFileA = &FindNextFileA;
	OriginalFindClose = &FindClose;
	OriginalPathFileExistsA = &PathFileExistsA;
	OriginalGetFileVersionInfoSizeA = &GetFileVersionInfoSizeA;
	OriginalGetFileVersionInfoA = &GetFileVersionInfoA;
	OriginalCreateFileA = &CreateFileA;
	OriginalWinVerifyTrust = (decltype(OriginalWinVerifyTrust)) GetProcAddress(g_wintrust_dll, "WinVerifyTrust");
	OriginalWTHelperProvDataFromStateData = (decltype(OriginalWTHelperProvDataFromStateData))GetProcAddress(g_wintrust_dll, "WTHelperProvDataFromStateData");
	OriginalWTHelperGetProvSignerFromChain = (decltype(OriginalWTHelperGetProvSignerFromChain))GetProcAddress(g_wintrust_dll, "WTHelperGetProvSignerFromChain");
	OriginalLoadLibraryExA = &LoadLibraryExA;

	HookFunction(&OriginalFindFirstFileExA, HookFindFirstFileExA);
	HookFunction(&OriginalFindNextFileA, HookFindNextFileA);
	HookFunction(&OriginalFindClose, HookFindClose);
	HookFunction(&OriginalPathFileExistsA, HookPathFileExistsA);
	HookFunction(&OriginalGetFileVersionInfoSizeA, HookGetFileVersionInfoSizeA);
	HookFunction(&OriginalGetFileVersionInfoA, HookGetFileVersionInfoA);
	HookFunction(&OriginalCreateFileA, HookCreateFileA);
	HookFunction(&OriginalWinVerifyTrust, HookWinVerifyTrust);
	HookFunction(&OriginalWTHelperProvDataFromStateData, HookWTHelperProvDataFromStateData);
	HookFunction(&OriginalWTHelperGetProvSignerFromChain, HookWTHelperGetProvSignerFromChain);
	HookFunction(&OriginalLoadLibraryExA, HookLoadLibraryExA);
}

void pspcsdk_hooks_cleanup() {
	if (!g_wintrust_dll) {
		return;
	}

	UnhookFunction(&OriginalFindFirstFileExA, HookFindFirstFileExA);
	UnhookFunction(&OriginalFindNextFileA, HookFindNextFileA);
	UnhookFunction(&OriginalFindClose, HookFindClose);
	UnhookFunction(&OriginalPathFileExistsA, HookPathFileExistsA);
	UnhookFunction(&OriginalGetFileVersionInfoSizeA, HookGetFileVersionInfoSizeA);
	UnhookFunction(&OriginalGetFileVersionInfoA, HookGetFileVersionInfoA);
	UnhookFunction(&OriginalCreateFileA, HookCreateFileA);
	UnhookFunction(&OriginalWinVerifyTrust, HookWinVerifyTrust);
	UnhookFunction(&OriginalWTHelperProvDataFromStateData, HookWTHelperProvDataFromStateData);
	UnhookFunction(&OriginalWTHelperGetProvSignerFromChain, HookWTHelperGetProvSignerFromChain);
	UnhookFunction(&OriginalLoadLibraryExA, HookLoadLibraryExA);
	
	FreeLibrary(g_wintrust_dll);
	g_wintrust_dll = nullptr;
}
