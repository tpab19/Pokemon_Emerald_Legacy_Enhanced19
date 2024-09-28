.set LOCALID_GROUDON, 1
.set LOCALID_MAXIE, 2

TerraCave_End_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TerraCave_End_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, TerraCave_End_OnTransition
	.byte 0

TerraCave_End_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, TerraCave_End_EventScript_TryRemoveGroudon
	end

TerraCave_End_EventScript_TryRemoveGroudon::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject LOCALID_GROUDON
	return

TerraCave_End_OnTransition:
	call_if_unset FLAG_DEFEATED_GROUDON, TerraCave_End_EventScript_ShowGroudon
	setflag FLAG_HIDE_MAXIE_TERRA_CAVE
	end

TerraCave_End_EventScript_ShowGroudon::
	clearflag FLAG_HIDE_TERRA_CAVE_GROUDON
	setvar VAR_TEMP_1, 1
	return

TerraCave_End_EventScript_Groudon::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_GROUDON, TerraCave_End_Movement_GroudonApproach
	waitmovement 0
	waitse
	playmoncry SPECIES_GROUDON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_GROUDON
	setwildbattle SPECIES_GROUDON, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	setvar VAR_TEMP_1, 0
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, TerraCave_End_EventScript_DefeatedGroudon
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, TerraCave_End_EventScript_RanFromGroudon
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, TerraCave_End_EventScript_RanFromGroudon
	goto_if_unset FLAG_BEAT_MAXIE_TERRA_CAVE, TerraCave_End_EventScript_Maxie
	setvar VAR_SHOULD_END_ABNORMAL_WEATHER, 1
	setflag FLAG_DEFEATED_GROUDON
	releaseall
	end

TerraCave_End_EventScript_DefeatedGroudon::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	goto_if_unset FLAG_BEAT_MAXIE_TERRA_CAVE, TerraCave_End_EventScript_Maxie
	setvar VAR_SHOULD_END_ABNORMAL_WEATHER, 1
	setflag FLAG_DEFEATED_GROUDON
	end

TerraCave_End_EventScript_RanFromGroudon::
	setvar VAR_0x8004, SPECIES_GROUDON
	goto Common_EventScript_LegendaryFlewAway
	end

TerraCave_End_EventScript_Maxie::
	addobject LOCALID_MAXIE
	applymovement LOCALID_MAXIE, TerraCave_End_Movement_MaxieApproach
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	trainerbattle_single TRAINER_MAXIE_TERRA_CAVE, TerraCave_End_Text_MaxieIntro, TerraCave_End_Text_MaxieDefeat, TerraCave_End_EventScript_MaxieDefeated
	releaseall
	end

TerraCave_End_EventScript_MaxieDefeated::
	msgbox TerraCave_End_Text_MaxiePostBattle, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_BEAT_MAXIE_TERRA_CAVE
	setvar VAR_SHOULD_END_ABNORMAL_WEATHER, 1
	setflag FLAG_DEFEATED_GROUDON
	call TerraCave_End_EventScript_SetMtPyre
	applymovement LOCALID_MAXIE, TerraCave_End_Movement_MaxieLeaves
	waitmovement 0
	removeobject LOCALID_MAXIE
	releaseall
	end

TerraCave_End_EventScript_SetMtPyre::
	goto_if_unset FLAG_BEAT_ARCHIE_MARINE_CAVE, Common_EventScript_NopReturn
	goto_if_unset FLAG_BEAT_MAXIE_TERRA_CAVE, Common_EventScript_NopReturn
	setvar VAR_MT_PYRE_STATE, 2
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_MAXIE
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_ARCHIE
	return

TerraCave_End_Movement_GroudonApproach:
	init_affine_anim
	walk_down_start_affine
	delay_16
	delay_16
	walk_down_affine
	delay_16
	delay_16
	walk_down_affine
	step_end

TerraCave_End_Movement_MaxieApproach:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

TerraCave_End_Movement_MaxieLeaves:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

TerraCave_End_Text_MaxieIntro:
	.string "MAXIE: GROUDON.... captured by you?!\n"
	.string "No! This isn't how it was supposed to\l"
	.string "be!\p" 
	.string "You think you can handle that kind of\n"
	.string "power?\p"
	.string "Only I, who understands its true\n"
	.string "potential, can keep it safe from those\l"
	.string "who would misuse it!\p"
	.string "You... {PLAYER}{KUN}...\n"
	.string "You have no idea what you've done!\p"
	.string "I'll battle you here and now to take\n"
	.string "back GROUDON! It's my responsibility!$"

TerraCave_End_Text_MaxieDefeat:
	.string "MAXIE: So, you've bested me...\n"
	.string "for now.$"

TerraCave_End_Text_MaxiePostBattle:
	.string "MAXIE: ...How could this happen?\n"
	.string "Even after everything...\p"
	.string "All this time, I believed expanding the\n"
	.string "land would heal the world, feed the\l"
	.string "hungry, and create new opportunities.\p"
	.string "Perhaps I was too absorbed in my\n"
	.string "calculations, too focused on grand\l"
	.string "designs to notice the subtle truths.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "It's ironic...\p"
	.string "ARCHIE'S ideals aren't so different from\n"
	.string "mine after all.\p"
	.string "We both sought a better world, yet in my\p"
	.string "ambition to reshape the land, I may\n"
	.string "have overlooked the balance that\l"
	.string "sustains us.\p"
	.string "Nature isn't a formula to be solved,\n"
	.string "but a delicate system to be respected.\p"
	.string "Even the smallest seeds can grow into\n"
	.string "mighty forests if tended properly.\p"
	.string "Perhaps small, considerate actions\n"
	.string "will lead to the change we seek...\p"
	.string "I won't abandon my vision, but maybe\n"
	.string "there's a better path...\p"
	.string "One that avoids catastrophe.$"
