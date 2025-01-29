/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "misc.h"

#include "../sce.h"
#include "auth.h"
#include "callback.h"
#include "uds.h"
#include "webapi2.h"
#include "session.h"
#include <Windows.h>

PSPCSDK_API SceResult sceNpNotifyPremiumFeature(SceNpPremiumInfo* info) {
	if (!info) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	printf("(STUBBED) sceNpNotifyPremiumFeature(%p)\n", info);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpSetAdditionalScope(void* scpe) {
	if (!scpe) {
		return SCE_ERROR_NP_NULL_PARAMETER;
	}
	printf("(STUBBED) sceNpSetAdditionalScope(%p)\n", scpe);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpGetPlatformError(uint32_t unknown1, HRESULT* error, uint64_t four) {
	if (!error || !unknown1 || four != 4) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	printf("(STUBBED) sceNpGetPlatformError(%u, %p, %llu)\n", unknown1, error, four);
	*error = 0;
	return SCE_OK;
}

void np_reset() {
	np_auth_reset();
	np_callback_reset();
	np_uds_reset();
	np_web_api2_reset();
	np_session_reset();
}
