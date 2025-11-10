#include "global.h" // u8, etc
#include "script.h" // ScriptContext_SetupScript()
#include "fldeff.h" // FieldMove_SetUpDive()
#include "event_data.h" // VarSet()
#include "event_scripts.h" // EventScript_FldEffAmyDive()

bool32 FieldMove_SetUpDive(void)
{
    u8 currentMapGroup = gSaveBlock1Ptr->location.mapGroup;
    u8 currentMapNum = gSaveBlock1Ptr->location.mapNum;
    u8 targetMapGroup, targetMapNum, warpId;
    bool8 canDive = TRUE;
    if (currentMapGroup == MAP_GROUP(MAP_CERULEAN_CAVE_B1F) && currentMapNum == MAP_NUM(MAP_CERULEAN_CAVE_B1F))
    {
        targetMapGroup = MAP_GROUP(MAP_CERULEAN_CAVE_UNDERWATER);
        targetMapNum = MAP_NUM(MAP_CERULEAN_CAVE_UNDERWATER);
        warpId = 0;
    }
    else if (currentMapGroup == MAP_GROUP(MAP_CERULEAN_CAVE_SECRET_CHAMBER_B1F) && currentMapNum == MAP_NUM(MAP_CERULEAN_CAVE_SECRET_CHAMBER_B1F))
    {
        targetMapGroup = MAP_GROUP(MAP_CERULEAN_CAVE_UNDERWATER);
        targetMapNum = MAP_NUM(MAP_CERULEAN_CAVE_UNDERWATER);
        warpId = 1;
    }
    else if (currentMapGroup == MAP_GROUP(MAP_CERULEAN_CAVE_UNDERWATER) && currentMapNum == MAP_NUM(MAP_CERULEAN_CAVE_UNDERWATER))
    {
        bool8 secret = TRUE;
        targetMapGroup = secret ? MAP_GROUP(MAP_CERULEAN_CAVE_SECRET_CHAMBER_B1F) : MAP_GROUP(MAP_CERULEAN_CAVE_B1F);
        targetMapNum = secret ? MAP_NUM(MAP_CERULEAN_CAVE_SECRET_CHAMBER_B1F) : MAP_NUM(MAP_CERULEAN_CAVE_B1F);
        warpId = secret ? 0 : 1;
    }
    else
    {
        canDive = FALSE;
    }
    if (canDive)
    {
        canDive = FlagGet(FLAG_TEMP_D);
    }
    if (!canDive)
    {
        //DisplayFieldMessage(_("There's no deep water here."));
        return FALSE;
    }
    VarSet(VAR_TEMP_4, targetMapGroup);
    VarSet(VAR_TEMP_5, targetMapNum);
    VarSet(VAR_TEMP_6, warpId);
    ScriptContext_SetupScript(EventScript_FldEffAmyDive);
    return TRUE;
}

