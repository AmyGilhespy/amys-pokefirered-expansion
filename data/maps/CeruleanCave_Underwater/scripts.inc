CeruleanCave_Underwater_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeruleanCave_Underwater_OnTransitionOrResume
	map_script MAP_SCRIPT_ON_RESUME, CeruleanCave_Underwater_OnTransitionOrResume
	.byte 0

CeruleanCave_Underwater_OnTransitionOrResume::
	@call Common_EventScript_EnableSurfingIfUnderwater
	end

CeruleanCave_Underwater_DiveSpot::
CeruleanCave_Underwater_DiveSpot1::
CeruleanCave_Underwater_DiveSpot2::
	@goto_if_set FLAG_TEMP_A, CeruleanCave_Underwater_DiveSpotPrintedMessage
	@lock
	@setflag FLAG_TEMP_A
	@msgbox Text_TheWaterIsDeepHere
CeruleanCave_Underwater_DiveSpotPrintedMessage::
	setflag FLAG_TEMP_D
	release
	end

CeruleanCave_Underwater_DiveSpotExited::
	clearflag FLAG_TEMP_D
	release
	end


