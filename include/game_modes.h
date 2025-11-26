#ifndef GUARD_GAME_MODES_H
#define GUARD_GAME_MODES_H

#include "constants/game_modes.h"

bool32 GameModeAllBallsAreMasterBalls(void);
bool32 GameModeCannotReviveDeadPokemon(void);
bool32 GameModeCannotUseFullRestoreInBattle(void);
bool32 GameModeCannotUseRevivalItemsInBattle(void);
bool32 GameModeCannotUseRevivalItemsOutOfBattle(void);
bool32 GameModeFaintedPokemonDie(void);
bool32 GameModeFirstRivalBattleIsRigged(void);
bool32 GameModeHasEntirelyHandCraftedBattles(void);
bool32 GameModeHasEntirelyPPMaxedMoves(void);
bool32 GameModeHasLimitedSpawns(void);
bool32 GameModeHasRandomWildEncounters(void);
bool32 GameModeHasStaticPlayerTrainerID(void);
bool32 GameModeIsDeterministic(void);
bool32 GameModeKeepStolenTrainerItems(void);
bool32 GameModeSpawnInPalletTown(void);
bool32 GameModeStandardizesStolenPokemonLevelsTo20(void);
bool32 GameModeStartsWithAll8Badges(void);
bool32 GameModeStartsWithPokemonMenuItem(void);
bool32 GameModeStartWith3000Money(void);
bool32 GameModeStartWithDash(void);
bool32 GameModeStartWithStandardPCItems(void);
bool32 GameModeStartWithStandardQoLFlags(void);
bool32 GameModeStartWithStandardQoLItems(void);

#endif // GUARD_GAME_MODES_H
