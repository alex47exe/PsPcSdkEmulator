/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#pragma once

#include <Windows.h>
#include <detours.h>
#include <vector>
#include <type_traits>

bool ismemzero(void* ptr, size_t size);
bool strendswith(const char* str, const char* suffix);
bool wstrendswith(const wchar_t* str, const wchar_t* suffix);

#define DETOUR_CALL(x) { LONG e = x; if (e != NO_ERROR) { DetourTransactionAbort(); return; } }

template<typename T>
static void HookFunction(T* originalFunction, T newFunction) {
	DETOUR_CALL(DetourTransactionBegin());
	DETOUR_CALL(DetourUpdateThread(GetCurrentThread()));
	DETOUR_CALL(DetourAttach(originalFunction, newFunction));
	DETOUR_CALL(DetourTransactionCommit());
}

template<typename T>
static void UnhookFunction(T* originalFunction, T newFunction) {
	DETOUR_CALL(DetourTransactionBegin());
	DETOUR_CALL(DetourUpdateThread(GetCurrentThread()));
	DETOUR_CALL(DetourDetach(originalFunction, newFunction));
	DETOUR_CALL(DetourTransactionCommit());
}

template<typename T, typename std::enable_if_t<std::is_integral_v<T>, int> = 0>
class IdProvider {
	private:
		T next_id;
		std::vector<T> free_ids;
	public:
		IdProvider() : next_id(1) {}
		T new_id() {
			if (free_ids.empty()) {
				return next_id++;
			}
			T id = free_ids.back();
			free_ids.pop_back();
			return id;
		}

		void free_id(T id) {
			if (!is_used(id)) {
				return;
			}
			free_ids.push_back(id);
			auto it = std::find(free_ids.begin(), free_ids.end(), next_id - 1);
			while (it != free_ids.end()) {
				free_ids.erase(it);
				next_id--;
				it = std::find(free_ids.begin(), free_ids.end(), next_id - 1);
			}
		}

		void reset() {
			next_id = 1;
			free_ids.clear();
		}

		bool is_used(T id) {
			return id < next_id && std::find(free_ids.begin(), free_ids.end(), id) == free_ids.end();
		}
};
