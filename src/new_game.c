#include "global.h"
#include "gflib.h"
#include "random.h"
#include "overworld.h"
#include "constants/maps.h"
#include "load_save.h"
#include "item_menu.h"
#include "tm_case.h"
#include "berry_pouch.h"
#include "clock.h"
#include "quest_log.h"
#include "wild_encounter.h"
#include "event_data.h"
#include "mail.h"
#include "play_time.h"
#include "money.h"
#include "battle_records.h"
#include "pokemon_size_record.h"
#include "pokemon_storage_system.h"
#include "roamer.h"
#include "item.h"
#include "player_pc.h"
#include "berry.h"
#include "easy_chat.h"
#include "union_room_chat.h"
#include "mystery_gift.h"
#include "renewable_hidden_items.h"
#include "trainer_tower.h"
#include "script.h"
#include "berry_powder.h"
#include "pokemon_jump.h"
#include "event_scripts.h"
#include "save.h"
#include "rtc.h"
#include "random_encounters.h"
#include "constants/game_modes.h"
#include "constants/species.h"

// this file's functions
static void ResetMiniGamesResults(void);
static void ResetItemFlags(void);
static void ResetDexNav(void);

// EWRAM vars
EWRAM_DATA bool8 gDifferentSaveFile = FALSE;

void SetTrainerId(u32 trainerId, u8 *dst)
{
    dst[0] = trainerId;
    dst[1] = trainerId >> 8;
    dst[2] = trainerId >> 16;
    dst[3] = trainerId >> 24;
}

void CopyTrainerId(u8 *dst, u8 *src)
{
    s32 i;
    for (i = 0; i < 4; i++)
        dst[i] = src[i];
}

static void InitPlayerTrainerId(void)
{
    if (gSaveBlock2Ptr->customData.gameMode == GAME_MODE_ESCAPE_ROOM)
    {
        SetTrainerId(42069, gSaveBlock2Ptr->playerTrainerId);
        return;
    }
    u32 trainerId = (Random() << 0x10) | GetGeneratedTrainerIdLower();
    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
}

static void SetDefaultOptions(void)
{
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_FAST;
    gSaveBlock2Ptr->optionsWindowFrameType = 0;
    gSaveBlock2Ptr->optionsSound = OPTIONS_SOUND_MONO;
    gSaveBlock2Ptr->optionsBattleStyle = OPTIONS_BATTLE_STYLE_SET;
    gSaveBlock2Ptr->optionsBattleSceneOff = FALSE;
    gSaveBlock2Ptr->regionMapZoom = FALSE;
    gSaveBlock2Ptr->optionsButtonMode = OPTIONS_BUTTON_MODE_HELP;
}

static void ClearPokedexFlags(void)
{
    memset(&gSaveBlock1Ptr->dexCaught, 0, sizeof(gSaveBlock1Ptr->dexCaught));
    memset(&gSaveBlock1Ptr->dexSeen, 0, sizeof(gSaveBlock1Ptr->dexSeen));
}

static void ClearBattleTower(void)
{
}

