const struct SaveBlock2_v0* sOldSaveBlock2Ptr = (struct SaveBlock2_v0*)(locations[SECTOR_ID_SAVEBLOCK2].data);
const struct SaveBlock1_v0* sOldSaveBlock1Ptr = (struct SaveBlock1_v0*)(locations[SECTOR_ID_SAVEBLOCK1_START].data);
const struct PokemonStorage* sOldPokemonStoragePtr = (struct PokemonStorage*)(locations[SECTOR_ID_PKMN_STORAGE_START].data);

bool8 UpdateSave_v0_v1(const struct SaveSectorLocation *locations)
{
    gSaveBlock2Ptr->playerGender = sOldSaveBlock2Ptr->playerGender;
    gSaveBlock2Ptr->playerApprentice = sOldSaveBlock2Ptr->playerApprentice;
    gSaveBlock1Ptr->pos = sOldSaveBlock1Ptr->pos;
    CpuCopy16(&sOldSaveBlock1Ptr->pokeblocks, &gSaveBlock1Ptr->pokeblocks, sizeof(gSaveBlock1Ptr->pokeblocks));
    CpuCopy16(&sOldSaveBlock1Ptr->seen1, &gSaveBlock1Ptr->seen1, sizeof(gSaveBlock1Ptr->seen1));
    CpuCopy16(&sOldSaveBlock1Ptr->flags, &gSaveBlock1Ptr->flags, sizeof(gSaveBlock1Ptr->flags));

    SetContinueGameWarpStatus();
    gSaveBlock1Ptr->continueGameWarp = gSaveBlock1Ptr->lastHealLocation;
}

struct SaveBlock2_v0
{
    /*0x00*/ u8 playerName[7 + 1];
    /*0x08*/ u8 playerGender; // MALE, FEMALE
    /*0x09*/ u8 specialSaveWarpFlags;
    /*0x0A*/ u8 playerTrainerId[4];
    /*0x0E*/ u16 playTimeHours;
    /*0x10*/ u8 playTimeMinutes;
    /*0x11*/ u8 playTimeSeconds;
    /*0x12*/ u8 playTimeVBlanks;
    /*0x13*/ u8 optionsButtonMode;  // OPTIONS_BUTTON_MODE_[NORMAL/LR/L_EQUALS_A]
    /*0x14*/ u16 optionsTextSpeed:3; // OPTIONS_TEXT_SPEED_[SLOW/MID/FAST]
             u16 optionsWindowFrameType:5; // Specifies one of the 20 decorative borders for text boxes
             u16 optionsSound:1; // OPTIONS_SOUND_[MONO/STEREO]
             u16 optionsBattleStyle:1; // OPTIONS_BATTLE_STYLE_[SHIFT/SET]
             u16 optionsBattleSceneOff:1; // whether battle animations are disabled
             u16 regionMapZoom:1; // whether the map is zoomed in
             u16 optionsBikeMusic:1; // whether the bike music plays when riding
             u16 optionsSurfMusic:1; // whether the surf music plays when surfing
             u16 optionsSurfOverworld:1; // whether to use the original Surf blob or dynamic blob (False to use dynamic)
             u16 optionsBattleItemAnimation:3; // whether the battle animation is reduced or not
    /*0x18*/ struct Pokedex pokedex;
    /*0x90*/ u8 filler_90[0x8];
    /*0x98*/ struct Time localTimeOffset;
    /*0xA0*/ struct Time lastBerryTreeUpdate;
    /*0xA8*/ u32 gcnLinkFlags; // Read by Pokémon Colosseum/XD
    /*0xAC*/ u32 encryptionKey;
    /*0xB0*/ struct PlayersApprentice playerApprentice;
    /*0xDC*/ struct Apprentice apprentices[4];
    /*0x1EC*/ struct BerryCrush berryCrush;
    /*0x1FC*/ struct PokemonJumpRecords pokeJump;
    /*0x20C*/ struct BerryPickingResults berryPick;
    /*0x21C*/ struct RankingHall1P hallRecords1P[9][2][3]; // From record mixing.
    /*0x57C*/ struct RankingHall2P hallRecords2P[2][3]; // From record mixing.
    /*0x624*/ u16 contestLinkResults[5][4];
    /*0x64C*/ struct BattleFrontier frontier;
}; // sizeof=0xF2C

