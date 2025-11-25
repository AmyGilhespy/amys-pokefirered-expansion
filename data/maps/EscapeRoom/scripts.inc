EscapeRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EscapeRoom_OnTransition
	.byte 0

EscapeRoom_OnTransition::
	call_if_unset FLAG_ESCAPE_ROOM_INIT, EscapeRoom_EventScript_Init
	end


EscapeRoom_EventScript_Init::
	setflag FLAG_ESCAPE_ROOM_INIT
	setrespawn HEAL_LOCATION_ESCAPE_ROOM

	givemon SPECIES_RALTS, 12, ITEM_NONE, ITEM_LOVE_BALL, NATURE_NAUGHTY, 0, MON_FEMALE,  208, 0, 0, 0, 0, 0,  31, 31, 31, 31, 31, 31,  MOVE_DISABLE, MOVE_GROWL, MOVE_DISARMING_VOICE, MOVE_NONE, FALSE, FALSE, TYPE_FAIRY, 0

	givemon SPECIES_BONSLY, 16, ITEM_NONE, ITEM_LOVE_BALL, NATURE_HARDY, 0, MON_MALE,  0, 252, 0, 0, 0, 0,  31, 31, 31, 31, 31, 31,  MOVE_ROCK_THROW, MOVE_NONE, MOVE_NONE, MOVE_NONE, FALSE, FALSE, TYPE_ROCK, 0

	givemon SPECIES_FARFETCHD, 14, ITEM_NONE, ITEM_LOVE_BALL, NATURE_SASSY, 0, MON_MALE,  0, 0, 0, 0, 0, 0,  31, 31, 31, 31, 31, 31,  MOVE_PLUCK, MOVE_FEINT, MOVE_SAND_ATTACK, MOVE_PECK, FALSE, FALSE, TYPE_NORMAL, 0

	setflag FLAG_SYS_B_DASH

	return


EscapeRoom_EventScript_Sign1::
	msgbox EscapeRoom_Text_Sign1, MSGBOX_SIGN
	end


EscapeRoom_EventScript_TrainerA::
	trainerbattle_double TRAINER_ESCAPE_ROOM_A, EscapeRoom_Text_AIntro, EscapeRoom_Text_ADefeat, EscapeRoom_Text_ANotEnoughPkmn, EscapeRoom_EventScript_DefeatedA
	goto_if_set FLAG_TEMP_1C, EscapeRoom_EventScript_StoleA
	cleartrainerflag TRAINER_ESCAPE_ROOM_A @ This MUST NOT happen before the battle, as it uses LOS to start the battle instead of waiting for you to talk to them and LOS trainers MUST have their trainer flag not cleared between the LOS trigger and the battle or it hard freezes or even crashes due to a null pointer mishap.
	end
EscapeRoom_EventScript_StoleA::
	clearflag FLAG_TEMP_1C
	msgbox EscapeRoom_Text_YouJerk, MSGBOX_NPC
	setflag FLAG_SPECIAL_GAME_MODE_HIDE_TRAINER_A
	removeobject LOCALID_ESCAPE_ROOM_TRAINER_A1
	removeobject LOCALID_ESCAPE_ROOM_TRAINER_A2
	end

EscapeRoom_EventScript_DefeatedA::
	end


EscapeRoom_EventScript_TrainerB::
	trainerbattle_single TRAINER_ESCAPE_ROOM_B, EscapeRoom_Text_BIntro, EscapeRoom_Text_BDefeat, EscapeRoom_EventScript_DefeatedB
	goto_if_set FLAG_TEMP_1C, EscapeRoom_EventScript_StoleB
	cleartrainerflag TRAINER_ESCAPE_ROOM_B @ This MUST NOT happen before the battle, as it uses LOS to start the battle instead of waiting for you to talk to them and LOS trainers MUST have their trainer flag not cleared between the LOS trigger and the battle or it hard freezes or even crashes due to a null pointer mishap.
	end
