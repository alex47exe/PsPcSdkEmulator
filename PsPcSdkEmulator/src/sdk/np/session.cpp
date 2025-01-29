/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "session.h"

#include "../sce.h"
#include <Windows.h>

static bool g_session_initialized = false;

PSPCSDK_API SceResult sceNpSessionSignalingCrossplayInitialize(void* param) {
	if (!param) {
		return SCE_ERROR_NP_SESSION_NULL_PARAM;
	}
	printf("(STUBBED) sceNpSessionSignalingCrossplayInitialize(%p)\n", param);
	g_session_initialized = true;
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpSessionSignalingCrossplayTerminate(void) {
	if (!g_session_initialized) {
		return SCE_ERROR_NP_SESSION_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpSessionSignalingCrossplayTerminate()\n");
	g_session_initialized = false;
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpSessionSignalingCrossplayCreateContext(void* param, uint64_t* context) {
	if (!g_session_initialized) {
		return SCE_ERROR_NP_SESSION_NOT_INITIALIZED;
	}
	if (!param || !context) {
		return SCE_ERROR_NP_SESSION_NULL_PARAM;
	}
	printf("(STUBBED) sceNpSessionSignalingCrossplayCreateContext(%p, %p)\n", param, context);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpSessionSignalingCrossplayDestroyContext(uint64_t context) {
	if (!g_session_initialized) {
		return SCE_ERROR_NP_SESSION_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpSessionSignalingCrossplayDestroyContext(%llu)\n", context);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpSessionSignalingCrossplayActivateUser(uint64_t context, uint64_t* param, uint64_t unknown3) {
	if (!g_session_initialized) {
		return SCE_ERROR_NP_SESSION_NOT_INITIALIZED;
	}
	if (!param || !unknown3 || !param[0] || !param[1]) {
		return SCE_ERROR_NP_SESSION_NULL_PARAM;
	}
	printf("(STUBBED) sceNpSessionSignalingCrossplayActivateUser(%llx, %p, %llx)\n", context, param, unknown3);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpSessionSignalingCrossplayActivateSession(uint64_t context, void* unknown2, uint64_t unknown3, void* unknown4, void* unknown5) {
	if (!unknown2 || !unknown4 || !unknown5) {
		return SCE_ERROR_NP_SESSION_NULL_PARAM;
	}
	if (!g_session_initialized) {
		return SCE_ERROR_NP_SESSION_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpSessionSignalingCrossplayActivateSession(%llx, %p, %llx, %p, %p)\n", context, unknown2, unknown3, unknown4, unknown5);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpSessionSignalingCrossplayDeactivate(uint64_t context, uint64_t unknown2) {
	if (!g_session_initialized) {
		return SCE_ERROR_NP_SESSION_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpSessionSignalingCrossplayDeactivate(%llx, %llx)\n", context, unknown2);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpSessionSignalingCrossplayRequestPrepare(uint64_t context, void* params) {
	if (!params) {
		return SCE_ERROR_NP_SESSION_NULL_PARAM;
	}
	if (!g_session_initialized) {
		return SCE_ERROR_NP_SESSION_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpSessionSignalingCrossplayPrepareRequest(%llx, %p)\n", context, params);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpSessionSignalingCrossplayEstablishConnection(uint64_t context, void* unknown2, void* unknown3, uint64_t* unknown4, void* unknown5, uint64_t unknown6, void* unknown7) {
	if (!g_session_initialized) {
		return SCE_ERROR_NP_SESSION_NOT_INITIALIZED;
	}
	if (!unknown4 || !unknown4[0] || !unknown4[1] || unknown6 > 0x40 || !unknown7) {
		return SCE_ERROR_NP_SESSION_NULL_PARAM;
	}
	printf("(STUBBED) sceNpSessionSignalingCrossplayEstablishConnection(%llx, %p, %p, %p, %p, %llx, %p)\n", context, unknown2, unknown3, unknown4, unknown5, unknown6, unknown7);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpSessionSignalingCrossplayAbortConnection(uint64_t context, uint64_t unknown2) {
	if (!g_session_initialized) {
		return SCE_ERROR_NP_SESSION_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpSessionSignalingCrossplayAbortConnection(%llx, %llx)\n", context, unknown2);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpSessionSignalingCrossplayGetMemoryInfo(void* out) {
	if (!out) {
		return SCE_ERROR_NP_SESSION_NULL_PARAM;
	}
	if (!g_session_initialized) {
		return SCE_ERROR_NP_SESSION_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpSessionSignalingCrossplayGetMemoryInfo(%p)\n", out);
	return SCE_OK;
}

PSPCSDK_API	SceResult sceNpSessionSignalingCrossplayGetPlatformError(HRESULT* error, uint64_t four) {
	if (!error || four != 4) {
		return SCE_ERROR_NP_SESSION_NULL_PARAM;
	}
	printf("(STUBBED) sceNpSessionSignalingCrossplayGetPlatformError(%p, %llx)\n", error, four);
	return SCE_OK;
}

void np_session_reset() {
	g_session_initialized = false;
}
