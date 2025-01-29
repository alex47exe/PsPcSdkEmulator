/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#pragma once

#include <stdint.h>
#include <vector>

#define DEFAULT_FAKE_ACCOUNT_ID 0x1234567890ABCDEF

struct SceNpAccount {
	int user_id;
	uint64_t account_id;
	bool is_logged_in;
};

void load_fake_account(uint64_t account_id);
void load_fake_account(uint64_t account_id, int user_id);
SceNpAccount* get_fake_account(int user_id);
SceNpAccount* get_fake_account_by_account_id(uint64_t account_id);
const std::vector<SceNpAccount>& get_fake_accounts();
bool unload_fake_account(int user_id);

void service_user_reset();
