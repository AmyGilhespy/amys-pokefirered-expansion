EscapeRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EscapeRoom_OnTransition
	.byte 0

EscapeRoom_OnTransition::
	call_if_unset FLAG_ESCAPE_ROOM_INIT, EscapeRoom_EventScript_GiveStarter
	end

EscapeRoom_EventScript_GiveStarter::
	setflag FLAG_ESCAPE_ROOM_INIT
	setrespawn HEAL_LOCATION_ESCAPE_ROOM
	givemon SPECIES_RALTS, 1, ITEM_NONE, ITEM_LOVE_BALL, NATURE_NAUGHTY, 0, MON_FEMALE,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  MOVE_ENDURE, MOVE_COPYCAT, MOVE_SWITCHEROO, MOVE_SKILL_SWAP, TRUE, FALSE, TYPE_FAIRY, 0
	return

EscapeRoom_EventScript_TrainerA::
	trainerbattle_single TRAINER_ESCAPE_ROOM_A, EscapeRoom_Text_AIntro, EscapeRoom_Text_ADefeat, EscapeRoom_EventScript_DefeatedA
	end

EscapeRoom_EventScript_DefeatedA::
	end
