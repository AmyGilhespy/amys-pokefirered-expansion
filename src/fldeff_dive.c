#include "global.h" // u8, etc
#include "script.h" // ScriptContext_SetupScript()
#include "fldeff.h" // FieldMove_SetUpDive()
#include "event_data.h" // VarSet()
#include "event_scripts.h" // EventScript_FldEffAmyDive()

bool32 FieldMove_SetUpDive(void)
{
    const struct WarpEvent *warps = gMapHeader.events->warps;
    s16 px = gSaveBlock1Ptr->pos.x;
    s16 py = gSaveBlock1Ptr->pos.y;
    s16 bestDist = 0x7fff;
    u8 mapGroup, mapNum, warpId;
    u8 warpCount = gMapHeader.events->warpCount;
    u8 bestWarpId = 0xff;

    if (!FlagGet(FLAG_TEMP_D))
    {
        return FALSE;
    }

    for (int i = 0; i < warpCount; i++) {
        s16 dx = px - warps[i].x;
        s16 dy = py - warps[i].y;
        s16 dist = abs(dx) + abs(dy);
        if (dist < bestDist) {
            bestDist = dist;
            bestWarpId = i;
        }
    }
    if (bestDist == 0x7fff)
    {
        return FALSE;
    }
    mapGroup = warps[bestWarpId].mapGroup;
    mapNum = warps[bestWarpId].mapNum;
    warpId = warps[bestWarpId].warpId;
    VarSet(VAR_TEMP_4, mapGroup);
    VarSet(VAR_TEMP_5, mapNum);
    VarSet(VAR_TEMP_6, warpId);
    ScriptContext_SetupScript(EventScript_FldEffAmyDive);
    return TRUE;
}

