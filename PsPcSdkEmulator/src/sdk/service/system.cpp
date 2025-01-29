/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "system.h"

#include "../sce.h"
#include <memory.h>

PSPCSDK_API void sceSystemServiceInitializeFriendsListDialogParam(SceFriendsListDialogParam* param) {
	if (!param) {
		return;
	}
	memset(param, 0, sizeof(SceFriendsListDialogParam));
	param->unknown0 = 0x18;
	param->unknown2 = 0xffffffff;
}

PSPCSDK_API void sceSystemServiceInitializePlayerDialogParam(ScePlayerDialogParam* param) {
	if (!param) {
		return;
	}
	memset(param, 0, sizeof(ScePlayerDialogParam));
	param->unknown0 = 0x48;
	param->unknown2 = 0xffffffff;
}

PSPCSDK_API SceResult sceSystemServiceLaunchFriendsListDialog(SceFriendsListDialogParam* param) {
	if (!param || !param->unknown2) {
		return SCE_ERROR_SYSTEM_SERVICE_INVALID_PARAM;
	}
	printf("(STUBBED) sceSystemServiceLaunchFriendsListDialog(%p)\n", param);
	return SCE_OK;
}

PSPCSDK_API SceResult sceSystemServiceLaunchPlayerDialog(ScePlayerDialogParam* param) {
	if (!param || !param->unknown2) {
		return SCE_ERROR_SYSTEM_SERVICE_INVALID_PARAM;
	}
	printf("(STUBBED) sceSystemServiceLaunchPlayerDialog(%p)\n", param);
	return SCE_OK;
}
