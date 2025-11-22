EscapeRoom_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EscapeRoom_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

EscapeRoom_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_ESCAPE_ROOM
	end

EscapeRoom_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse
	release
	end
