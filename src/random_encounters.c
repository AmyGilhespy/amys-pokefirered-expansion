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
//#include "gba/isagbprint.h"

EWRAM_DATA static u16 sRandomEncounters_RegionTargetBST[RANDOM_ENCOUNTER_REGION_COUNT] = {0};
EWRAM_DATA static u16 sRandomEncounters_ValidSpecies[NUM_SPECIES];
EWRAM_DATA static u16 sRandomEncounters_ValidSpeciesCount;
EWRAM_DATA static u16 sRandomEncounters_ValidStarterSpeciesCount;
EWRAM_DATA static u16 * sRandomEncounters_ValidStarterSpecies;

u16 RandomEncounters_ChooseRandomSpeciesForBST(u16 targetBST, u16 avoid1, u16 avoid2)
{
    const u16 attempts = 20;
    u16 bestSpecies = SPECIES_RATTATA; // fallback guaranteed valid
    u16 bestScore = 0xFFFF;
    u16 i = 0;
    u16 species, bst, score;

    for (i = 0; i < attempts; i++)
    {
        species = RandomEncounters_PickRandomValidSpecies();
        //MgbaPrintf(MGBA_LOG_WARN, "RandomEncounters_ChooseRandomSpeciesForBST: chose %d (0x%x)", species, species);
        bst = gSpeciesInfo[species].baseHP
                + gSpeciesInfo[species].baseAttack
                + gSpeciesInfo[species].baseDefense
                + gSpeciesInfo[species].baseSpeed
                + gSpeciesInfo[species].baseSpAttack
                + gSpeciesInfo[species].baseSpDefense;

        score = abs((s16) bst - (s16) targetBST);
        if (species == avoid1 || species == avoid2)
        {
            score += 100;
        }
        if (score < bestScore)
        {
            bestScore = score;
            bestSpecies = species;
        }
    }

    return bestSpecies;
}

u16 RandomEncounters_ChooseRandomSpeciesForRegion(s32 regionId, u16 avoid1, u16 avoid2)
{
    return RandomEncounters_ChooseRandomSpeciesForBST(sRandomEncounters_RegionTargetBST[regionId], avoid1, avoid2);
}

u16 RandomEncounters_ChooseRandomSpeciesForStarter(u16 targetBST, u16 avoid1, u16 avoid2)
{
    const u16 attempts = 20;
    u16 bestSpecies = SPECIES_BULBASAUR; // fallback guaranteed valid
    u16 bestScore = 0xFFFF;
    u16 i = 0;
    u16 species, bst, score;

    for (i = 0; i < attempts; i++)
    {
        species = RandomEncounters_PickRandomValidStarterSpecies();
        bst = gSpeciesInfo[species].baseHP
                + gSpeciesInfo[species].baseAttack
                + gSpeciesInfo[species].baseDefense
                + gSpeciesInfo[species].baseSpeed
                + gSpeciesInfo[species].baseSpAttack
                + gSpeciesInfo[species].baseSpDefense;

        score = abs((s16) bst - (s16) targetBST);
        if (species == avoid1 || species == avoid2)
        {
            score += 100;
        }
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
            gSaveBlock2Ptr->customData.randomEncounters[regionId][0] = species0;
        }
        if (1 < RANDOM_ENCOUNTER_SLOTS_PER_REGION)
        {
            species1 = RandomEncounters_ChooseRandomSpeciesForRegion(regionId, species0, SPECIES_NONE);
            gSaveBlock2Ptr->customData.randomEncounters[regionId][1] = species1;
        }
        for (slot = 2; slot < RANDOM_ENCOUNTER_SLOTS_PER_REGION; ++slot)
        {
            species2plus = RandomEncounters_ChooseRandomSpeciesForRegion(regionId, species0, species1);
            gSaveBlock2Ptr->customData.randomEncounters[regionId][slot] = species2plus;
        }
    }
}

