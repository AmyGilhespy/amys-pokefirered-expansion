#include "global.h"
#include "battle.h"
#include "game_modes.h"

bool32 GameModeAllBallsAreMasterBalls(void)
{
    return GameModeIsDeterministic();
}

bool32 GameModeCannotReviveDeadPokemon(void)
{
    return gSaveBlock2Ptr->customData.gameMode > 1 && gSaveBlock2Ptr->customData.gameMode < 128;
}

bool32 GameModeCannotUseFullRestoreInBattle(void)
{
    return gSaveBlock2Ptr->customData.gameMode > 1 && gSaveBlock2Ptr->customData.gameMode < 128;
}

bool32 GameModeCannotUseRevivalItemsInBattle(void)
{
    return gSaveBlock2Ptr->customData.gameMode > 1 && gSaveBlock2Ptr->customData.gameMode < 128;
}

bool32 GameModeCannotUseRevivalItemsOutOfBattle(void)
{
    return gSaveBlock2Ptr->customData.gameMode > 1 && gSaveBlock2Ptr->customData.gameMode < 128;
}

bool32 GameModeFaintedPokemonDie(void)
{
    return gSaveBlock2Ptr->customData.gameMode > 1 && gSaveBlock2Ptr->customData.gameMode < 128;
}

bool32 GameModeFirstRivalBattleIsRigged(void)
{
    return GameModeFaintedPokemonDie();
}

bool32 GameModeHasEntirelyHandCraftedBattles(void)
{
    return gSaveBlock2Ptr->customData.gameMode >= 128;
}

bool32 GameModeHasEntirelyPPMaxedMoves(void)
{
    return gSaveBlock2Ptr->customData.gameMode == GAME_MODE_ESCAPE_ROOM;
}

bool32 GameModeHasLimitedSpawns(void)
{
    return gSaveBlock2Ptr->customData.gameMode > 0 && gSaveBlock2Ptr->customData.gameMode < 128;
}

bool32 GameModeHasRandomWildEncounters(void)
{
    return gSaveBlock2Ptr->customData.gameMode < 128;
}

bool32 GameModeHasStaticPlayerTrainerID(void)
{
    return GameModeIsDeterministic();
}

bool32 GameModeIsDeterministic(void)
{
    return gSaveBlock2Ptr->customData.gameMode == GAME_MODE_ESCAPE_ROOM;
}

bool32 GameModeKeepStolenTrainerItems(void)
{
    return gSaveBlock2Ptr->customData.gameMode == GAME_MODE_ESCAPE_ROOM;
}

bool32 GameModeSpawnInPalletTown(void)
{
    return gSaveBlock2Ptr->customData.gameMode < 128;
}

bool32 GameModeStandardizesStolenPokemonLevelsTo20(void)
{
    return gSaveBlock2Ptr->customData.gameMode == GAME_MODE_ESCAPE_ROOM;
}

bool32 GameModeStartsWithAll8Badges(void)
{
    return gSaveBlock2Ptr->customData.gameMode == GAME_MODE_ESCAPE_ROOM;
}

bool32 GameModeStartsWithPokemonMenuItem(void)
{
    return gSaveBlock2Ptr->customData.gameMode == GAME_MODE_ESCAPE_ROOM;
}

bool32 GameModeStartWith3000Money(void)
{
    return gSaveBlock2Ptr->customData.gameMode < 128;
}

bool32 GameModeStartWithDash(void)
{
    return TRUE;
}

bool32 GameModeStartWithStandardPCItems(void)
{
    return gSaveBlock2Ptr->customData.gameMode < 128;
}

bool32 GameModeStartWithStandardQoLFlags(void)
{
    return gSaveBlock2Ptr->customData.gameMode < 128;
}

bool32 GameModeStartWithStandardQoLItems(void)
{
    return gSaveBlock2Ptr->customData.gameMode < 128;
}
