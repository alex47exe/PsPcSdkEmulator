/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "account.h"

#include "../sce.h"
#include "../service/user.h"

PSPCSDK_API SceResult sceNpGetAccountAge(int unknown1, int user_id, void* age) {
	if (unknown1 < 1 || user_id == -1 || !age) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	printf("(STUBBED) sceNpGetAccountAge(%d, %d, %p)\n", unknown1, user_id, age);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpGetAccountCountryA(int user_id, int* country) {
	if (user_id == -1 || !country) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	printf("(STUBBED) sceNpGetAccountCountryA(%x, %p)\n", user_id, country);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpGetAccountIdA(int user_id, uint64_t* id) {
	if (user_id == -1 || !id) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	SceNpAccount* account = get_fake_account(user_id);
	if (!account) {
		return SCE_ERROR_NP_INVALID_PARAM; // this is not the correct error code
	}
	*id = account->account_id;
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpGetAccountLanguage2(int user_id, int account, void* language) {
	if (user_id < 1 || account == -1 || !language) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	printf("(STUBBED) sceNpGetAccountLanguage2(%d, %d, %p)\n", user_id, account, language);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpGetOnlineId(int user_id, SceNpOnlineId* id) {
	if (user_id == -1 || !id) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	SceNpAccount* account = get_fake_account(user_id);
	if (!account) {
		return SCE_ERROR_NP_INVALID_PARAM; // this is not the correct error code
	}
	memset(id, 0, sizeof(SceNpOnlineId));
	strcpy_s(id->name, account->username.c_str());
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpGetState(int user_id, SceNpState* state) {
	if (user_id == -1 || !state) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	SceNpAccount* account = get_fake_account(user_id);
	if (!account) {
		*state = SCE_NP_STATUS_UNKNOW;
	} else {
		*state = account->is_logged_in ? SCE_NP_STATUS_LOGGED_IN : SCE_NP_STATUS_LOGGED_OUT;
	}
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpGetUserIdByAccountId(uint64_t id, int* user_id) {
	if (!id || !user_id) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	SceNpAccount* account = get_fake_account_by_account_id(id);
	if (!account) {
		return SCE_ERROR_NP_INVALID_PARAM; // this is not the correct error code
	}
	*user_id = account->user_id;
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpSignOut(int unknown1, int user_id) {
	if (unknown1 < 1 || user_id == -1) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	SceNpAccount* account = get_fake_account(user_id);
	if (!account) {
		return SCE_ERROR_NP_INVALID_PARAM; // this is not the correct error code
	}
	account->is_logged_in = false;
	return SCE_OK;
}
