/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "uds.h"

#include "../sce.h"
#include <string.h>
#include <Windows.h>

bool g_udsInitialized = false;

PSPCSDK_API SceResult sceNpUniversalDataSystemInitialize(SceNpUniversalDataSystemInitParams* params) {
	if (g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_ALREADY_INITIALIZED;
	}
	if (!params) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_PARAM;
	}
	if (params->size != 0x118) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_PARAM_UNK1;
	}
	if (!params->unknown2) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_PARAM;
	}
	size_t path_len = strnlen(params->path, 0x105);
	if (path_len <= 0 || path_len >= 0x105) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_PARAM;
	}
	printf("(STUBBED) sceUniversalDataSystemInitialize(%p)\n", params);
	g_udsInitialized = true;
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemTerminate() {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	g_udsInitialized = false;
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemCreateContext(int* unknown1, int unknown2, int unknown3, void* unused) {
	if (!unknown1 || unknown3 >= 100 || unused) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_PARAM;
	}
	printf("(STUBBED) sceUniversalDataSystemCreateContext(%p, %d, %d, %p)\n", unknown1, unknown2, unknown3, unused);
	*unknown1 = 0x12345678;
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemDestroyContext(int context) {
	if (context == -1) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_CONTEXT;
	}
	printf("(STUBBED) sceUniversalDataSystemDestroyContext(%d)\n", context);
	return SCE_OK;
}

PSPCSDK_API	SceResult sceNpUniversalDataSystemCreateEvent(char* name, uint64_t unknown2, void* unknown3, void* unknown4) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!name) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_EVENT_NAME;
	}
	printf("(STUBBED) sceUniversalDataSystemCreateEvent(%s, %llx, %p, %p)\n", name, unknown2, unknown3, unknown4);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemDestroyEvent(void* context) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceUniversalDataSystemDestroyEvent(%p)\n", context);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemCreateEventPropertyArray(void* param) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!param) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_PARAM;
	}
	printf("(STUBBED) sceUniversalDataSystemCreateEventPropertyArray(%p)\n", param);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemDestroyEventPropertyArray(void* param) {
	printf("(STUBBED) sceUniversalDataSystemDestroyEventPropertyArray(%p)\n", param);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemCreateEventPropertyObject(void* param) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!param) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_PARAM;
	}
	printf("(STUBBED) sceUniversalDataSystemCreateEventPropertyObject(%p)\n", param);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemDestroyEventPropertyObject(void* param) {
	printf("(STUBBED) sceUniversalDataSystemDestroyEventPropertyObject(%p)\n", param);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemCreateHandle(int* handle) {
	if (!handle) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_PARAM;
	}
	printf("(STUBBED) sceUniversalDataSystemCreateHandle(%p)\n", handle);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemDestroyHandle(int param) {
	if (param == -1) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_HANDLE;
	}
	printf("(STUBBED) sceUniversalDataSystemDestroyHandle(%d)\n", param);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemAbortHandle(int param) {
	if (param == -1) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_HANDLE;
	}
	printf("(STUBBED) sceUniversalDataSystemAbortHandle(%d)\n", param);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventEstimateSize(int* param, int* size) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!param) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_EVENT;
	}
	if (!size) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_PARAM;
	}
	printf("(STUBBED) sceUniversalDataSystemEventEstimateSize(%p, %p)\n", param, size);
	*size = 0x100;
	return SCE_OK;
}

