/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#pragma once

#include <stdint.h>

#define SCE_NP_WEB_API2_MAX_CONTEXTS 0X7fff

struct SceNpNpWebApi2ContextNode {
	int16_t context = 0;
	SceNpNpWebApi2ContextNode* next = nullptr;
};

void np_web_api2_reset();