static void WarpToPlayersRoom(void)
{
    SetWarpDestination(MAP_GROUP(MAP_PALLET_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(MAP_PALLET_TOWN_PLAYERS_HOUSE_2F), -1, 6, 6);
    WarpIntoMap();
}

static void WarpToEscapeRoom(void)
{
    SetWarpDestination(MAP_GROUP(MAP_ESCAPE_ROOM), MAP_NUM(MAP_ESCAPE_ROOM), 0, 0, 0);
    WarpIntoMap();
}

void Sav2_ClearSetDefault(void)
{
    ClearSav2();
    SetDefaultOptions();
}

void ResetMenuAndMonGlobals(void)
{
    gDifferentSaveFile = FALSE;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetBagScrollPositions();
    ResetTMCaseCursorPos();
    BerryPouch_CursorResetToTop();
    ResetQuestLog();
    SeedWildEncounterRng(Random());
    ResetSpecialVars();
}

void NewGameInitData(void)
{
    u16 i;
    u8 rivalName[PLAYER_NAME_LENGTH + 1];

    if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_INVALID)
        RtcReset();

    StringCopy(rivalName, gSaveBlock1Ptr->rivalName);
    gDifferentSaveFile = TRUE;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ClearBattleTower();
    ClearSav1();
    ClearSav3();
    ClearMailData();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    gSaveBlock2Ptr->gcnLinkFlags = 0;
    gSaveBlock2Ptr->unkFlag1 = TRUE;
    gSaveBlock2Ptr->unkFlag2 = FALSE;
    InitPlayerTrainerId();
    PlayTimeCounter_Reset();
    ClearPokedexFlags();
    InitEventData();
    InitTimeBasedEvents(); // remove if wallclock
    ResetFameChecker();
    if (gSaveBlock2Ptr->customData.gameMode < 128)
    {
        SetMoney(&gSaveBlock1Ptr->money, 3000);
    }
    else
    {
        SetMoney(&gSaveBlock1Ptr->money, 0);
    }
    ResetGameStats();
    ClearPlayerLinkBattleRecords();
    InitHeracrossSizeRecord();
    InitMagikarpSizeRecord();
    EnableNationalPokedex_RSE();
    EnableNationalPokedex();
    gPlayerPartyCount = 0;
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    DeactivateAllRoamers();
    gSaveBlock1Ptr->registeredItem = 0;
    ClearBag();

    if (gSaveBlock2Ptr->customData.gameMode < 128)
    {
        // Give starting items
        AddBagItem(ITEM_RARE_CANDY, 999);
        AddBagItem(ITEM_MAX_REPEL, 999);

        // Give starting PC items
        NewGameInitPCItems();
    }
    else if (gSaveBlock2Ptr->customData.gameMode == GAME_MODE_ESCAPE_ROOM)
    {
        // Give starting items
        AddBagItem(ITEM_POKE_DOLL,  999);
        AddBagItem(ITEM_HM_SURF,      1);

        // Give starting PC items
        NewGameInitPCItemsEscapeRoom();
    }

    // ClearEnigmaBerries();
    InitEasyChatPhrases();
    ResetTrainerFanClub();
    UnionRoomChat_InitializeRegisteredTexts();
    ResetMiniGamesResults();
    ClearMysteryGift();
    SetAllRenewableItemFlags();
    if (gSaveBlock2Ptr->customData.gameMode < 128)
    {
        WarpToPlayersRoom();
    }
    else if (gSaveBlock2Ptr->customData.gameMode == GAME_MODE_ESCAPE_ROOM)
    {
        WarpToEscapeRoom();
    }
    RunScriptImmediately(EventScript_ResetAllMapFlags);
    StringCopy(gSaveBlock1Ptr->rivalName, rivalName);
    ResetTrainerTowerResults();
    ResetItemFlags();
    ResetDexNav();
    if (gSaveBlock2Ptr->customData.gameMode < 128)
    {
        RandomEncounters_Init();
        RandomEncounters_FillAllWithRandom();
    }

    if (gSaveBlock2Ptr->customData.gameMode < 128)
    {
        // Shortcuts:
        FlagSet(FLAG_SYS_B_DASH); // Gives running shoes
        FlagSet(FLAG_GOT_TEA); // Unlocks the gate houses to Saffron
        FlagSet(FLAG_HIDE_SAFFRON_ROCKETS); // Moves the Rocket blocking the gym in Saffron
        FlagClear(FLAG_HIDE_SAFFRON_CIVILIANS); // Moves the Rocket blocking the gym in Saffron
        AddBagItem(ITEM_POKE_FLUTE, 1);
        FlagSet(FLAG_GOT_POKE_FLUTE);
        AddBagItem(ITEM_HM03, 1); // Surf
        AddBagItem(ITEM_HM05, 1); // Flash
        AddBagItem(ITEM_SECRET_KEY, 1);
        FlagSet(FLAG_HIDE_POKEMON_MANSION_B1F_SECRET_KEY); // Unlocks the gym in Cinnabar
        FlagSet(FLAG_HIDE_CERULEAN_CAVE_GUARD); // Unlocks the Cerulean Cave from the start (once you can surf)
    }
    else if (gSaveBlock2Ptr->customData.gameMode == GAME_MODE_ESCAPE_ROOM)
    {
        FlagSet(FLAG_SYS_POKEMON_GET); // Add "POKEMON" to the menu.

        // Collect all the badges:
        for (i = 0; i < NUM_BADGES; i++)
        {
            FlagSet(FLAG_BADGE01_GET + i);
        }
    }

    // Testing/debug:
    if (FALSE) // For easy testing, change this to TRUE.
    {
        for (i = 0; i < NUM_BADGES; i++)
        {
            FlagSet(FLAG_BADGE01_GET + i);
        }
        for (i = FLAG_DEFEATED_BROCK; i < FLAG_DEFEATED_LORELEI; i++)
        {
            FlagSet(i);
        }
        for (i = FLAG_WORLD_MAP_PALLET_TOWN; i <= FLAG_WORLD_MAP_BIRTH_ISLAND_EXTERIOR; i++)
        {
            FlagSet(i);
        }
    }
}

static void ResetMiniGamesResults(void)
{
    CpuFill16(0, &gSaveBlock2Ptr->berryCrush, sizeof(struct BerryCrush));
    SetBerryPowder(&gSaveBlock2Ptr->berryCrush.berryPowderAmount, 0);
    ResetPokemonJumpRecords();
    CpuFill16(0, &gSaveBlock2Ptr->berryPick, sizeof(struct BerryPickingResults));
}

static void ResetItemFlags(void)
{
#if OW_SHOW_ITEM_DESCRIPTIONS == OW_ITEM_DESCRIPTIONS_FIRST_TIME
    memset(&gSaveBlock3Ptr->itemFlags, 0, sizeof(gSaveBlock3Ptr->itemFlags));
#endif
}

static void ResetDexNav(void)
{
#if USE_DEXNAV_SEARCH_LEVELS == TRUE
    memset(gSaveBlock3Ptr->dexNavSearchLevels, 0, sizeof(gSaveBlock3Ptr->dexNavSearchLevels));
#endif
    gSaveBlock3Ptr->dexNavChain = 0;
}
