/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#pragma once

#include "common.h"

struct SceSigninDialogParam {
	SceDialogCommonParam common;
	int unknown0;
	int desired_user_id;
	void* unknown1;
	char reserved[8];
};

struct SceSigninDialogResult {
	int error;
	int user_id;
	uint64_t account_id;
	char reserved[8];
};

void signin_dialog_reset();
