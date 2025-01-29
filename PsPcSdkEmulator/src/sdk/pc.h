/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#pragma once

#include <stdint.h>

typedef uint32_t ScePsPcPropertyType;

#define SCE_PSPC_PROPERTY_TYPE_STRING 0
#define SCE_PSPC_PROPERTY_TYPE_INT 1
#define SCE_PSPC_PROPERTY_TYPE_BOOL 2
#define SCE_PSPC_PROPERTY_TYPE_DATA 3

typedef struct ScePsPcProperty {
	const char* name;
	ScePsPcPropertyType type;
	union {
		char* string;
		int integer;
		bool boolean;
		void* data;
	};
} ScePsPcProperty;	

struct ScePsPcInitializeInternalParam {
	ScePsPcProperty* properties;
	int property_count;
	uint64_t unknown1;
};
