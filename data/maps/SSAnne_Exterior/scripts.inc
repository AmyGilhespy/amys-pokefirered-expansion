SSAnne_Exterior_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SSAnne_Exterior_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SSAnne_Exterior_OnFrame
	.byte 0

SSAnne_Exterior_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SSANNE_EXTERIOR
	end

SSAnne_Exterior_OnFrame::
	map_script_2 VAR_MAP_SCENE_VERMILION_CITY, 1, SSAnne_Exterior_ExitSSAnne
	.2byte 0

SSAnne_Exterior_CoordEvent_PierWarpCheck::
	goto_if_eq VAR_MAP_SCENE_VERMILION_CITY, 3, SSAnne_Exterior_CoordEvent_PierWarpBlock
	end

SSAnne_Exterior_CoordEvent_PierWarpBlock::
	msgbox SSAnne_Exterior_Text_ShipHasDeparted
	closemessage
	goto SSAnne_Exterior_WalkUpPier
	end

SSAnne_Exterior_WalkUpPier::
	closemessage
	applymovement LOCALID_PLAYER, SSAnne_Exterior_Movement_WalkUp
	waitmovement 0
	releaseall
	end

SSAnne_Exterior_Movement_WalkUp::
	walk_up
	step_end

SSAnne_Exterior_EventScript_StrengthTruck::
	goto_if_unset FLAG_TEMP_1, SSAnne_Exterior_EventScript_StrengthTruckSignActive
	end

SSAnne_Exterior_EventScript_StrengthTruckSignActive::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	goto_if_set FLAG_SYS_USE_STRENGTH, SSAnne_Exterior_EventScript_AlreadyUsedStrength
	checkfieldmoveusable FIELD_MOVE_STRENGTH
	goto_if_eq VAR_RESULT, FALSE, SSAnne_Exterior_EventScript_CantMoveTruck
	msgbox SSAnne_Exterior_Text_UseStrength, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SSAnne_Exterior_EventScript_DontUseStrength
	closemessage
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto SSAnne_Exterior_EventScript_UseStrength
	end

SSAnne_Exterior_EventScript_FldEffStrength::
	lockall
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto SSAnne_Exterior_EventScript_UseStrength
	end

SSAnne_Exterior_EventScript_UseStrength::
	setflag FLAG_SYS_USE_STRENGTH
	msgbox SSAnne_Exterior_Text_MonUsedStrengthCanMoveTrucks, MSGBOX_SIGN
	lock
	setflag FLAG_TEMP_1 @disable the signs
	setmetatile 54, 2, METATILE_General_PavementBlockedAbove, 1
	setmetatile 54, 3, METATILE_General_PavementCenter, 1
	special DoTruckMoveCutscene
	waitstate
	setmetatile 57, 2, METATILE_General_PavementBlockedAbove, 0
	setmetatile 57, 3, METATILE_General_PavementCenter, 0
	release
	goto_if_unset FLAG_MEW_UNDER_TRUCK_ENCOUNTER, SSAnne_Exterior_EventScript_MewUnderTruckEncounter
	end

SSAnne_Exterior_EventScript_MewUnderTruckEncounter::
	setwildbattle SPECIES_MEW, 60, ITEM_MASTER_BALL
	waitse
	playmoncry SPECIES_MEW, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	dowildbattle
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	special QuestLog_CutRecording
	specialvar VAR_RESULT, GetBattleOutcome
	@goto_if_eq VAR_RESULT, B_OUTCOME_WON, SSAnne_Exterior_EventScript_FoughtMewUnderTruck
	@goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SSAnne_Exterior_EventScript_FoughtMewUnderTruck
	@goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SSAnne_Exterior_EventScript_FoughtMewUnderTruck
	setflag FLAG_MEW_UNDER_TRUCK_ENCOUNTER
	end

SSAnne_Exterior_EventScript_FoughtMewUnderTruck::
	end

SSAnne_Exterior_EventScript_CantMoveTruck::
	msgbox SSAnne_Exterior_Text_MonMayPushTruck, MSGBOX_SIGN
	end

SSAnne_Exterior_EventScript_AlreadyUsedStrength::
	msgbox SSAnne_Exterior_Text_StrengthMadeMovingTrucksPossible, MSGBOX_SIGN
	end

SSAnne_Exterior_EventScript_DontUseStrength::
	closemessage
	releaseall
	end

SSAnne_Exterior_Text_UseStrength::
	.string "It's a big truck, but a POKéMON\n"
	.string "may be able to push it aside.\p"
	.string "Would you like to use STRENGTH?$"

SSAnne_Exterior_Text_MonUsedStrengthCanMoveTrucks::
	.string "{STR_VAR_1} used STRENGTH!\p"
	.string "{STR_VAR_1}'s STRENGTH made it\n"
	.string "possible to move the truck!$"

SSAnne_Exterior_Text_MonMayPushTruck::
	.string "It's a big truck, but a POKéMON\n"
	.string "may be able to push it aside.$"

SSAnne_Exterior_Text_StrengthMadeMovingTrucksPossible::
	.string "STRENGTH made it possible to move\n"
	.string "the truck.$"

SSAnne_Exterior_ExitSSAnne::
	lockall
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_le VAR_0x8005, 6, SSAnne_Exterior_WalkDown
	call_if_ge VAR_0x8005, 7, SSAnne_Exterior_WalkInPlaceDown
	fadenewbgm MUS_SURF
	delay 50
	special DoSSAnneDepartureCutscene
	waitstate
	removeobject LOCALID_SS_ANNE
	applymovement LOCALID_PLAYER, SSAnne_Exterior_Movement_Exit
	waitmovement 0
	setvar VAR_MAP_SCENE_VERMILION_CITY, 2
	setvar VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 0
	warp MAP_VERMILION_CITY, 23, 34
	waitstate
	releaseall
	end

SSAnne_Exterior_WalkDown::
	applymovement LOCALID_PLAYER, SSAnne_Exterior_Movement_WalkDown
	waitmovement 0
	return

SSAnne_Exterior_WalkInPlaceDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

SSAnne_Exterior_Movement_Exit::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SSAnne_Exterior_Movement_WalkDown::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
