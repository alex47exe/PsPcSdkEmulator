/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "common.h"

#include "../sce.h"
#include "signin.h"

bool g_common_dialog_initialized = false;
bool g_common_dialog_busy = false;

PSPCSDK_API SceResult sceCommonDialogInitialize() {
	if (g_common_dialog_initialized) {
		return SCE_ERROR_COMMON_DIALOG_ALREADY_INITIALIZED;
	}
	g_common_dialog_initialized = true;
	return SCE_OK;
}

PSPCSDK_API bool sceCommonDialogIsUsed() {
	return g_common_dialog_busy;
}

void common_dialog_reset() {
	signin_dialog_reset();
	g_common_dialog_initialized = false;
	g_common_dialog_busy = false;
}
