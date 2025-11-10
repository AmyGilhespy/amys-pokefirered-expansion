CeruleanCave_Underwater_MapScripts::
	.byte 0

CeruleanCave_Underwater_DiveSpot1::
	setflag FLAG_TEMP_D
	release
	end

CeruleanCave_Underwater_DiveSpot2::
	setflag FLAG_TEMP_D
	release
	end

CeruleanCave_Underwater_DiveSpotExited::
	clearflag FLAG_TEMP_D
	release
	end


