/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#pragma once

#include <stdint.h>

struct SceNpPremiumInfo {
	int64_t unknown;
	int64_t unknown2;
	int64_t unknown3;
	int64_t unknown4;
	char reserved[0x18];
};

void np_reset();
