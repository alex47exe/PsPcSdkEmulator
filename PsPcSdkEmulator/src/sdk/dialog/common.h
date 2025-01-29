/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#pragma once

#include <stdint.h>
#include <Windows.h>

typedef uint32_t SceDialogStatus;

#define SCE_DIALOG_STATUS_NOT_INITIALIZED 0
#define SCE_DIALOG_STATUS_INITIALIZED 1
#define SCE_DIALOG_STATUS_RUNNING 2
#define SCE_DIALOG_STATUS_FINISHED 3

extern bool g_common_dialog_initialized;
extern bool g_common_dialog_busy;

struct SceDialogCommonParam {
	uint64_t unknown0;
	HWND* hwnd;
	char reserved[36];
	int check;
};

void common_dialog_reset();
