#ifndef GUARD_RANDOM_ENCOUNTERS_H
#define GUARD_RANDOM_ENCOUNTERS_H

#include "constants/random_encounters.h"
#include "global.h"

void RandomEncounters_FillAllWithSpecies(u16 species);
u16 RandomEncounters_GetSpeciesForRegionSlot(u8 regionId, u8 slot);
bool8 RandomEncounters_GetSpeciesArrayForRegion(u8 regionId, u16 *outSpecies);

#endif // GUARD_RANDOM_ENCOUNTERS_H

