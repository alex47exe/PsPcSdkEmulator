/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "user.h"

#include "../sce.h"
#include "../np/callback.h"
#include "../../utils.h"
#include <cstdio>

static std::vector<SceNpAccount> g_accounts;
uint64_t g_custom_account_id = DEFAULT_FAKE_ACCOUNT_ID;
std::string g_custom_username = DEFAULT_PSN_USERNAME;

void load_config_from_ini() {
    auto iniPath = GetIniFilePath();
    
    // Try to load PSN ID from INI
    auto accountId = ReadIniHexValue(iniPath, "PSN", "psn_id", DEFAULT_FAKE_ACCOUNT_ID);
    if (accountId.has_value()) {
        g_custom_account_id = accountId.value();
        printf("[PsPcSdkEmulator] Using custom PSN ID: 0x%llx from INI file\n", g_custom_account_id);
    }
    
    // Try to load PSN username from INI
    auto username = ReadIniValue(iniPath, "PSN", "psn_user", DEFAULT_PSN_USERNAME);
    if (username.has_value()) {
        g_custom_username = username.value();
        printf("[PsPcSdkEmulator] Using custom PSN username: %s from INI file\n", g_custom_username.c_str());
    }
}

void load_fake_account(uint64_t account_id) {
	load_fake_account(account_id, (int) g_accounts.size());
}

void load_fake_account(uint64_t account_id, int user_id) {
    load_fake_account(account_id, user_id, g_custom_username.c_str());
}

void load_fake_account(uint64_t account_id, int user_id, const char* username) {
	SceNpAccount account;
	account.user_id = user_id;
	account.account_id = account_id;
	account.is_logged_in = true;
    account.username = username ? username : g_custom_username;
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
	SceNpAccount* account = get_fake_account_by_account_id(g_custom_account_id);
	if (!account) {
		load_fake_account(g_custom_account_id);
		account = get_fake_account_by_account_id(g_custom_account_id);
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