EscapeRoom_EventScript_StoleB::
	clearflag FLAG_TEMP_1C
	msgbox EscapeRoom_Text_YouBastard, MSGBOX_NPC
	setflag FLAG_SPECIAL_GAME_MODE_HIDE_TRAINER_B
	removeobject LOCALID_ESCAPE_ROOM_TRAINER_B
	end

EscapeRoom_EventScript_DefeatedB::
	end


EscapeRoom_EventScript_Sign2::
	msgbox EscapeRoom_Text_Sign2, MSGBOX_SIGN
	end

EscapeRoom_EventScript_Sign3::
	msgbox EscapeRoom_Text_Sign3, MSGBOX_SIGN
	end


EscapeRoom_EventScript_MoveTutor_Trick::
	goto_if_set FLAG_ESCAPE_ROOM_GOT_ITEMS_FROM_PROSTITUTE, EventScript_EscapeRoom_TrickTutor
	setflag FLAG_ESCAPE_ROOM_GOT_ITEMS_FROM_PROSTITUTE
	msgbox EscapeRoom_Text_MoveTutor_Trick_RareCandy_Message, MSGBOX_NPC
	giveitem_msg EscapeRoom_Text_MoveTutor_Trick_RareCandy_Received, ITEM_RARE_CANDY, 1
	msgbox EscapeRoom_Text_MoveTutor_Trick_SuperRod_Message, MSGBOX_NPC
	giveitem_msg EscapeRoom_Text_MoveTutor_Trick_SuperRod_Received, ITEM_SUPER_ROD, 1
	goto EventScript_EscapeRoom_TrickTutor
	end


EscapeRoom_EventScript_Item1::
	finditem ITEM_LIGMA_BALL
	end

EscapeRoom_EventScript_Item2::
	finditem ITEM_LIGMA_BALL
	end


EscapeRoom_EventScript_TrainerC::
	trainerbattle_single TRAINER_ESCAPE_ROOM_C, EscapeRoom_Text_CIntro, EscapeRoom_Text_CDefeat, EscapeRoom_EventScript_DefeatedC
	goto_if_set FLAG_TEMP_1C, EscapeRoom_EventScript_StoleC
	cleartrainerflag TRAINER_ESCAPE_ROOM_C @ This MUST NOT happen before the battle, as it uses LOS to start the battle instead of waiting for you to talk to them and LOS trainers MUST have their trainer flag not cleared between the LOS trigger and the battle or it hard freezes or even crashes due to a null pointer mishap.
	end
EscapeRoom_EventScript_StoleC::
	clearflag FLAG_TEMP_1C
	msgbox EscapeRoom_Text_YouBastard, MSGBOX_NPC
	setflag FLAG_SPECIAL_GAME_MODE_HIDE_TRAINER_C
	removeobject LOCALID_ESCAPE_ROOM_TRAINER_C
	end

EscapeRoom_EventScript_DefeatedC::
	end


EscapeRoom_EventScript_Item3::
	finditem ITEM_COCAINE
	end

EscapeRoom_EventScript_Sign4::
	msgbox EscapeRoom_Text_Sign4, MSGBOX_SIGN
	end


EscapeRoom_EventScript_SittingBoy::
	msgbox EscapeRoom_Text_SittingBoy_NeedSomethingToWakeUp, MSGBOX_NPC
	checkitem ITEM_COCAINE, 1
	goto_if_eq VAR_RESULT, FALSE, EscapeRoom_EventScript_SittingBoy_PleaseFindMeSomethingEnergizing
	msgbox EscapeRoom_Text_SittingBoy_GiveCocaine, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, EscapeRoom_EventScript_SittingBoy_PleaseFindMeSomethingEnergizing
	removeitem ITEM_COCAINE, 1
	msgbox EscapeRoom_Text_SittingBoy_YayCocaine, MSGBOX_NPC
	setflag FLAG_ESCAPE_ROOM_HIDE_SITTING_BOY
	removeobject LOCALID_ESCAPE_ROOM_SITTING_BOY
	release
	end
