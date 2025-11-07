EventScript_PkmnCenterNurse::
	goto_if_questlog EventScript_ReleaseEnd
	message Text_WelcomeWantToHealPkmn
	waitmessage
	multichoice 19, 5, MULTICHOICE_NURSE_CUSTOM, FALSE | (TRUE << 1)
	switch VAR_RESULT
	case 0, EventScript_PkmnCenterNurse_HealPkmn
	case 1, EventScript_PkmnCenterNurse_RenamePkmn
	case 2, EventScript_PkmnCenterNurse_RemindPkmn
	case 3 EventScript_PkmnCenterNurse_Goodbye
	case SCR_MENU_CANCEL, EventScript_PkmnCenterNurse_Goodbye
	end

EventScript_PkmnCenterNurse_HealPkmn::
	incrementgamestat GAME_STAT_USED_POKECENTER
	message Text_TakeYourPkmnForFewSeconds
	waitmessage
	call EventScript_PkmnCenterNurse_TakeAndHealPkmn
	special SetUsedPkmnCenterQuestLogEvent
	goto EventScript_PkmnCenterNurse_CheckTrainerTowerAndUnionRoom
	end

EventScript_PkmnCenterNurse_TakeAndHealPkmn::
	hidefollower 0
	applymovement VAR_LAST_TALKED, Movement_PkmnCenterNurse_Turn
	waitmovement 0
	dofieldeffect FLDEFF_POKECENTER_HEAL
	waitfieldeffect FLDEFF_POKECENTER_HEAL
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	return

EventScript_PkmnCenterNurse_CheckTrainerTowerAndUnionRoom::
	specialvar VAR_RESULT, IsPlayerNotInTrainerTowerLobby
	goto_if_eq VAR_RESULT, FALSE, EventScript_PkmnCenterNurse_ReturnPkmn
	specialvar VAR_RESULT, BufferUnionRoomPlayerName
	copyvar VAR_0x8008, VAR_RESULT
	goto_if_eq VAR_0x8008, 0, EventScript_PkmnCenterNurse_ReturnPkmn
	goto_if_eq VAR_0x8008, 1, EventScript_PkmnCenterNurse_PlayerWaitingInUnionRoom
	end

EventScript_PkmnCenterNurse_ReturnPkmn::
	message Text_RestoredPkmnToFullHealth
	waitmessage
	applymovement VAR_LAST_TALKED, Movement_Bow
	@waitmovement 0
	@msgbox Text_WeHopeToSeeYouAgain
	waitbuttonpress
	return

EventScript_PkmnCenterNurse_PlayerWaitingInUnionRoom::
	goto_if_set FLAG_SYS_INFORMED_OF_LOCAL_WIRELESS_PLAYER, EventScript_PkmnCenterNurse_ReturnPkmn
	msgbox Text_RestoredPkmnToFullHealth
	setflag FLAG_SYS_INFORMED_OF_LOCAL_WIRELESS_PLAYER
	message Text_PlayerIsPlayingRightNowGoForIt
	waitmessage
	applymovement VAR_LAST_TALKED, Movement_Bow
	@waitmovement 0
	@msgbox Text_WeHopeToSeeYouAgain
	return

EventScript_PkmnCenterNurse_RenamePkmn::
	msgbox LavenderTown_House2_Text_WhatShallNewNicknameBe
	setvar VAR_0x8004, 0 @ Index of pokemon in player's party whose name is to change
	call EventScript_ChangePokemonNickname
	specialvar VAR_RESULT, NameRaterWasNicknameChanged
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, LavenderTown_House2_EventScript_ChoseNewNickname
	msgbox LavenderTown_House2_Text_FromNowOnShallBeKnownAsSameName
	release
	end

EventScript_PkmnCenterNurse_RemindPkmn::
	msgbox TwoIsland_House_Text_TutorWhichMon
	special ChooseMonForMoveRelearner
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, EventScript_PkmnCenterNurse_Goodbye
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, EventScript_PkmnCenterNurse_CantTutorEgg
	goto_if_eq VAR_0x8005, 0, EventScript_PkmnCenterNurse_NoMoveToTutorMon
	goto EventScript_PkmnCenterNurse_ChooseMoveToTeach
	end

EventScript_PkmnCenterNurse_ChooseMoveToTeach::
	msgbox TwoIsland_House_Text_TeachWhichMove
	special TeachMoveRelearnerMove
	waitstate
	goto_if_eq VAR_0x8004, 0, EventScript_PkmnCenterNurse_RemindPkmn
	end

EventScript_PkmnCenterNurse_NoMoveToTutorMon::
	msgbox TwoIsland_House_Text_NoMoveICanTeachThatMon
	goto EventScript_PkmnCenterNurse_RemindPkmn
	end

EventScript_PkmnCenterNurse_CantTutorEgg::
	msgbox TwoIsland_House_Text_CantTeachAnEgg
	goto EventScript_PkmnCenterNurse_RemindPkmn
	end

EventScript_PkmnCenterNurse_Goodbye::
	msgbox Text_WeHopeToSeeYouAgain
	return

Movement_Bow::
	nurse_joy_bow
	delay_4
	step_end

Movement_PkmnCenterNurse_Turn:
	walk_in_place_faster_left
	step_end
