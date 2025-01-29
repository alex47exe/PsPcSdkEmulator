/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "../sce.h"
#include "common.h"

PSPCSDK_API SceResult sceMsgDialogInitialize() {
	if (!g_common_dialog_initialized) {
		return SCE_ERROR_COMMON_DIALOG_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceMsgDialogInitialize\n");
	return SCE_OK;
}

PSPCSDK_API SceResult sceMsgDialogTerminate() {
	if (!g_common_dialog_initialized) {
		return SCE_ERROR_COMMON_DIALOG_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceMsgDialogTerminate\n");
	return SCE_OK;
}

PSPCSDK_API SceResult sceMsgDialogOpen(void* params) {
	if (!params) {
		return SCE_ERROR_COMMON_DIALOG_NULL_PARAMETER;
	}
	if (!g_common_dialog_initialized) {
		return SCE_ERROR_COMMON_DIALOG_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceMsgDialogOpen(%p)\n", params);
	return SCE_OK;
}

PSPCSDK_API SceResult sceMsgDialogClose() {
	if (!g_common_dialog_initialized) {
		return SCE_ERROR_COMMON_DIALOG_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceMsgDialogClose\n");
	return SCE_OK;
}

PSPCSDK_API SceResult sceMsgDialogGetResult(void* result) {
	if (!result) {
		return SCE_ERROR_COMMON_DIALOG_NULL_PARAMETER;
	}
	if (!g_common_dialog_initialized) {
		return SCE_ERROR_COMMON_DIALOG_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceMsgDialogGetResult(%p)\n", result);
	return SCE_OK;
}

PSPCSDK_API SceDialogStatus sceMsgDialogGetStatus() {
	printf("(STUBBED) sceMsgDialogGetStatus\n");
	return SCE_DIALOG_STATUS_NOT_INITIALIZED;
}

PSPCSDK_API SceDialogStatus sceMsgDialogUpdateStatus() {
	printf("(STUBBED) sceMsgDialogUpdateStatus\n");
	return SCE_DIALOG_STATUS_NOT_INITIALIZED;
}
