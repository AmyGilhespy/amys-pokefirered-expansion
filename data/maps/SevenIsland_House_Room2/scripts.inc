SevenIsland_House_Room2_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SevenIsland_House_Room2_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SevenIsland_House_Room2_OnFrame
	.byte 0

SevenIsland_House_Room2_OnTransition::
	end

SevenIsland_House_Room2_OnFrame::
	map_script_2 VAR_TEMP_1, 0, SevenIsland_House_Room2_EventScript_BattleVisitingTrainer
	.2byte 0

SevenIsland_House_Room2_EventScript_BattleVisitingTrainer::
	end

SevenIsland_House_Room2_EventScript_BattleTie::
	setvar VAR_MAP_SCENE_SEVEN_ISLAND_HOUSE_ROOM1, 3
	msgbox SevenIsland_House_Room2_Text_MatchEndedUpDraw
	return

SevenIsland_House_Room2_EventScript_BattleWon::
	setvar VAR_MAP_SCENE_SEVEN_ISLAND_HOUSE_ROOM1, 1
	special ShowFieldMessageStringVar4
	waitmessage
	waitbuttonpress
	return

SevenIsland_House_Room2_EventScript_BattleLost::
	setvar VAR_MAP_SCENE_SEVEN_ISLAND_HOUSE_ROOM1, 2
	special ShowFieldMessageStringVar4
	waitmessage
	waitbuttonpress
	return

SevenIsland_House_Room2_Movement_PlayerEnterRoom::
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

SevenIsland_House_Room2_Movement_PlayerExitRoom::
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	step_end
