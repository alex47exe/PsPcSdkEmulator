/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#pragma once
#include <stdint.h>

typedef uint32_t SceNpState;

struct SceNpOnlineId {
	char name[16];
	char term;
	char reserved[3];
};

#define SCE_NP_STATUS_UNKNOW 0x0
#define SCE_NP_STATUS_LOGGED_OUT 0x1
#define SCE_NP_STATUS_LOGGED_IN 0x2
