#ifndef GAMEDATA
#define GAMEDATA

#define STAGE1_BACKGROUND "assets/img/6000x600.png"
#define STAGE1_TILESET "assets/img/tileset.png"
#define STAGE1_GROUND_ENEMY_IDLE_ANIMATION "assets/img/Louva-God.png"

#define PLATFORM_TYPE1 "assets/map/Platform.txt"

#define PROTAGONIST_IDLE_ANIMATION "assets/img/Fightpose.png"
#define PROTAGONIST_RUN_ANIMATION "assets/img/Run_Sprite.png"

class GameData{
	public:
		GameData();
		~GameData();
		static bool playerVictory;
		
};
#endif