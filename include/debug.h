#ifndef GUARD_DEBUG_H
#define GUARD_DEBUG_H

extern u8 gKonamiProgress;

void Debug_ShowMainMenu(void);
extern const u8 Debug_FlagsAndVarNotSetBattleConfigMessage[];
const u8 *GetWeatherName(u32 weatherId);

extern EWRAM_DATA bool8 gIsDebugBattle;
extern EWRAM_DATA u64 gDebugAIFlags;

extern void ConvertGbaTextToAscii(const u8 *gba, char *ascii, size_t maxLen);

#endif // GUARD_DEBUG_H
