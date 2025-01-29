/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "user.h"

#include "../sce.h"
#include "../np/callback.h"

static std::vector<SceNpAccount> g_accounts;

void load_fake_account(uint64_t account_id) {
	load_fake_account(account_id, (int) g_accounts.size());
}

void load_fake_account(uint64_t account_id, int user_id) {
	SceNpAccount account;
	account.user_id = user_id;
	account.account_id = account_id;
	account.is_logged_in = true;
	g_accounts.push_back(account);
}

SceNpAccount* get_fake_account(int user_id) {
	for (auto& account : g_accounts) {
		if (account.user_id == user_id) {
			return &account;
		}
	}
	return nullptr;
}

SceNpAccount* get_fake_account_by_account_id(uint64_t account_id) {
	for (auto& account : g_accounts) {
		if (account.account_id == account_id) {
			return &account;
		}
	}
	return nullptr;
}

const std::vector<SceNpAccount>& get_fake_accounts() {
	return g_accounts;
}

bool unload_fake_account(int user_id) {
	for (auto it = g_accounts.begin(); it != g_accounts.end(); ++it) {
		if (it->user_id == user_id) {
			g_accounts.erase(it);
			remove_user_from_callbacks(user_id);
			return true;
		}
	}
	return false;
}

PSPCSDK_API	SceResult sceUserServiceLoadLastSignInUser(int* user_id) {
	if (g_accounts.empty()) {
		return SCE_ERROR_USER_SERVICE_INVALID_PARAM;
	}
	SceNpAccount* account = get_fake_account_by_account_id(DEFAULT_FAKE_ACCOUNT_ID);
	if (!account) {
		load_fake_account(DEFAULT_FAKE_ACCOUNT_ID);
		account = get_fake_account_by_account_id(DEFAULT_FAKE_ACCOUNT_ID);
	}
	*user_id = account->user_id;
	return SCE_OK;
}

PSPCSDK_API SceResult sceUserServiceLoadUserByAccountId(uint64_t account_id, int* user_id) {
	if (g_accounts.empty()) {
		return SCE_ERROR_USER_SERVICE_INVALID_PARAM;
	}
	SceNpAccount* account = get_fake_account_by_account_id(account_id);
	if (!account) {
		load_fake_account(account_id);
		account = get_fake_account_by_account_id(account_id);
	}
	*user_id = account->user_id;
	return SCE_OK;
}

PSPCSDK_API SceResult sceUserServiceUnloadUser(int user_id) {
	if (!unload_fake_account(user_id)) {
		return SCE_ERROR_USER_SERVICE_INVALID_PARAM;
	}
	return SCE_OK;
}

void service_user_reset() {
	g_accounts.clear();
}
