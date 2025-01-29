/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "signin.h"

#include "../sce.h"
#include "../../utils.h"
#include "../service/user.h"
#include <Windows.h>

static SceDialogStatus g_signin_dialog_status = SCE_DIALOG_STATUS_NOT_INITIALIZED;

PSPCSDK_API SceResult sceSigninDialogInitialize() {
	if (!g_common_dialog_initialized) {
		return SCE_ERROR_COMMON_DIALOG_NOT_INITIALIZED;
	}
	if (g_signin_dialog_status != SCE_DIALOG_STATUS_NOT_INITIALIZED) {
		return SCE_ERROR_SIGNIN_DIALOG_ALREADY_INITIALIZED;
	}
	g_signin_dialog_status = SCE_DIALOG_STATUS_INITIALIZED;
	return SCE_OK;
}

PSPCSDK_API SceResult sceSigninDialogTerminate() {
	if (g_signin_dialog_status == SCE_DIALOG_STATUS_NOT_INITIALIZED) {
		return SCE_ERROR_COMMON_DIALOG_NOT_INITIALIZED;
	}
	if (g_signin_dialog_status != SCE_DIALOG_STATUS_INITIALIZED) {
		g_common_dialog_busy = false;
	}
	g_signin_dialog_status = SCE_DIALOG_STATUS_NOT_INITIALIZED;
	return SCE_OK;
}

PSPCSDK_API SceResult sceSigninDialogGetPlatformError(HRESULT* error, uint64_t four) {
	if (!error) {
		return SCE_ERROR_COMMON_DIALOG_NULL_PARAMETER;
	}
	if (four != 4) {
		return SCE_ERROR_COMMON_DIALOG_INVALID_PARAM;
	}
	printf("(STUBBED) sceSigninDialogGetPlatformError(%p, %llu)\n", error, four);
	*error = 0;
	return SCE_OK;
}

PSPCSDK_API SceResult sceSigninDialogOpen(SceSigninDialogParam* params) {
	if (!params) {
		return SCE_ERROR_COMMON_DIALOG_NULL_PARAMETER;
	}
#pragma warning(push)
#pragma warning(disable: 4311)
#pragma warning(disable: 4302)
	int expected_check = ((int) params) - 0x3f2e5ef7;
#pragma warning(pop)
	if (params->common.check != expected_check || params->common.unknown0 != 0x38) {
		return SCE_ERROR_COMMON_DIALOG_INVALID_PARAM;
	}
	if (!ismemzero(params->common.reserved, sizeof(params->common.reserved))) {
		return SCE_ERROR_COMMON_DIALOG_INVALID_PARAM;
	}
	if (params->unknown0 != 0x50) {
		return SCE_ERROR_COMMON_DIALOG_INVALID_PARAM;
	}
	if (!ismemzero(params->reserved, sizeof(params->reserved))) {
		return SCE_ERROR_COMMON_DIALOG_INVALID_PARAM;
	}
	if (g_signin_dialog_status == SCE_DIALOG_STATUS_NOT_INITIALIZED) {
		return SCE_ERROR_COMMON_DIALOG_NOT_INITIALIZED;
	}
	if (!params->common.hwnd) {
		return SCE_ERROR_COMMON_DIALOG_INVALID_PARAM;
	}
	if (g_signin_dialog_status != SCE_DIALOG_STATUS_INITIALIZED) {
		return SCE_ERROR_COMMON_DIALOG_ALREADY_RUNNING;
	}
	if (g_common_dialog_busy) {
		return SCE_ERROR_COMMON_DIALOG_BUSY;
	}
	g_common_dialog_busy = true;
	g_signin_dialog_status = SCE_DIALOG_STATUS_RUNNING;
	return SCE_OK;
}

PSPCSDK_API SceResult sceSigninDialogClose() {
	if (g_signin_dialog_status != SCE_DIALOG_STATUS_RUNNING && g_signin_dialog_status != SCE_DIALOG_STATUS_FINISHED) {
		return SCE_ERROR_COMMON_DIALOG_NOT_RUNNING;
	}
	g_common_dialog_busy = false;
	g_signin_dialog_status = SCE_DIALOG_STATUS_INITIALIZED;
	return SCE_OK;
}

PSPCSDK_API SceResult sceSigninDialogGetResult(SceSigninDialogResult* result) {
	if (!result) {
		return SCE_ERROR_COMMON_DIALOG_NULL_PARAMETER;
	}
	if (g_signin_dialog_status == SCE_DIALOG_STATUS_NOT_INITIALIZED) {
		return SCE_ERROR_COMMON_DIALOG_NOT_INITIALIZED;
	}
	if (g_signin_dialog_status != SCE_DIALOG_STATUS_FINISHED) {
		return SCE_ERROR_COMMON_DIALOG_STILL_RUNNING;
	}
	SceNpAccount* account = get_fake_account_by_account_id(DEFAULT_FAKE_ACCOUNT_ID);
	result->error = 0;
	result->user_id = account->user_id;
	result->account_id = account->account_id;
	return SCE_OK;
}

PSPCSDK_API SceDialogStatus sceSigninDialogGetStatus() {
	return g_signin_dialog_status;
}

PSPCSDK_API SceDialogStatus sceSigninDialogUpdateStatus() {
	SceDialogStatus status = g_signin_dialog_status;
	if (status == SCE_DIALOG_STATUS_RUNNING) {
		SceNpAccount* account = get_fake_account_by_account_id(DEFAULT_FAKE_ACCOUNT_ID);
		if (!account) {
			load_fake_account(DEFAULT_FAKE_ACCOUNT_ID);
			account = get_fake_account_by_account_id(DEFAULT_FAKE_ACCOUNT_ID);
		}
		account->is_logged_in = true;
		g_signin_dialog_status = SCE_DIALOG_STATUS_FINISHED;
	}
	return status;
}

void signin_dialog_reset() {
	g_signin_dialog_status = SCE_DIALOG_STATUS_NOT_INITIALIZED;
}
