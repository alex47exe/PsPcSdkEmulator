/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "dllmain.h"

#include "hooks.h"
#include "procs.h"
#include <windows.h>
#include <ShlObj_core.h>
#include <Shlwapi.h>
#include <cinttypes>

static HMODULE g_version_dll = nullptr;

wchar_t* g_cuurent_dll_path = nullptr;

static void get_current_dll_path(HMODULE mod) {
	DWORD size = MAX_PATH;
	g_cuurent_dll_path = new wchar_t[size];
retry:
	GetModuleFileNameW(mod, g_cuurent_dll_path, size);
	if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
		size *= 2;
		delete[] g_cuurent_dll_path;
		g_cuurent_dll_path = new wchar_t[size];
		goto retry;
	}
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH: {

            char system_path[MAX_PATH] = {};
			char version_dll_path[MAX_PATH] = {};

			if (SHGetFolderPathA(nullptr, CSIDL_SYSTEM, nullptr, SHGFP_TYPE_CURRENT, system_path) == S_OK) {
				PathCombineA(version_dll_path, system_path, "version.dll");
				g_version_dll = LoadLibraryA(version_dll_path);

				if (g_version_dll) {
					for (std::uint32_t i = 0; i < sizeof(g_version_dll_procs) / sizeof(g_version_dll_procs[0]); ++i) {
						g_version_dll_procs[i] = GetProcAddress(g_version_dll, g_exports_dll_proc_names[i]);
                    }
				}

			}
			get_current_dll_path(hModule);
			pspcsdk_hooks_setup();
            break;
		}
        case DLL_PROCESS_DETACH:
			pspcsdk_hooks_cleanup();

			if (g_version_dll) {
				FreeLibrary(g_version_dll);
			}

			if (g_cuurent_dll_path) {
				delete[] g_cuurent_dll_path;
			}
			break;
    }
    return TRUE;
}