EscapeRoom_EventScript_SittingBoy_PleaseFindMeSomethingEnergizing:
	msgbox EscapeRoom_Text_SittingBoy_PleaseFindMeSomethingEnergizing, MSGBOX_NPC
	goto_if_set FLAG_ESCAPE_ROOM_GOT_ITEMS_FROM_SITTING_BOY, EscapeRoom_EventScript_ReleaseEnd
	msgbox EscapeRoom_Text_SittingBoy_IDontLikeCandy, MSGBOX_NPC
	setflag FLAG_ESCAPE_ROOM_GOT_ITEMS_FROM_SITTING_BOY
	giveitem_msg EscapeRoom_Text_SittingBoy_RareCandy_Received, ITEM_RARE_CANDY, 1
	goto EscapeRoom_EventScript_ReleaseEnd
	end


EscapeRoom_EventScript_FloorSwitch::
	lockall
	goto_if_eq VAR_MAP_SCENE_ESCAPE_ROOM_BOULDER, 100, EscapeRoom_EventScript_FloorSwitchAlreadyPressed
	playse SE_ICE_BREAK
	waitse
	setvar VAR_MAP_SCENE_ESCAPE_ROOM_BOULDER, 100
	releaseall
	end

EscapeRoom_EventScript_FloorSwitchAlreadyPressed::
	releaseall
	end


EscapeRoom_EventScript_TrainerD::
	goto_if_ne VAR_MAP_SCENE_ESCAPE_ROOM_BOULDER, 100, EscapeRoom_EventScript_TrainerDWontFightBeforeBoulderPuzzleSolved
	msgbox EscapeRoom_Text_TrainerDShitILostMyBalls, MSGBOX_NPC
	callnative EscapeRoomCheckIfFullTeamOf6InParty
	goto_if_eq VAR_RESULT, FALSE, EscapeRoom_EventScript_TrainerDWontFightPartialParty
	trainerbattle_single TRAINER_ESCAPE_ROOM_D, EscapeRoom_Text_DIntro, EscapeRoom_Text_DDefeat, EscapeRoom_EventScript_DefeatedD
	clearflag FLAG_TEMP_1C
	setflag FLAG_SPECIAL_GAME_MODE_HIDE_TRAINER_D
	removeobject LOCALID_ESCAPE_ROOM_TRAINER_D
	end

EscapeRoom_EventScript_TrainerDWontFightBeforeBoulderPuzzleSolved::
	msgbox EscapeRoom_Text_TrainerDWontFightBeforeBoulderPuzzleSolved, MSGBOX_NPC
	end

EscapeRoom_EventScript_TrainerDWontFightPartialParty::
	msgbox EscapeRoom_Text_TrainerDWontFightPartialParty, MSGBOX_NPC
	end

EscapeRoom_EventScript_DefeatedD::
	callnative EscapeRoomRemoveAllButRaltsLine
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox EscapeRoom_Text_DTookPokemon, MSGBOX_NPC
	textcolor NPC_TEXT_COLOR_MALE
	msgbox EscapeRoom_Text_DPostTakePokemon, MSGBOX_NPC
	end


EscapeRoom_EventScript_Item4::
	finditem ITEM_ROCKET_BALL
	end

EscapeRoom_EventScript_Item5::
	finditem ITEM_ROCKET_BALL
	end

EscapeRoom_EventScript_Item6::
	finditem ITEM_TM_SKILL_SWAP
	end


EscapeRoom_EventScript_TrainerE::
	trainerbattle_single TRAINER_ESCAPE_ROOM_E, EscapeRoom_Text_EIntro, EscapeRoom_Text_EDefeat, EscapeRoom_EventScript_DefeatedE
	goto_if_set FLAG_TEMP_1C, EscapeRoom_EventScript_StoleE
	cleartrainerflag TRAINER_ESCAPE_ROOM_E @ This MUST NOT happen before the battle, as it uses LOS to start the battle instead of waiting for you to talk to them and LOS trainers MUST have their trainer flag not cleared between the LOS trigger and the battle or it hard freezes or even crashes due to a null pointer mishap.
	end
