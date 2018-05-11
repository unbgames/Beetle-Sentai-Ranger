#ifndef GAMEDATA
#define GAMEDATA

#define STAGE1_BACKGROUND "assets/img/Background/6000x600.png"
#define STAGE1_TILESET "assets/img/Background/tileset.png"
#define STAGE1_GROUND_ENEMY_IDLE_ANIMATION "assets/img/GroundEnemy1/Louva-God.png"
#define STAGE1_GROUND_ENEMY_PUNCH_ANIMATION "assets/img/GroundEnemy1/Punch Louvagod_spritesheet.png"
#define STAGE1_BOSS_BACKGROUND "assets/img/Background/chefao600.png"
#define STAGE1_BACKGROUNDMUSIC "assets/audio/TemadaFloresta.wav"

#define PLATFORM_TYPE1 "assets/map/Platform.txt"

#define PROTAGONIST_IDLE_ANIMATION "assets/img/Beetle/Fightpose.png"
#define PROTAGONIST_RUN_ANIMATION "assets/img/Beetle/Run_sprite_.png"
#define PROTAGONIST_JUMP_ANIMATION "assets/img/Beetle/Jump_spritesheet.png"
#define PROTAGONIST_SHITBALL_ANIMATION "assets/img/Beetle/Poo.png"
#define PROTAGONIST_PUNCH_ANIMATION "assets/img/Beetle/Punch_spritesheet.png"

class GameData{
	public:
		GameData();
		~GameData();
		static bool playerVictory;
		
};
#endif