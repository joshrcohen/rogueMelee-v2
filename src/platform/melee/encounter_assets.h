#ifndef ROGUE_ENCOUNTER_ASSETS_H
#define ROGUE_ENCOUNTER_ASSETS_H
#include <Runtime/platform.h>
int Rogue_AnimationArchiveLoad(int kind, void** data, size_t* size);
void Rogue_EncounterAssetsRelease(void);
#endif