void RandomEncounters_FillAllWithSpecies(u16 species)
{
    s32 regionId, slot;
    for (regionId = 0; regionId < RANDOM_ENCOUNTER_REGION_COUNT; ++regionId)
    {
        for (slot = 0; slot < RANDOM_ENCOUNTER_SLOTS_PER_REGION; ++slot) {
            gSaveBlock2Ptr->customData.randomEncounters[regionId][slot] = species;
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
    return gSaveBlock2Ptr->customData.randomEncounters[regionId][slot];
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
        outSpecies[i] = gSaveBlock2Ptr->customData.randomEncounters[regionId][i];
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
    // Init the seed:
    gSaveBlock2Ptr->customData.seed = Random32();
    // Init the valid species list:
    sRandomEncounters_ValidSpeciesCount = 0;
    for (species = 1; species < NUM_SPECIES; ++species)
    {
        if (RandomEncounters_IsAllowedSpecies(species))
        {
            sRandomEncounters_ValidSpecies[sRandomEncounters_ValidSpeciesCount++] = species;
        }
    }
    //MgbaPrintf(MGBA_LOG_WARN, "RandomEncounters_Init: Have sRandomEncounters_ValidSpeciesCount=%d of NUM_SPECIES=%d valid species, highest of which is %d.", sRandomEncounters_ValidSpeciesCount, NUM_SPECIES, species - 1);
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
    // Init the starters:
    bst = 0
            + gSpeciesInfo[SPECIES_BULBASAUR].baseHP
            + gSpeciesInfo[SPECIES_BULBASAUR].baseAttack
            + gSpeciesInfo[SPECIES_BULBASAUR].baseDefense
            + gSpeciesInfo[SPECIES_BULBASAUR].baseSpeed
            + gSpeciesInfo[SPECIES_BULBASAUR].baseSpAttack
            + gSpeciesInfo[SPECIES_BULBASAUR].baseSpDefense
            + gSpeciesInfo[SPECIES_CHARMANDER].baseHP
            + gSpeciesInfo[SPECIES_CHARMANDER].baseAttack
            + gSpeciesInfo[SPECIES_CHARMANDER].baseDefense
            + gSpeciesInfo[SPECIES_CHARMANDER].baseSpeed
            + gSpeciesInfo[SPECIES_CHARMANDER].baseSpAttack
            + gSpeciesInfo[SPECIES_CHARMANDER].baseSpDefense
            + gSpeciesInfo[SPECIES_SQUIRTLE].baseHP
            + gSpeciesInfo[SPECIES_SQUIRTLE].baseAttack
            + gSpeciesInfo[SPECIES_SQUIRTLE].baseDefense
            + gSpeciesInfo[SPECIES_SQUIRTLE].baseSpeed
            + gSpeciesInfo[SPECIES_SQUIRTLE].baseSpAttack
            + gSpeciesInfo[SPECIES_SQUIRTLE].baseSpDefense
            ;
    bst /= 3;
    sRandomEncounters_ValidStarterSpecies = calloc(sRandomEncounters_ValidSpeciesCount, sizeof(u16));
    for (i = 0; i < sRandomEncounters_ValidSpeciesCount; ++i)
    {
        if (RandomEncounters_IsAllowedStarterSpecies(sRandomEncounters_ValidSpecies[i]))
        {
            sRandomEncounters_ValidStarterSpecies[sRandomEncounters_ValidStarterSpeciesCount++] = sRandomEncounters_ValidSpecies[i];
        }
    }
    gSaveBlock2Ptr->customData.starters[0] = RandomEncounters_ChooseRandomSpeciesForStarter(bst, SPECIES_NONE, SPECIES_NONE);
    gSaveBlock2Ptr->customData.starters[1] = RandomEncounters_ChooseRandomSpeciesForStarter(bst, gSaveBlock2Ptr->customData.starters[0], SPECIES_NONE);
    gSaveBlock2Ptr->customData.starters[2] = RandomEncounters_ChooseRandomSpeciesForStarter(bst, gSaveBlock2Ptr->customData.starters[0], gSaveBlock2Ptr->customData.starters[1]);
    free(sRandomEncounters_ValidStarterSpecies);
}

bool8 RandomEncounters_IsAllowedSpecies(u16 species)
{
    if (species >= NUM_SPECIES)
    {
        return FALSE;
    }

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

    if (gSpeciesInfo[species].formSpeciesIdTable != NULL && gSpeciesInfo[species].formSpeciesIdTable[0] != species)
    {
        return FALSE;
    }

    return TRUE;
}

bool8 RandomEncounters_IsAllowedStarterSpecies(u16 species)
{
    if (GetSpeciesPreEvolution(species) != SPECIES_NONE)
    {
        return FALSE;
    }

    const struct Evolution *evolutions = GetSpeciesEvolutions(species);
    if (evolutions == NULL || evolutions[0].method == EVOLUTIONS_END)
    {
        return FALSE;
    }

    return TRUE;
}

void RandomEncounters_Load(void)
{
    u16 species;
    // Init the valid species list:
    sRandomEncounters_ValidSpeciesCount = 0;
    for (species = 1; species < NUM_SPECIES; ++species)
    {
        if (RandomEncounters_IsAllowedSpecies(species))
        {
            sRandomEncounters_ValidSpecies[sRandomEncounters_ValidSpeciesCount++] = species;
        }
    }
    //MgbaPrintf(MGBA_LOG_WARN, "RandomEncounters_Load: Have sRandomEncounters_ValidSpeciesCount=%d of NUM_SPECIES=%d valid species, highest of which is %d.", sRandomEncounters_ValidSpeciesCount, NUM_SPECIES, species - 1);
}

u16 RandomEncounters_PickRandomValidSpecies(void)
{
    u32 rand = Random32();
    //MgbaPrintf(MGBA_LOG_WARN, "RandomEncounters_PickRandomValidSpecies: rand(%d) %% sRandomEncounters_ValidSpeciesCount(%d) => %d // NUM_SPECIES=%d", rand, sRandomEncounters_ValidSpeciesCount, rand % sRandomEncounters_ValidSpeciesCount, NUM_SPECIES);
    u16 species = sRandomEncounters_ValidSpecies[rand % (u32) sRandomEncounters_ValidSpeciesCount];
    if (species >= NUM_SPECIES)
    {
        species = SPECIES_RATTATA;
    }
    return species;
}

u16 RandomEncounters_PickRandomValidStarterSpecies(void)
{
    u32 rand = Random32();
    u16 species = sRandomEncounters_ValidStarterSpecies[rand % (u32) sRandomEncounters_ValidStarterSpeciesCount];
    if (species >= NUM_SPECIES)
    {
        species = SPECIES_BULBASAUR;
    }
    return species;
}

