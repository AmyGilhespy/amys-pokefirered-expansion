#include "gba/gba.h"
#include "global.h"
#include "malloc.h"
#include "overworld.h"
#include "random.h"
#include "random_encounters.h"
#include "rtc.h"
#include "wild_encounter.h"
#include "constants/random_encounters.h"
#include "constants/species.h"

EWRAM_DATA static u16 sRandomEncounters_RegionTargetBST[RANDOM_ENCOUNTER_REGION_COUNT] = {0};
EWRAM_DATA static u16 * sRandomEncounters_ValidSpecies;
EWRAM_DATA static u16 sRandomEncounters_ValidSpeciesCount;

u16 RandomEncounters_ChooseRandomSpeciesForRegion(s32 regionId, u16 avoid1, u16 avoid2)
{
    const u16 target = sRandomEncounters_RegionTargetBST[regionId];
    const u16 attempts = 20;
    u16 bestSpecies = SPECIES_RATTATA; // fallback guaranteed valid
    u16 bestScore = 0xFFFF;
    u16 i = 0;
    u16 species, bst, score;

    for (i = 0; i < attempts; i++)
    {
        species = RandomEncounters_PickRandomValidSpecies();
        bst = gSpeciesInfo[species].baseHP
                + gSpeciesInfo[species].baseAttack
                + gSpeciesInfo[species].baseDefense
                + gSpeciesInfo[species].baseSpeed
                + gSpeciesInfo[species].baseSpAttack
                + gSpeciesInfo[species].baseSpDefense;

        score = abs((s16) bst - (s16) target);
        if (score < bestScore)
        {
            bestScore = score;
            bestSpecies = species;
        }
    }

    return bestSpecies;
}

void RandomEncounters_FillAllWithRandom(void)
{
    s32 regionId, slot;
    u16 species0, species1, species2plus;
    for (regionId = 0; regionId < RANDOM_ENCOUNTER_REGION_COUNT; ++regionId)
    {
        if (0 < RANDOM_ENCOUNTER_SLOTS_PER_REGION)
        {
            species0 = RandomEncounters_ChooseRandomSpeciesForRegion(regionId, SPECIES_NONE, SPECIES_NONE);
            gSaveBlock2Ptr->randomEncounterData.randomEncounters[regionId][0] = species0;
        }
        if (1 < RANDOM_ENCOUNTER_SLOTS_PER_REGION)
        {
            species1 = RandomEncounters_ChooseRandomSpeciesForRegion(regionId, species0, SPECIES_NONE);
            gSaveBlock2Ptr->randomEncounterData.randomEncounters[regionId][1] = species1;
        }
        for (slot = 2; slot < RANDOM_ENCOUNTER_SLOTS_PER_REGION; ++slot)
        {
            species2plus = RandomEncounters_ChooseRandomSpeciesForRegion(regionId, species0, species1);
            gSaveBlock2Ptr->randomEncounterData.randomEncounters[regionId][slot] = species2plus;
        }
    }
    free(sRandomEncounters_ValidSpecies);
}

void RandomEncounters_FillAllWithSpecies(u16 species)
{
    s32 regionId, slot;
    for (regionId = 0; regionId < RANDOM_ENCOUNTER_REGION_COUNT; ++regionId)
    {
        for (slot = 0; slot < RANDOM_ENCOUNTER_SLOTS_PER_REGION; ++slot) {
            gSaveBlock2Ptr->randomEncounterData.randomEncounters[regionId][slot] = species;
        }
    }
}

/**
 * Return the species for a given region and slot (0..RANDOM_ENCOUNTER_SLOTS_PER_REGION-1).
 * If the entry is invalid, returns RANDOM_ENCOUNTER_SPECIES_NONE.
 */
u16 RandomEncounters_GetSpeciesForRegionSlot(u16 regionId, u8 slot)
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
bool8 RandomEncounters_GetSpeciesArrayForRegion(u16 regionId, u16 *outSpecies)
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

