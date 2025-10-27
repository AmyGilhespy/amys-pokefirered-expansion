#include "global.h"
#include "random_encounters.h"
#include "constants/random_encounters.h"
#include "constants/species.h"

static void FillRegionWithSpecies(u8 regionId, u16 species);

void RandomEncounters_FillAllWithSpecies(u16 species)
{
    s32 region, slot;
    for (region = 0; region < RANDOM_ENCOUNTER_REGION_COUNT; ++region)
    {
        for (slot = 0; slot < RANDOM_ENCOUNTER_SLOTS_PER_REGION; ++slot) {
            gSaveBlock2Ptr->randomEncounterData.randomEncounters[region][slot] = species;
        }
    }
}

/**
 * Return the species for a given region and slot (0..RANDOM_ENCOUNTER_SLOTS_PER_REGION-1).
 * If the entry is invalid, returns RANDOM_ENCOUNTER_SPECIES_NONE.
 */
u16 RandomEncounters_GetSpeciesForRegionSlot(u8 regionId, u8 slot)
{
    if (regionId >= RANDOM_ENCOUNTER_REGION_COUNT) {
        return RANDOM_ENCOUNTER_SPECIES_NONE;
    }
    if (slot >= RANDOM_ENCOUNTER_SLOTS_PER_REGION) {
        return RANDOM_ENCOUNTER_SPECIES_NONE;
    }
    return gSaveBlock2Ptr->randomEncounterData.randomEncounters[regionId][slot];
}

/**
 * Helper: get species array for regionId into outSpecies pointer (size RANDOM_ENCOUNTER_SLOTS_PER_REGION).
 * Returns TRUE if valid; FALSE if uninitialized.
 */
bool8 RandomEncounters_GetSpeciesArrayForRegion(u8 regionId, u16 *outSpecies)
{
    s32 i;
    if (regionId >= RANDOM_ENCOUNTER_REGION_COUNT) {
        return FALSE;
    }

    for (i = 0; i < RANDOM_ENCOUNTER_SLOTS_PER_REGION; ++i) {
        outSpecies[i] = gSaveBlock2Ptr->randomEncounterData.randomEncounters[regionId][i];
    }
    return TRUE;
}

static void FillRegionWithSpecies(u8 regionId, u16 species)
{
    s32 i;
    if (regionId >= RANDOM_ENCOUNTER_REGION_COUNT) {
        return;
    }
    for (i = 0; i < RANDOM_ENCOUNTER_SLOTS_PER_REGION; ++i) {
        gSaveBlock2Ptr->randomEncounterData.randomEncounters[regionId][i] = species;
    }
}

