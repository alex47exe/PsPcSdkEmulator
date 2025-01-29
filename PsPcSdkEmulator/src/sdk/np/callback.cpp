/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "callback.h"

#include "../sce.h"
#include "../service/user.h"
#include <array>

static std::array<SceNpCallbackEntry, 8> g_callbacks;

void remove_user_from_callbacks(int user_id) {
	for (auto& entry : g_callbacks) {
		entry.user_states.erase(user_id);
	}
}

PSPCSDK_API int sceNpRegisterStateCallbackA(SceNpCallback callback, void* userdata) {
	int index = -1;
	for (int i = 0; i < g_callbacks.size(); ++i) {
		if (g_callbacks[i].callback == callback) {
			return SCE_ERROR_NP_CALLBACK_ALREADY_REGISTERED;
		}
		if (!g_callbacks[i].callback && index == -1) {
			index = i;
		}
	}
	if (index == -1) {
		return SCE_ERROR_NP_CALLBACK_NO_FREE_SLOT;
	}
	g_callbacks[index].callback = callback;
	g_callbacks[index].userdata = userdata;
	g_callbacks[index].user_states.clear();
	return index;
}

PSPCSDK_API SceResult sceNpUnregisterStateCallbackA(int callback_id) {
	if (callback_id < 0 || callback_id >= g_callbacks.size() || !g_callbacks[callback_id].callback) {
		return SCE_ERROR_NP_CALLBACK_NOT_REGISTERED;
	}
	g_callbacks[callback_id].callback = nullptr;
	g_callbacks[callback_id].userdata = nullptr;
	g_callbacks[callback_id].user_states.clear();
	return SCE_OK;
}

PSPCSDK_API void sceNpCheckCallback() {
	const auto& accounts = get_fake_accounts();
	for (const auto& account : accounts) {
		for (auto& entry : g_callbacks) {
			if (!entry.callback) {
				continue;
			}
			auto it = entry.user_states.find(account.user_id);
			bool call = false;
			if (it == entry.user_states.end()) {
				call = true;
				entry.user_states[account.user_id] = account.is_logged_in;
			} else if (it->second != account.is_logged_in) {
				call = true;
				it->second = account.is_logged_in;
			}
			if (call) {
				SceNpState status = account.is_logged_in ? SCE_NP_STATUS_LOGGED_IN : SCE_NP_STATUS_LOGGED_OUT;
				entry.callback(account.user_id, status, entry.userdata);
			}
		}
	}
}

void np_callback_reset() {
	g_callbacks.fill({});
}
