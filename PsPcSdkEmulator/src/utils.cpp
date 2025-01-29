/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "utils.h"

#include <string.h>

bool strendswith(const char* str, const char* suffix) {
	size_t str_len = strlen(str);
	size_t suffix_len = strlen(suffix);
	if (str_len < suffix_len) {
		return false;
	}
	return strcmp(str + str_len - suffix_len, suffix) == 0;
}

bool wstrendswith(const wchar_t* str, const wchar_t* suffix) {
	size_t str_len = wcslen(str);
	size_t suffix_len = wcslen(suffix);
	if (str_len < suffix_len) {
		return false;
	}
	return wcscmp(str + str_len - suffix_len, suffix) == 0;
}

bool ismemzero(void* ptr, size_t size) {
	if (!ptr) {
		return false;
	}
	char* p = (char*)ptr;
	char* q = p + size;
	while (p < q) {
		if (*p++ != 0) {
			return false;
		}
	}
	return true;
}
