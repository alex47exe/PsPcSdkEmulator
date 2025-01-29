; This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
; If a copy of the MPL was not distributed with this file, you can obtain one at
; https://mozilla.org/MPL/2.0/.
;
; Copyright (c) 2025 Lander Gallastegi (LNDF)

.code
	extern g_version_dll_procs:QWORD
	GetFileVersionInfoA proc
		jmp QWORD ptr g_version_dll_procs[0 * 8]
	GetFileVersionInfoA endp
	GetFileVersionInfoByHandle proc
		jmp QWORD ptr g_version_dll_procs[1 * 8]
	GetFileVersionInfoByHandle endp
	GetFileVersionInfoExA proc
		jmp QWORD ptr g_version_dll_procs[2 * 8]
	GetFileVersionInfoExA endp
	GetFileVersionInfoExW proc
		jmp QWORD ptr g_version_dll_procs[3 * 8]
	GetFileVersionInfoExW endp
	GetFileVersionInfoSizeA proc
		jmp QWORD ptr g_version_dll_procs[4 * 8]
	GetFileVersionInfoSizeA endp
	GetFileVersionInfoSizeExA proc
		jmp QWORD ptr g_version_dll_procs[5 * 8]
	GetFileVersionInfoSizeExA endp
	GetFileVersionInfoSizeExW proc
		jmp QWORD ptr g_version_dll_procs[6 * 8]
	GetFileVersionInfoSizeExW endp
	GetFileVersionInfoSizeW proc
		jmp QWORD ptr g_version_dll_procs[7 * 8]
	GetFileVersionInfoSizeW endp
	GetFileVersionInfoW proc
		jmp QWORD ptr g_version_dll_procs[8 * 8]
	GetFileVersionInfoW endp
	VerFindFileA proc
		jmp QWORD ptr g_version_dll_procs[9 * 8]
	VerFindFileA endp
	VerFindFileW proc
		jmp QWORD ptr g_version_dll_procs[10 * 8]
	VerFindFileW endp
	VerInstallFileA proc
		jmp QWORD ptr g_version_dll_procs[11 * 8]
	VerInstallFileA endp
	VerInstallFileW proc
		jmp QWORD ptr g_version_dll_procs[12 * 8]
	VerInstallFileW endp
	VerLanguageNameA proc
		jmp QWORD ptr g_version_dll_procs[13 * 8]
	VerLanguageNameA endp
	VerLanguageNameW proc
		jmp QWORD ptr g_version_dll_procs[14 * 8]
	VerLanguageNameW endp
	VerQueryValueA proc
		jmp QWORD ptr g_version_dll_procs[15 * 8]
	VerQueryValueA endp
	VerQueryValueW proc
		jmp QWORD ptr g_version_dll_procs[16 * 8]
	VerQueryValueW endp
end
