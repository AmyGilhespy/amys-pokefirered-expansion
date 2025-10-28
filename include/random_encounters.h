#ifndef GUARD_RANDOM_ENCOUNTERS_H
#define GUARD_RANDOM_ENCOUNTERS_H

#include "constants/random_encounters.h"
#include "global.h"

u16 RandomEncounters_ChooseRandomSpeciesForBST(u16 targetBST, u16 avoid1, u16 avoid2);
u16 RandomEncounters_ChooseRandomSpeciesForRegion(s32 region, u16 avoid1, u16 avoid2);
void RandomEncounters_FillAllWithRandom(void);
void RandomEncounters_FillAllWithSpecies(u16 species);
u16 RandomEncounters_GetSpeciesForRegionSlot(u16 regionId, u8 slot);
bool8 RandomEncounters_GetSpeciesArrayForRegion(u16 regionId, u16 *outSpecies);
void RandomEncounters_Init(void);
bool8 RandomEncounters_IsAllowedSpecies(u16 species);
void RandomEncounters_Load(void);
u16 RandomEncounters_PickRandomValidSpecies(void);

#endif // GUARD_RANDOM_ENCOUNTERS_H