void RandomEncounters_Init(void)
{
    u32 * bst_num;
    u16 * bst_div;
    s32 i;
    u16 species, bst, regionId;
    u8 wildMonIndex, season, timeOfDay;
    // Init the valid species list:
    sRandomEncounters_ValidSpecies = calloc(NUM_SPECIES, sizeof(u16));
    sRandomEncounters_ValidSpeciesCount = 0;
    for (species = 1; species < NUM_SPECIES; ++species)
    {
        if (RandomEncounters_IsAllowedSpecies(species))
        {
            sRandomEncounters_ValidSpecies[sRandomEncounters_ValidSpeciesCount++] = species;
        }
    }
    // Init the region BST targets:
    bst_num = (u32 *) calloc(RANDOM_ENCOUNTER_REGION_COUNT, sizeof(u32));
    bst_div = (u16 *) calloc(RANDOM_ENCOUNTER_REGION_COUNT, sizeof(u16));
    for (i = 0; gWildMonHeaders[i].mapGroup != MAP_GROUP(MAP_UNDEFINED); ++i)
    {
        regionId = Overworld_GetMapHeaderByGroupAndId(gWildMonHeaders[i].mapGroup, gWildMonHeaders[i].mapNum)->regionMapSectionId;
        if (regionId >= RANDOM_ENCOUNTER_REGION_COUNT) {
            continue;
        }
        for (season = 0; season < (OW_SEASON_ENCOUNTERS ? SEASON_COUNT : 1); ++season)
        {
            for (timeOfDay = 0; timeOfDay < (OW_TIME_OF_DAY_ENCOUNTERS ? TIMES_OF_DAY_COUNT : 1); ++timeOfDay)
            {
                if (gWildMonHeaders[i].encounterTypes[season][timeOfDay].landMonsInfo == NULL)
                {
                    continue;
                }
                for (wildMonIndex = 0; wildMonIndex < 1/*2*/; wildMonIndex++)
                {
                    species = gWildMonHeaders[i].encounterTypes[season][timeOfDay].landMonsInfo->wildPokemon[wildMonIndex].species;
                    if (species == SPECIES_NONE || species < 0 || species >= NUM_SPECIES) {
                        continue;
                    }
                    bst = gSpeciesInfo[species].baseHP
                            + gSpeciesInfo[species].baseAttack
                            + gSpeciesInfo[species].baseDefense
                            + gSpeciesInfo[species].baseSpeed
                            + gSpeciesInfo[species].baseSpAttack
                            + gSpeciesInfo[species].baseSpDefense;
                    bst_num[regionId] += bst;
                    bst_div[regionId]++;
                }
            }
        }
    }
    for (regionId = 0; regionId < RANDOM_ENCOUNTER_REGION_COUNT; ++regionId)
    {
        if (bst_div[regionId] > 0)
        {
            sRandomEncounters_RegionTargetBST[regionId] = bst_num[regionId] / bst_div[regionId];
        }
        else
        {
            sRandomEncounters_RegionTargetBST[regionId] = 275;
        }
    }
    free(bst_num);
    free(bst_div);
}

bool8 RandomEncounters_IsAllowedSpecies(u16 species)
{
    if (species == SPECIES_NONE)
    {
        return FALSE;
    }

    if (gSpeciesInfo[species].isLegendary)
    {
        return FALSE;
    }

    if (gSpeciesInfo[species].isMythical)
    {
        return FALSE;
    }

    if (gSpeciesInfo[species].isUltraBeast)
    {
        return FALSE;
    }

    if (gSpeciesInfo[species].isParadox)
    {
        return FALSE;
    }

    if (gSpeciesInfo[species].isTotem)
    {
        return FALSE;
    }

    if (gSpeciesInfo[species].isMegaEvolution)
    {
        return FALSE;
    }

    if (gSpeciesInfo[species].isPrimalReversion)
    {
        return FALSE;
    }

    if (gSpeciesInfo[species].isUltraBurst)
    {
        return FALSE;
    }

    if (gSpeciesInfo[species].isGigantamax)
    {
        return FALSE;
    }

    if (gSpeciesInfo[species].isTeraForm)
    {
        return FALSE;
    }

    return TRUE;
}

u16 RandomEncounters_PickRandomValidSpecies(void)
{
    return sRandomEncounters_ValidSpecies[Random() % sRandomEncounters_ValidSpeciesCount];
}

