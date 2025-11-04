ViridianCity_House_MapScripts::
	.byte 0

ViridianCity_House_EventScript_BaldingMan::
	msgbox ViridianCity_House_Text_NicknamingIsFun, MSGBOX_NPC
	end

ViridianCity_House_EventScript_LittleGirl::
	trainerbattle_single TRAINER_ANNA, ViridianCity_House_Text_AnnaIntro, ViridianCity_House_Text_AnnaDefeat, ViridianCity_House_EventScript_DefeatedAnna, NO_MUSIC
ViridianCity_House_EventScript_DefeatedAnna::
	msgbox ViridianCity_House_Text_YouKilledMrCuddles, MSGBOX_NPC
	end

ViridianCity_House_EventScript_Speary::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SPEAROW, CRY_MODE_NORMAL
	msgbox ViridianCity_House_Text_Speary
	waitmoncry
	release
	end

ViridianCity_House_EventScript_NicknameSign::
	msgbox ViridianCity_House_Text_SpearowNameSpeary, MSGBOX_SIGN
	end
