CeruleanCave_SecretChamber_B9F_MapScripts::
	.byte 0

CeruleanCave_SecretChamber_B9F_Kyouko::
	lock
	msgbox CeruleanCave_SecretChamber_B9F_Text_Kyouko, MSGBOX_NPC
	release
	end

CeruleanCave_SecretChamber_B9F_Lilith::
	lock
	msgbox CeruleanCave_SecretChamber_B9F_Text_Lilith, MSGBOX_NPC
	release
	end

CeruleanCave_SecretChamber_B9F_Molly::
	lock
	msgbox CeruleanCave_SecretChamber_B9F_Text_Molly, MSGBOX_NPC
	release
	end

CeruleanCave_SecretChamber_B9F_Natalie::
	lock
	msgbox CeruleanCave_SecretChamber_B9F_Text_Natalie, MSGBOX_NPC
	release
	end

CeruleanCave_SecretChamber_B9F_Olivia::
	lock
	msgbox CeruleanCave_SecretChamber_B9F_Text_Olivia, MSGBOX_NPC
	release
	end

CeruleanCave_SecretChamber_B9F_Amy::
	lock
	checktrainerflag TRAINER_AMY
	goto_if_eq CeruleanCave_SecretChamber_B9F_EventScript_RematchAmy
	trainerbattle_single TRAINER_AMY, CeruleanCave_SecretChamber_B9F_Text_AmyIntro, CeruleanCave_SecretChamber_B9F_Text_AmyDefeat, CeruleanCave_SecretChamber_B9F_EventScript_DefeatedAmy, NO_MUSIC
CeruleanCave_SecretChamber_B9F_EventScript_DefeatedAmy::
	lockall
	msgbox CeruleanCave_SecretChamber_B9F_Text_AmyPostBattle, MSGBOX_NPC
@	// TODO: I wanted to just give an ESCAPE ROPE, but there was the problem of if
@	//       the player's bag was full.  This does the Hall of Fame instead, which
@	//       might just be a better approach anyway, but it needs testing!
@	checkitem ITEM_ESCAPE_ROPE, 1
@	goto_if_ne VAR_RESULT, FALSE, CeruleanCave_SecretChamber_B9F_EventScript_HaveEscapeRope
@	checkitemspace ITEM_ESCAPE_ROPE, 1
@	goto_if_ne VAR_RESULT, FALSE, CeruleanCave_SecretChamber_B9F_EventScript_GiveEscapeRope
@	msgbox CeruleanCave_SecretChamber_B9F_Text_DidNotReceiveEscapeRope, MSGBOX_NPC
@	// TODO: Do here: Warp to Pallet Town
@CeruleanCave_SecretChamber_B9F_EventScript_GiveEscapeRope::
@	giveitem_msg CeruleanCave_SecretChamber_B9F_Text_ReceivedEscapeRope, ITEM_ESCAPE_ROPE, 1
@CeruleanCave_SecretChamber_B9F_EventScript_HaveEscapeRope::
@	// If we're not going to give escape rope or anything, don't hide the NPCs either.
@	setflag FLAG_TEMP_E @ Hide Amy and friends until map reload
@	removeobject LOCALID_CCSC_B9F_KYOUKO
@	removeobject LOCALID_CCSC_B9F_LILITH
@	removeobject LOCALID_CCSC_B9F_MOLLY
@	removeobject LOCALID_CCSC_B9F_NATALIE
@	removeobject LOCALID_CCSC_B9F_OLIVIA
@	removeobject LOCALID_AMY
	setrespawn HEAL_LOCATION_PALLET_TOWN
	fadescreenspeed FADE_TO_BLACK, 24
	special EnterHallOfFame
	waitstate
	releaseall
	end

CeruleanCave_SecretChamber_B9F_EventScript_RematchAmy::
	cleartrainerflag TRAINER_AMY
	trainerbattle_single TRAINER_AMY, CeruleanCave_SecretChamber_B9F_Text_AmyRematchIntro, CeruleanCave_SecretChamber_B9F_Text_AmyDefeat, CeruleanCave_SecretChamber_B9F_EventScript_DefeatedAmy, NO_MUSIC
	goto CeruleanCave_SecretChamber_B9F_EventScript_DefeatedAmy
	end