EscapeRoom_EventScript_StoleE::
	clearflag FLAG_TEMP_1C
	msgbox EscapeRoom_Text_YouBastard, MSGBOX_NPC
	setflag FLAG_SPECIAL_GAME_MODE_HIDE_TRAINER_E
	removeobject LOCALID_ESCAPE_ROOM_TRAINER_E
	end

EscapeRoom_EventScript_DefeatedE::
	end


EscapeRoom_EventScript_TrainerF::
	trainerbattle_single TRAINER_ESCAPE_ROOM_F, EscapeRoom_Text_FIntro, EscapeRoom_Text_FDefeat, EscapeRoom_EventScript_DefeatedF
	goto_if_set FLAG_TEMP_1C, EscapeRoom_EventScript_StoleF
	cleartrainerflag TRAINER_ESCAPE_ROOM_F @ This MUST NOT happen before the battle, as it uses LOS to start the battle instead of waiting for you to talk to them and LOS trainers MUST have their trainer flag not cleared between the LOS trigger and the battle or it hard freezes or even crashes due to a null pointer mishap.
	end
EscapeRoom_EventScript_StoleF::
	clearflag FLAG_TEMP_1C
	msgbox EscapeRoom_Text_YouBastard, MSGBOX_NPC
	setflag FLAG_SPECIAL_GAME_MODE_HIDE_TRAINER_F
	removeobject LOCALID_ESCAPE_ROOM_TRAINER_F
	end

EscapeRoom_EventScript_DefeatedF::
	end


EscapeRoom_EventScript_TrainerG::
	trainerbattle_single TRAINER_ESCAPE_ROOM_G, EscapeRoom_Text_GIntro, EscapeRoom_Text_GDefeat, EscapeRoom_EventScript_DefeatedG
	goto_if_set FLAG_TEMP_1C, EscapeRoom_EventScript_StoleG
	cleartrainerflag TRAINER_ESCAPE_ROOM_G @ This MUST NOT happen before the battle, as it uses LOS to start the battle instead of waiting for you to talk to them and LOS trainers MUST have their trainer flag not cleared between the LOS trigger and the battle or it hard freezes or even crashes due to a null pointer mishap.
	end
EscapeRoom_EventScript_StoleG::
	clearflag FLAG_TEMP_1C
	msgbox EscapeRoom_Text_YouBastard, MSGBOX_NPC
	setflag FLAG_SPECIAL_GAME_MODE_HIDE_TRAINER_G
	removeobject LOCALID_ESCAPE_ROOM_TRAINER_G
	end

EscapeRoom_EventScript_DefeatedG::
	end


EscapeRoom_EventScript_TrainerH::
	trainerbattle_single TRAINER_ESCAPE_ROOM_H, EscapeRoom_Text_HIntro, EscapeRoom_Text_HDefeat, EscapeRoom_EventScript_DefeatedH
	goto_if_set FLAG_TEMP_1C, EscapeRoom_EventScript_StoleH
	cleartrainerflag TRAINER_ESCAPE_ROOM_H @ This MUST NOT happen before the battle, as it uses LOS to start the battle instead of waiting for you to talk to them and LOS trainers MUST have their trainer flag not cleared between the LOS trigger and the battle or it hard freezes or even crashes due to a null pointer mishap.
	end
EscapeRoom_EventScript_StoleH::
	clearflag FLAG_TEMP_1C
	msgbox EscapeRoom_Text_YouBastard, MSGBOX_NPC
	setflag FLAG_SPECIAL_GAME_MODE_HIDE_TRAINER_H
	removeobject LOCALID_ESCAPE_ROOM_TRAINER_H
	end

EscapeRoom_EventScript_DefeatedH::
	end


EscapeRoom_EventScript_ReleaseEnd:
	release
EscapeRoom_EventScript_End::
	end
