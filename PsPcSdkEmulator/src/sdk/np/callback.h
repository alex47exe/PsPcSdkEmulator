/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#pragma once

#include "account.h"
#include <unordered_map>

typedef void (*SceNpCallback)(int user_id, SceNpState status, void* userdata);

struct SceNpCallbackEntry {
	SceNpCallback callback = nullptr;
	void* userdata = nullptr;
	std::unordered_map<int, bool> user_states;
};;

void remove_user_from_callbacks(int user_id);

void np_callback_reset();
