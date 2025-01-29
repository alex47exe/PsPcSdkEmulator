/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#pragma once

#include "sceerror.h"
#include <stdio.h>

#define PSPCSDK_API extern "C" __declspec(dllexport)

#define PSPCSDK_STUB(name) PSPCSDK_API SceResult name() {printf("(STUBBED) " #name "()\n");return SCE_OK;}
