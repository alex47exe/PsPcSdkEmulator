/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "webapi2.h"

#include "../sce.h"
#include <Windows.h>

static SceNpNpWebApi2ContextNode g_contexts;
static int g_context_count = 0;

static SceNpNpWebApi2ContextNode* find_context(int16_t context) {
	SceNpNpWebApi2ContextNode* node = &g_contexts;
	while (node->next != nullptr) {
		if (node->context == context) {
			return node;
		}
		node = node->next;
	}
	return nullptr;
}

PSPCSDK_API SceResult sceNpWebApi2Initialize(int16_t context) {
	if (g_context_count >= SCE_NP_WEB_API2_MAX_CONTEXTS) {
		return SCE_ERROR_NP_WEB_API2_FULL_CONTEXT_POOL;
	}
	SceNpNpWebApi2ContextNode* last_node = &g_contexts;
	while (last_node->next != nullptr) {
		last_node = last_node->next;
	}
	last_node->next = new SceNpNpWebApi2ContextNode();
	last_node->context = context;
	g_context_count++;
	printf("(STUBBED) sceNpWebApi2Initialize(%hd)\n", context);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2Terminate(int16_t context) {
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	SceNpNpWebApi2ContextNode* next = node->next;
	node->next = next->next;
	node->context = next->context;
	delete next;
	g_context_count--;
	printf("(STUBBED) sceNpWebApi2Terminate(%hd)\n", context);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2CreateUserContext(int16_t context, int user) {
	if (context == -1) {
		return SCE_ERROR_NP_WEB_API2_INVALID_CONTEXT;
	}
	if (user == -1) {
		return SCE_ERROR_NP_WEB_API2_INVALID_USER;
	}
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2CreateUserContext(%hd, %d)\n", context, user);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2DeleteUserContext(int context_and_user) {
	int context = context_and_user >> 16;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2DeleteUserContext(%d)\n", context_and_user);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2CreateRequest(int data, void* unknown2, void* unknown3, void* unknown4, void* unknown5, void* unknown6) {
	if (!unknown2 || !unknown3 || !unknown4) {
		return SCE_ERROR_NP_WEB_API2_INVALID_PARAM;
	}
	int context = data >> 16;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2CreateRequest(%d, %p, %p, %p, %p, %p)\n", data, unknown2, unknown3, unknown4, unknown5, unknown6);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2DeleteRequest(uint64_t data) {
	int context = data >> 48;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2DeleteRequest(%llx)\n", data);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2DeleteContext(uint64_t data) {
	int context = data >> 48;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2DeleteContext(%llx)\n", data);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2AbortRequest(uint64_t data) {
	int context = data >> 48;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2AbortRequest(%llx)\n", data);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2CheckTimeout() {
	printf("(STUBBED) sceNpWebApi2CheckTimeout()\n");
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2AddHttpRequestHeader(uint64_t data, const char* key, const char* value) {
	if (!key || !value) {
		return SCE_ERROR_NP_WEB_API2_INVALID_PARAM;
	}
	int context = data >> 48;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2AddHttpRequestHeader(%llx, %s, %s)\n", data, key, value);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2GetHttpResponseHeaderValue(uint64_t data, const char* key, char* value, uint64_t* value_size) {
	if (!key || !value || !value_size) {
		return SCE_ERROR_NP_WEB_API2_INVALID_PARAM;
	}
	int context = data >> 48;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2GetHttpResponseHeaderValue(%llx, %s, %p, %p)\n", data, key, value, value_size);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2GetHttpResponseHeaderValueLength(uint64_t data, char* key, uint64_t* length) {
	if (!key || !length) {
		return SCE_ERROR_NP_WEB_API2_INVALID_PARAM;
	}
	int context = data >> 48;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2GetHttpResponseHeaderValueLength(%llx, %s, %p)\n", data, key, length);
	return SCE_OK;
}

PSPCSDK_API	SceResult sceNpWebApi2SetRequestTimeout(uint64_t data, uint64_t timeout) {
	int context = data >> 48;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2SetRequestTimeout(%llx, %llx)\n", data, timeout);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2ReadData(uint64_t data, void* buffer, uint64_t* size) {
	if (!buffer || !size) {
		return SCE_ERROR_NP_WEB_API2_INVALID_PARAM;
	}
	int context = data >> 48;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2ReadData(%llx, %p, %p)\n", data, buffer, size);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2SendRequest(uint64_t data, void* unused, void* unknown3, void* unknown4, void* unknown5) {
	int context = data >> 48;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2SendRequest(%llx, %p, %p, %p, %p)\n", data, unused, unknown3, unknown4, unknown5);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2GetMemoryPoolStats(uint16_t context, void* out) {
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2GetMemoryPoolStats(%d, %p)\n", context, out);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2GetPlatformError(uint64_t data, HRESULT* error, uint64_t four) {
	if (!error || four != 4) {
		return SCE_ERROR_NP_WEB_API2_INVALID_PARAM;
	}
	int context = 0;
	if ((data & 0xffffffffffff0000) == 0) {
		context = (int) (data >> 16);
	} else if ((data & 0xffffffff00000000) == 0 && (data & 0xffff0000) != 0) {
		context = (int) (data >> 32);
	} else {
		context = (int) (data >> 48);
	}
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2GetPlatformError(%llx, %p, %llx)\n", data, error, four);
	*error = 0;
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2PushEventCreatePushContext(int data, void* push_context) {
	if (!push_context) {
		return SCE_ERROR_NP_WEB_API2_INVALID_PARAM;
	}
	int context = data >> 16;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2PushEventCreatePushContext(%d, %p)\n", data, push_context);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2PushEventDeletePushContext(int data, void* push_context) {
	if (!push_context) {
		return SCE_ERROR_NP_WEB_API2_INVALID_PARAM;
	}
	int context = data >> 16;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2PushEventDeletePushContext(%d, %p)\n", data, push_context);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2PushEventCreateHandle(uint16_t context) {
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2PushEventCreateHandle(%d)\n", context);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2PushEventDeleteHandle(uint16_t context, int handle) {
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2PushEventDeleteHandle(%d, %d)\n", context, handle);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2PushEventAbortHandle(uint16_t context, int handle) {
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2PushEventAbortHandle(%d, %d)\n", context, handle);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2PushEventSetHandleTimeout(uint16_t context, int handle, uint64_t timeout) {
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2PushEventSetHandleTimeout(%d, %d, %llx)\n", context, handle, timeout);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2PushEventCreateFilter(uint16_t context, void* unknown2, uint64_t unknown3, int64_t unknown4, void* unknown5, void* unknown6) {
    if ((unknown3 && unknown4 != -1) || !unknown5 || !unknown6) {
		return SCE_ERROR_NP_WEB_API2_INVALID_PARAM;
	}
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2PushEventCreateFilter(%d, %p, %llx, %llx, %p, %p)\n", context, unknown2, unknown3, unknown4, unknown5, unknown6);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2PushEventDeleteFilter(uint16_t context, int filter) {
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2PushEventDeleteFilter(%d, %d)\n", context, filter);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2PushEventGetPlatformError(uint16_t context, int handle, HRESULT* error, uint64_t four) {
	if (!error || four != 4) {
		return SCE_ERROR_NP_WEB_API2_INVALID_PARAM;
	}
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2PushEventGetPlatformError(%d, %d, %p, %llx)\n", context, handle, error, four);
	*error = 0;
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2PushEventRegisterCallback(int data, int handle, void* callback, void* userdata) {
	if (!callback) {
		return SCE_ERROR_NP_WEB_API2_INVALID_PARAM;
	}
	int context = data >> 16;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2PushEventRegisterCallback(%d, %d, %p, %p)\n", data, handle, callback, userdata);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2PushEventUnregisterCallback(int data, int handle) {
	int context = data >> 16;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2PushEventUnregisterCallback(%d, %d)\n", data, handle);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2PushEventRegisterPushContextCallback(int data, int push_context, void* callback, void* userdata) {
	if (!callback) {
		return SCE_ERROR_NP_WEB_API2_INVALID_PARAM;
	}
	int context = data >> 16;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2PushEventRegisterPushContextCallback(%d, %d, %p, %p)\n", data, push_context, callback, userdata);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpWebApi2PushEventUnregisterPushContextCallback(int data, int push_context) {
	int context = data >> 16;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2PushEventUnregisterPushContextCallback(%d, %d)\n", data, push_context);
	return SCE_OK;
}

PSPCSDK_API	SceResult sceNpWebApi2PushEventStartPushContextCallback(int data, void* unknown2) {
	if (!unknown2) {
		return SCE_ERROR_NP_WEB_API2_INVALID_PARAM;
	}
	int context = data >> 16;
	SceNpNpWebApi2ContextNode* node = find_context(context);
	if (node == nullptr) {
		return SCE_ERROR_NP_WEB_API2_CONTEXT_NOT_INITIALIZED;
	}
	printf("(STUBBED) sceNpWebApi2PushEventStartPushContextCallback(%d, %p)\n", data, unknown2);
	return SCE_OK;
}

void np_web_api2_reset() {
	SceNpNpWebApi2ContextNode* node = g_contexts.next;
	while (node != nullptr) {
		SceNpNpWebApi2ContextNode* next = node->next;
		delete node;
		node = next;
	}
	g_contexts.next = nullptr;
	g_context_count = 0;
}
