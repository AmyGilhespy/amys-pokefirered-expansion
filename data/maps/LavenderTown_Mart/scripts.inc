LavenderTown_Mart_MapScripts::
	.byte 0

LavenderTown_Mart_EventScript_BaldingMan::
	msgbox LavenderTown_Mart_Text_SearchingForStatRaiseItems, MSGBOX_NPC
	end

LavenderTown_Mart_EventScript_Rocker::
	msgbox LavenderTown_Mart_Text_DidYouBuyRevives, MSGBOX_NPC
	end

LavenderTown_Mart_EventScript_Youngster::
	msgbox LavenderTown_Mart_Text_TrainerDuosCanChallengeYou, MSGBOX_NPC
	end

LavenderTown_Mart_EventScript_Clerk::
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	message Text_MayIHelpYou
	waitmessage
	pokemart LavenderTown_Mart_Items
	msgbox Text_PleaseComeAgain
	release
	end

	.align 2
LavenderTown_Mart_Items::
	.2byte ITEM_FOCUS_SASH
	.2byte ITEM_SCOPE_LENS
	.2byte ITEM_WIDE_LENS
	.2byte ITEM_ZOOM_LENS
	.2byte ITEM_EXPERT_BELT
	.2byte ITEM_AIR_BALLOON
	.2byte ITEM_BIG_ROOT
	.2byte ITEM_SHELL_BELL
	.2byte ITEM_IRON_BALL
	.2byte ITEM_MENTAL_HERB
	.2byte ITEM_MIRROR_HERB
	.2byte ITEM_POWER_HERB
	.2byte ITEM_WHITE_HERB
	.2byte ITEM_DAMP_ROCK
	.2byte ITEM_HEAT_ROCK
	.2byte ITEM_SMOOTH_ROCK
	.2byte ITEM_ICY_ROCK
	.2byte ITEM_TERRAIN_EXTENDER
	.2byte ITEM_LIGHT_CLAY
	@.2byte ITEM_BLANK_PLATE @ Doesn't exist in my fork.
	.2byte ITEM_FIST_PLATE
	.2byte ITEM_SKY_PLATE
	.2byte ITEM_TOXIC_PLATE
	.2byte ITEM_EARTH_PLATE
	.2byte ITEM_STONE_PLATE
	.2byte ITEM_INSECT_PLATE
	.2byte ITEM_SPOOKY_PLATE
	.2byte ITEM_IRON_PLATE
	.2byte ITEM_FLAME_PLATE
	.2byte ITEM_SPLASH_PLATE
	.2byte ITEM_MEADOW_PLATE
	.2byte ITEM_ZAP_PLATE
	.2byte ITEM_MIND_PLATE
	.2byte ITEM_ICICLE_PLATE
	.2byte ITEM_DRACO_PLATE
	.2byte ITEM_DREAD_PLATE
	.2byte ITEM_PIXIE_PLATE
	@.2byte ITEM_LEGEND_PLATE @ Doesn't exist in my fork.
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_RARE_CANDY
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end
