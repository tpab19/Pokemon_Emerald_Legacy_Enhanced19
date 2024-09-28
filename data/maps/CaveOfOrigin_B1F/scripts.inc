.set LOCALID_WALLACE, 1

CaveOfOrigin_B1F_MapScripts::
	.byte 0

CaveOfOrigin_B1F_EventScript_Wallace::
	lock
	faceplayer
	msgbox CaveOfOrigin_B1F_Text_WallaceStory, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	playse SE_PIN
	applymovement LOCALID_WALLACE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLACE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	applymovement LOCALID_WALLACE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox CaveOfOrigin_B1F_Text_WellHeadToSkyPillar, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	fadescreenspeed FADE_TO_BLACK, 4
	setflag FLAG_WALLACE_GOES_TO_SKY_PILLAR
	setvar VAR_SOOTOPOLIS_CITY_STATE, 3
	removeobject LOCALID_WALLACE
	clearflag FLAG_HIDE_SKY_PILLAR_WALLACE
	fadescreen FADE_FROM_BLACK
	release
	end

CaveOfOrigin_B1F_Text_WallaceStory:
	.string "Ah, so you are {PLAYER}{KUN}?\p"
	.string "I've heard such marvelous tales of your\n"
	.string "exploits.\p"
	.string "My name is WALLACE.\p"
	.string "As the GYM LEADER of SOOTOPOLIS, I've\n"
	.string "spent my life immersed in its mysteries,\l"
	.string "its beauty.\p"
	.string "And now, here we are...\n"
	.string "standing amidst a legend.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "GROUDON and KYOGRE... such power.\p"
	.string "But according to the ancient carvings\n"
	.string "here in the CAVE OF ORIGIN, there is yet\l"
	.string "another being.\p"
	.string "A sacred POKéMON, known in legends\n"
	.string "as the DRAGON LORD.\p"
	.string "It is said that in times of strife, this\n"
	.string "ethereal being descended from the\l"
	.string "heavens to quell the chaos below.\p"
	.string "I believe that seeking out this\n"
	.string "DRAGON LORD may be our only hope.\p"
	.string "The SKY PILLAR, a monument to its\n"
	.string "majesty, lies waiting on ROUTE 131.\p"
	.string "I trust that we will find the answers we\n"
	.string "seek there.\p"
	.string "I've studied the carvings, and at long\n"
	.string "last...\p"
	.string "I believe I know how to unlock its\n"
	.string "secrets.$"

CaveOfOrigin_B1F_Text_WellHeadToSkyPillar:
	.string "WALLACE: {PLAYER}{KUN}, will you\n"
	.string "accompany me?\p"
	.string "There's not a moment to lose!\p"
	.string "Let us make haste to the SKY PILLAR.\n"
	.string "Time is of the essence!\p"
	.string "I will go ahead and prepare to open\n"
	.string "its entrance.\p"
	.string "Please meet me there as soon as you can.$"
