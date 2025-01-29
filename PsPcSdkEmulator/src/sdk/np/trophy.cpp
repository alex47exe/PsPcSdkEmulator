/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "../sce.h"

PSPCSDK_API SceResult sceNpTrophy2CreateContext(int* unknown1, int unknown2, uint32_t unknown3, uint64_t unknown4) {
	// Invalid param checking
	printf("(STUBBED) sceNpTrophy2CreateContext(%p, %x, %x, %llx)\n", unknown1, unknown2, unknown3, unknown4);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpTrophy2DestroyContext(int unknown1) {
	// Invalid param checking
	printf("(STUBBED) sceNpTrophy2DestroyContext(%d)\n", unknown1);
	return SCE_OK;
}

PSPCSDK_API SceResult sceNpTrophy2ShowTrophyList(void* unknown1, int unknown2) {
	// Invalid param checking
	printf("(STUBBED) sceNpTrophy2ShowTrophyList(%p, %d)\n", unknown1, unknown2);
	return SCE_OK;
}
