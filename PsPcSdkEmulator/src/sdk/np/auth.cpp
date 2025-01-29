/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "auth.h"

#include "../sce.h"
#include "../../utils.h"
#include <Windows.h>

static IdProvider<uint32_t> g_auth_requests;

PSPCSDK_API SceResult sceNpAuthAbortRequest(uint32_t request) {
	if (!request) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	g_auth_requests.free_id(request);
	printf("(STUBBED) sceNpAuthAbortRequest(%d)\n", request);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpAuthCreateAsyncRequest(uint32_t request) {
	if (request) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	printf("(STUBBED) sceNpAuthCreateAsyncRequest(%d)\n", request);
	return SCE_OK;
}

PSPCSDK_API uint32_t sceNpAuthCreateRequest() {
	return g_auth_requests.new_id();
}

PSPCSDK_API SceResult sceNpAuthDeleteRequest(int request) {
	if (request) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	g_auth_requests.free_id(request);
	printf("(STUBBED) sceNpAuthDeleteRequest(%d)\n", request);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpAuthGetAuthorizationCodeV3(uint32_t request, void** data, char* auth_code, uint64_t* environment) {
	if (!request || !data || !auth_code || !environment) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	// we need to check request id here
	*environment = 256; // environemnt can be 1 or 256. We must set to 100. (maybe 1 is for dev environment)
	strcpy_s(auth_code, 135, "v3.AbCdEf");
	printf("(STUBBED) sceNpAuthGetAuthorizationCodeV3(%d, %p, %p, %p)\n", request, data, auth_code, environment);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpAuthGetPlatformError(int unkdown1, HRESULT* error, uint64_t unknown3) {
	if (!unkdown1 || !error || unknown3 != 4) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	printf("(STUBBED) sceNpAuthGetPlatformError(%x, %p, %llx)\n", unkdown1, error, unknown3);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpAuthPollAsync(int unknown1, uint64_t unknown2) {
	if (!unknown1 || !unknown2) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	printf("(STUBBED) sceNpAuthPollAsync(%x, %llx)\n", unknown1, unknown2);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpAuthSetTimeout(int unknown1, int unknown2, int unknown3, int unknown4, int unknown5) {
	if ((unknown1 != 0 && unknown1 < 1000000) ||
		(unknown2 != 0 && unknown2 < 10000000) ||
		(unknown3 != 0 && unknown3 < 10000000) ||
		(unknown4 != 0 && unknown4 < 10000000) ||
		(unknown5 != 0 && unknown5 < 10000000)) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	printf("(STUBBED) sceNpAuthSetTimeout(%d, %d, %d, %d, %d)\n", unknown1, unknown2, unknown3, unknown4, unknown5);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpAuthWaitAsync(int unknown1, uint64_t unknown2) {
	if (!unknown1 || !unknown2) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	printf("(STUBBED) sceNpAuthWaitAsync(%x, %llx)\n", unknown1, unknown2);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpCreateAsyncRequest(uint64_t request) {
	if (request) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	printf("(STUBBED) sceNpCreateAsyncRequest(%llx)\n", request);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpCreateRequest() {
	printf("(STUBBED) sceNpCreateRequest()\n");
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpDeleteRequest(int request) {
	if (request) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	printf("(STUBBED) sceNpDeleteRequest(%d)\n", request);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpAbortRequest(uint64_t request) {
	if (!request) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	printf("(STUBBED) sceNpAbortRequest(%llx)\n", request);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpPollAsync(int unknown1, void* unknown2) {
	if (unknown1 < 0 || !unknown2) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	printf("(STUBBED) sceNpPollAsync(%d, %p)\n", unknown1, unknown2);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpSetTimeout(int unknown1, int unknown2, int unknown3, int unknown4, int unknown5) {
	if ((unknown1 != 0 && unknown1 < 1000000) ||
		(unknown2 != 0 && unknown2 < 10000000) ||
		(unknown3 != 0 && unknown3 < 10000000) ||
		(unknown4 != 0 && unknown4 < 10000000) ||
		(unknown5 != 0 && unknown5 < 10000000)) {
		return SCE_ERROR_NP_INVALID_PARAM;
	}
	printf("(STUBBED) sceNpSetTimeout(%d, %d, %d, %d, %d)\n", unknown1, unknown2, unknown3, unknown4, unknown5);
	return SCE_OK;
}


PSPCSDK_API SceResult sceNpWaitAsync(int handle, int* status) {
	if (!status || handle < 1) {
		return SCE_ERROR_NP_NULL_PARAMETER;
	}
	printf("(STUBBED) sceNpWaitAsync(%d, %p)\n", handle, status);
	return SCE_OK;
}

void np_auth_reset() {
	g_auth_requests.reset();
}