PSPCSDK_API	SceResult sceNpUniversalDataSystemEventPropertyArraySetArray(void* dest, void* src, uint64_t* copied) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dest) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_ARRAY_DST;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyArraySetArray(%p, %p, %p)\n", dest, src, copied);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyArraySetBinary(void* dest, void* data, uint64_t size) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dest) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_ARRAY_DST;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyArraySetBinary(%p, %p, %llx)\n", dest, data, size);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyArraySetFloat32(void* dest, float value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dest) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_ARRAY_DST;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyArraySetFloat32(%p, %f)\n", dest, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyArraySetFloat64(void* dest, double value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dest) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_ARRAY_DST;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyArraySetFloat64(%p, %f)\n", dest, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyArraySetInt32(void* dest, int32_t value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dest) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_ARRAY_DST;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyArraySetInt32(%p, %d)\n", dest, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyArraySetInt64(void* dest, int64_t value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dest) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_ARRAY_DST;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyArraySetInt64(%p, %lld)\n", dest, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyArraySetString(void* dest, const char* value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dest) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_ARRAY_DST;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyArraySetString(%p, %s)\n", dest, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyArraySetUInt32(void* dest, uint32_t value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dest) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_ARRAY_DST;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyArraySetUInt32(%p, %u)\n", dest, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyArraySetUInt64(void* dest, uint64_t value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dest) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_ARRAY_DST;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyArraySetUInt64(%p, %llu)\n", dest, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyArraySetBool(void* dest, bool value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dest) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_ARRAY_DST;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyArraySetBool(%p, %d)\n", dest, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyArraySetObject(void* dest, void* src, uint64_t* copied) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dest) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_OBJECT_DST;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyArraySetObject(%p, %p, %p)\n", dest, src, copied);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyObjectSetArray(void* dst, void* key, void* src, uint64_t* copied) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dst) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_OBJECT_DST;
	}
	if (!key) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_KEY;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyObjectSetArray(%p, %p, %p, %p)\n", dst, key, src, copied);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyObjectSetBinary(void* dst, void* key, void* data, uint64_t size) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dst) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_OBJECT_DST;
	}
	if (!key) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_KEY;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyObjectSetBinary(%p, %p, %p, %llx)\n", dst, key, data, size);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyObjectSetFloat32(void* dst, void* key, float value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dst) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_OBJECT_DST;
	}
	if (!key) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_KEY;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyObjectSetFloat32(%p, %p, %f)\n", dst, key, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyObjectSetFloat64(void* dst, void* key, double value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dst) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_OBJECT_DST;
	}
	if (!key) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_KEY;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyObjectSetFloat64(%p, %p, %f)\n", dst, key, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyObjectSetInt32(void* dst, void* key, int32_t value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dst) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_OBJECT_DST;
	}
	if (!key) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_KEY;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyObjectSetInt32(%p, %p, %d)\n", dst, key, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyObjectSetInt64(void* dst, void* key, int64_t value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dst) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_OBJECT_DST;
	}
	if (!key) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_KEY;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyObjectSetInt64(%p, %p, %lld)\n", dst, key, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyObjectSetString(void* dst, void* key, const char* value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dst) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_OBJECT_DST;
	}
	if (!key) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_KEY;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyObjectSetString(%p, %p, %s)\n", dst, key, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyObjectSetUInt32(void* dst, void* key, uint32_t value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dst) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_OBJECT_DST;
	}
	if (!key) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_KEY;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyObjectSetUInt32(%p, %p, %u)\n", dst, key, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyObjectSetUInt64(void* dst, void* key, uint64_t value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dst) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_OBJECT_DST;
	}
	if (!key) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_KEY;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyObjectSetUInt64(%p, %p, %llu)\n", dst, key, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyObjectSetBool(void* dst, void* key, bool value) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dst) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_OBJECT_DST;
	}
	if (!key) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_KEY;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyObjectSetBool(%p, %p, %d)\n", dst, key, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventPropertyObjectSetObject(void* dst, void* key, void* src, uint64_t* copied) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!dst) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_OBJECT_DST;
	}
	if (!key) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_KEY;
	}
	printf("(STUBBED) sceUniversalDataSystemEventPropertyObjectSetObject(%p, %p, %p, %p)\n", dst, key, src, copied);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemEventToString(void* event, char* buffer, uint64_t size, uint64_t* written) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!event) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_EVENT;
	}
	if (!buffer && !written) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_PARAM;
	}
	printf("(STUBBED) sceUniversalDataSystemEventToString(%p, %p, %llx, %p)\n", event, buffer, size, written);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemGetMemoryStat(void* out) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!out) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_PARAM;
	}
	printf("(STUBBED) sceUniversalDataSystemGetMemoryStat(%p)\n", out);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemGetPlatformError(HRESULT* error, int64_t four) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (!error || four != 4) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_PARAM;
	}
	printf("(STUBBED) sceUniversalDataSystemGetPlatformError(%p, %lld)\n", error, four);
	*error = 0;
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemGetStorageStat(int context, void* out) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (context == -1) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_CONTEXT;
	}
	if (!out) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_PARAM;
	}
	printf("(STUBBED) sceUniversalDataSystemGetStorageStat(%d, %p)\n", context, out);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemPostEvent(int context, int handle, void* event, int* unknown4) {
	if (!g_udsInitialized) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_NOT_INITIALIZED;
	}
	if (context == -1) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_CONTEXT;
	}
	if (handle == -1) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_HANDLE;
	}
	if (!event) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_EVENT;
	}
	printf("(STUBBED) sceUniversalDataSystemPostEvent(%d, %d, %p, %p)\n", context, handle, event, unknown4);
	*unknown4 = 0x12345678;
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpUniversalDataSystemRegisterContext(int context, int handle, int zero) {
	if (context == -1) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_CONTEXT;
	}
	if (zero != 0) {
		return SCE_ERROR_NP_UNIVERSAL_DATA_SYSTEM_INVALID_PARAM;
	}
	printf("(STUBBED) sceUniversalDataSystemRegisterContext(%d, %d, %d)\n", context, handle, zero);
	return SCE_OK;
}

void np_uds_reset() {
	g_udsInitialized = false;
}
