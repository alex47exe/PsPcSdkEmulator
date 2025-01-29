/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#pragma once

#include <stdint.h>

struct SceNpUniversalDataSystemInitParams {
	uint64_t size; // apparently always 0x118
	uint64_t unknown2; // non-zero
	char path[272];
};

void np_uds_reset();