struct SaveBlock1_v0
{
    /*0x00*/ struct Coords16 pos;
    /*0x04*/ struct WarpData location;
    /*0x0C*/ struct WarpData continueGameWarp;
    /*0x14*/ struct WarpData dynamicWarp;
    /*0x1C*/ struct WarpData lastHealLocation; // used by white-out and teleport
    /*0x24*/ struct WarpData escapeWarp; // used by Dig and Escape Rope
    /*0x2C*/ u16 savedMusic;
    /*0x2E*/ u8 weather;
    /*0x2F*/ u8 weatherCycleStage;
    /*0x30*/ u8 flashLevel;
    /*0x31*/ //u8 padding1;
    /*0x32*/ u16 mapLayoutId;
    /*0x34*/ u16 mapView[0x100];
    /*0x234*/ u8 playerPartyCount;
    /*0x235*/ //u8 padding2[3];
    /*0x238*/ struct Pokemon playerParty[6];
    /*0x490*/ u32 money;
    /*0x494*/ u16 coins;
    /*0x496*/ u16 registeredItemSelect; // registered for use with SELECT button
    /*0x498*/ struct ItemSlot pcItems[50];
    /*0x560*/ struct ItemSlot bagPocket_Items[120];
    /*0x5D8*/ struct ItemSlot bagPocket_KeyItems[30];
    /*0x650*/ struct ItemSlot bagPocket_PokeBalls[16];
    /*0x690*/ struct ItemSlot bagPocket_TMHM[64];
    /*0x790*/ struct ItemSlot bagPocket_Berries[46];
    /*0x848*/ struct Pokeblock pokeblocks[40];
    /*0x988*/ u8 seen1[NUM_DEX_FLAG_BYTES];
    /*0x9BC*/ u16 berryBlenderRecords[3];
    /*0x9C2*/ u8 unused_9C2[6];
    /*0x9C8*/ u16 trainerRematchStepCounter;
    /*0x9CA*/ u8 trainerRematches[100];
    /*0xA2E*/ //u8 padding3[2];
    /*0xA30*/ struct ObjectEvent objectEvents[16];
    /*0xC70*/ struct ObjectEventTemplate objectEventTemplates[64];
    /*0x1270*/ u8 flags[NUM_FLAG_BYTES];
    /*0x139C*/ u16 vars[VARS_COUNT];
    /*0x159C*/ u32 gameStats[64];
    /*0x169C*/ struct BerryTree berryTrees[128];
    /*0x1A9C*/ struct SecretBase secretBases[20];
    /*0x271C*/ u8 playerRoomDecorations[12];
    /*0x2728*/ u8 playerRoomDecorationPositions[12];
    /*0x2734*/ u8 decorationDesks[10];
    /*0x273E*/ u8 decorationChairs[10];
    /*0x2748*/ u8 decorationPlants[10];
    /*0x2752*/ u8 decorationOrnaments[30];
    /*0x2770*/ u8 decorationMats[30];
    /*0x278E*/ u8 decorationPosters[10];
    /*0x2798*/ u8 decorationDolls[40];
    /*0x27C0*/ u8 decorationCushions[10];
    /*0x27CA*/ //u8 padding4[2];
    /*0x27CC*/ TVShow tvShows[5 + 20];
    /*0x2B50*/ PokeNews pokeNews[16];
    /*0x2B90*/ u16 outbreakPokemonSpecies;
    /*0x2B92*/ u8 outbreakLocationMapNum;
    /*0x2B93*/ u8 outbreakLocationMapGroup;
    /*0x2B94*/ u8 outbreakPokemonLevel;
    /*0x2B95*/ u8 outbreakUnused1;
    /*0x2B96*/ u16 outbreakUnused2;
    /*0x2B98*/ u16 outbreakPokemonMoves[4];
    /*0x2BA0*/ u8 outbreakUnused3;
    /*0x2BA1*/ u8 outbreakPokemonProbability;
    /*0x2BA2*/ u16 outbreakDaysLeft;
    /*0x2BA4*/ struct GabbyAndTyData gabbyAndTyData;
    /*0x2BB0*/ u16 easyChatProfile[6];
    /*0x2BBC*/ u16 easyChatBattleStart[6];
    /*0x2BC8*/ u16 easyChatBattleWon[6];
    /*0x2BD4*/ u16 easyChatBattleLost[6];
    /*0x2BE0*/ struct Mail mail[10 + 6];
    /*0x2E20*/ u8 unlockedTrendySayings[NUM_TRENDY_SAYING_BYTES]; // Bitfield for unlockable Easy Chat words in EC_GROUP_TRENDY_SAYING
    /*0x2E25*/ //u8 padding5[3];
    /*0x2E28*/ OldMan oldMan;
    /*0x2e64*/ struct DewfordTrend dewfordTrends[5];
    /*0x2e90*/ struct ContestWinner contestWinners[13]; // see CONTEST_WINNER_*
    /*0x3030*/ struct DayCare daycare;
    /*0x3150*/ struct LinkBattleRecords linkBattleRecords;
    /*0x31A8*/ u8 giftRibbons[11];
    /*0x31B3*/ struct ExternalEventData externalEventData;
    /*0x31C7*/ struct ExternalEventFlags externalEventFlags;
    /*0x31DC*/ struct Roamer roamer;
    /*0x31F8*/ struct EnigmaBerry enigmaBerry;
    /*0x322C*/ struct MysteryGiftSave mysteryGift;
    /*0x3598*/ u8 unused_3598[0x18];
    /*0x3718*/ u32 trainerHillTimes[4];
    /*0x3728*/ struct RamScript ramScript;
    /*0x3B14*/ struct RecordMixingGift recordMixingGift;
    /*0x3B24*/ u8 seen2[NUM_DEX_FLAG_BYTES];
    /*0x3B58*/ LilycoveLady lilycoveLady;
    /*0x3B98*/ struct TrainerNameRecord trainerNameRecords[20];
    /*0x3C88*/ u8 registeredTexts[10][21];
    /*0x3D5A*/ u8 unused_3D5A[10];
    /*0x3D64*/ struct TrainerHillSave trainerHill;
    /*0x3D70*/ struct WaldaPhrase waldaPhrase;
               u8 registeredItemLastSelected:4; //max 16 items
               u8 registeredItemListCount:4;
               struct RegisteredItemSlot registeredItems[10];
    // sizeof: 0x3D88
};