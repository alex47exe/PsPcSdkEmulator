/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "pc.h"

#include "sce.h"
#include "dialog/common.h"
#include "np/misc.h"
#include "service/user.h"
#include "../net/net.h"

static void pc_sdk_reset() {
	common_dialog_reset();
	np_reset();
	service_user_reset();
}

static void print_property(ScePsPcProperty* property) {
	switch (property->type) {
	case SCE_PSPC_PROPERTY_TYPE_STRING:
		printf("  %s: %s\n", property->name, property->string);
		break;
	case SCE_PSPC_PROPERTY_TYPE_INT:
		printf("  %s: %d\n", property->name, property->integer);
		break;
	case SCE_PSPC_PROPERTY_TYPE_BOOL:
		printf("  %s: %s\n", property->name, property->boolean ? "true" : "false");
		break;
	case SCE_PSPC_PROPERTY_TYPE_DATA:
		printf("  %s: %p\n", property->name, property->data);
		break;
	}
}

PSPCSDK_API SceResult scePsPcInitializeInternal(ScePsPcInitializeInternalParam param) {
	pc_sdk_reset();
	load_fake_account(DEFAULT_FAKE_ACCOUNT_ID);
	pspcsdk_net_setup();
	printf("PsPcSdkEmulator initialized\n");
	printf("Properties:\n");
	for (int i = 0; i < param.property_count; i++) {
		print_property(&param.properties[i]);
	}
	return SCE_OK;
}

PSPCSDK_API SceResult scePsPcTerminate() {
	pc_sdk_reset();
	pspcsdk_net_cleanup();
	return SCE_OK;
}

PSPCSDK_API bool scePsPcIsSupportedPlatform() {
	return true;
}

PSPCSDK_API void scePsPcHookApiCall(char* name) {
	// The game calls this function before calling
	// any other PsPcSdk function. The parameter is
	// the name of the function that is about to be
	// called.
#ifndef NDEBUG
	printf("[PsPcSdkEmulator] called %s\n", name);
#endif
}

PSPCSDK_API SceResult scePsPcSetDeviceDataCollectionSetting(uint32_t mode) {
	if (mode != 0 && mode != 1) {
		return SCE_ERROR_PC_INVALID_DATA_COLLECTION_MODE;
	}
	printf("(STUBBED) scePsPcSetDeviceDataCollectionSetting(%d)\n", mode);
	return SCE_OK;
}
