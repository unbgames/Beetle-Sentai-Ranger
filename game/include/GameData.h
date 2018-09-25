#ifndef GAMEDATA
#define GAMEDATA

#include "config.h"

#define FONT ASSETS_PATH("/font/orange kid.ttf")
#define LOSE_BACKGROUND ASSETS_PATH("/img/End/GameOver_00.png")
#define LOSE_MUSIC ASSETS_PATH("/audio/Musics/TemaGameOver.ogg")
#define WIN_MUSIC ASSETS_PATH("/audio/Musics/TemaVitoria.ogg")
#define CREDIT_TEXT ASSETS_PATH("/map/Credits.txt")
#define CREDIT_SCENE ASSETS_PATH("/img/Creditos/scene_final.jpg")
#define CREDIT_MUSIC ASSETS_PATH("/audio/Musics/TemaCreditos.ogg")

#define MAINMENU_BACKGROUND ASSETS_PATH("/img/Menu/main_menu_v2.png")
#define MAINMENU_LOGO ASSETS_PATH("/img/Menu/logo.png")
#define MAINMENU_PLAY_BUTTON_NOTPRESSED ASSETS_PATH("/img/Menu/play_button_notpressed.png")
#define MAINMENU_PLAY_BUTTON_PRESSED ASSETS_PATH("/img/Menu/play_button_pressed.png")
#define MAINMENU_EXIT_BUTTON_NOTPRESSED ASSETS_PATH("/img/Menu/exit_button_notpressed.png")
#define MAINMENU_EXIT_BUTTON_PRESSED ASSETS_PATH("/img/Menu/exit_button_pressed.png")
#define MAINMENU_OPTIONS_BUTTON_NOTPRESSED ASSETS_PATH("/img/Menu/options_button_notpressed.png")
#define MAINMENU_OPTIONS_BUTTON_PRESSED ASSETS_PATH("/img/Menu/options_button_pressed.png")
#define MAINMENU_VERSUS_BUTTON_NOTPRESSED ASSETS_PATH("/img/Menu/pvp_button_notpressed.png")
#define MAINMENU_VERSUS_BUTTON_PRESSED ASSETS_PATH("/img/Menu/pvp_button_pressed.png")
#define MAINMENU_CURSOR ASSETS_PATH("/img/Menu/mouse2.png")
#define MAINMENU_CURSOR_SOUND ASSETS_PATH("/audio/Sounds/5. Outros/Click.wav")

#define MAINMENU_BACKGROUNDMUSIC_INTRO ASSETS_PATH("/audio/Musics/TemaMenuIntro.ogg")
#define MAINMENU_BACKGROUNDMUSIC_LOOP ASSETS_PATH("/audio/Musics/TemaMenuLoop.ogg")

#define CUTSCENES_PANEL ASSETS_PATH("/img/TextBox/Textbox2.png")
#define CUTSCENES_MUSIC ASSETS_PATH("/audio/Musics/TemaCutscene.ogg")
#define CUTSCENES_MUSIC_1 ASSETS_PATH("/audio/Musics/TemaCutscene1.ogg")
#define CUTSCENES_MUSIC_2 ASSETS_PATH("/audio/Musics/TemaCutscene2.ogg")
#define CUTSCENES_MUSIC_3 ASSETS_PATH("/audio/Musics/TemaCutscene3.ogg")
#define CUTSCENES_MUSIC_4 ASSETS_PATH("/audio/Musics/TemaCutscene4.ogg")
#define CUTSCENES_1 ASSETS_PATH("/img/Cutscenes/scene1.png")
#define CUTSCENES_2 ASSETS_PATH("/img/Cutscenes/scene2.png")
#define CUTSCENES_3 ASSETS_PATH("/img/Cutscenes/scene3.png")
#define CUTSCENES_FINAL ASSETS_PATH("/img/Cutscenes/scene_final.png")

#define OPTIONS_BACKGROUND ASSETS_PATH("/img/Menu/options_menu_v2.png")
#define OPTIONS_PANEL ASSETS_PATH("/img/Menu/options_panel.png")
#define OPTIONS_BACK_BUTTON_NOTPRESSED ASSETS_PATH("/img/Menu/back_button_notpressed.png")
#define OPTIONS_BACK_BUTTON_PRESSED ASSETS_PATH("/img/Menu/back_button_pressed.png")
#define OPTIONS_CHANGE_BUTTON_NOTPRESSED ASSETS_PATH("/img/Menu/change_button_notpressed.png")
#define OPTIONS_CHANGE_BUTTON_PRESSED ASSETS_PATH("/img/Menu/change_button_pressed.png")
#define OPTIONS_UP_ICON ASSETS_PATH("/img/FristPlane/Up.png")
#define OPTIONS_DOWN_ICON ASSETS_PATH("/img/FristPlane/Down.png")
#define OPTIONS_LEFT_ICON ASSETS_PATH("/img/FristPlane/Left.png")
#define OPTIONS_RIGHT_ICON ASSETS_PATH("/img/FristPlane/Right.png")
#define OPTIONS_PUNCH_ICON ASSETS_PATH("/img/FristPlane/Punch.png")

#define PLATFORM_TYPE1 ASSETS_PATH("/map/terreno_platform.txt")
#define COLUMN_TYPE1 ASSETS_PATH("/map/terreno_column1.txt")
#define COLUMN_TYPE2 ASSETS_PATH("/map/terreno_column2.txt")
#define COLUMN_TYPE3 ASSETS_PATH("/map/terreno_column3.txt")
#define TERRAIN_TYPE1 ASSETS_PATH("/map/terreno_terrain1.txt")
#define TERRAIN_TYPE2 ASSETS_PATH("/map/terreno_terrain2.txt")
#define TERRAIN_TYPE3 ASSETS_PATH("/map/terreno_terrain3.txt")
#define TERRAIN_TYPE4 ASSETS_PATH("/map/terreno_terrain4.txt")
#define TERRAIN_TYPE5 ASSETS_PATH("/map/terreno_terrain5.txt")
#define TERRAIN_TYPE6 ASSETS_PATH("/map/terreno_terrain6.txt")
#define TERRAIN_TYPE7 ASSETS_PATH("/map/terreno_terrain7.txt")
#define TERRAIN_CHAO ASSETS_PATH("/map/terreno_chao_fase.txt")
#define TERRAIN_BOSS ASSETS_PATH("/map/terreno_chao_boss.txt")

#define HUD_ACID_ICON ASSETS_PATH("/img/FristPlane/Acid.png")
#define HUD_ACID_COOLDOWN_ICON ASSETS_PATH("/img/FristPlane/Acid_cooldown.png")
#define HUD_DASH_ICON ASSETS_PATH("/img/FristPlane/Dash.png")
#define HUD_DASH_COOLDOWN_ICON ASSETS_PATH("/img/FristPlane/Dash_cooldown.png")
#define HUD_SHIT_ICON ASSETS_PATH("/img/FristPlane/Shit.png")
#define HUD_SHIT_COOLDOWN_ICON ASSETS_PATH("/img/FristPlane/Shit_cooldown.png")
#define HUD_FLY_ICON ASSETS_PATH("/img/FristPlane/Wings.png")
#define HUD_FLY_COOLDOWN_ICON ASSETS_PATH("/img/FristPlane/Wings_cooldown.png")
#define HUD_HEALTHBAR ASSETS_PATH("/img/FristPlane/Life.png")


#define PROTAGONIST_IDLE_ANIMATION ASSETS_PATH("/img/Beetle/Fightpose.png")
#define PROTAGONIST_RUN_ANIMATION ASSETS_PATH("/img/Beetle/Run_sprite_.png")
#define PROTAGONIST_JUMP_ANIMATION ASSETS_PATH("/img/Beetle/Jump Beetle2.png")
#define PROTAGONIST_SHITBALL_ANIMATION ASSETS_PATH("/img/Beetle/PooAttack.png")
#define PROTAGONIST_ACID_ANIMATION ASSETS_PATH("/img/Beetle/Acid.png")
#define PROTAGONIST_PUNCH_ANIMATION ASSETS_PATH("/img/Beetle/Punch_spritesheet.png")
#define PROTAGONIST_DEATH_ANIMATION ASSETS_PATH("/img/Beetle/Death.png")
#define PROTAGONIST_DASH_ANIMATION ASSETS_PATH("/img/Beetle/Dash.png")
#define PROTAGONIST_FLY_ANIMATION ASSETS_PATH("/img/Beetle/BeetleFly.png")
#define PROTAGONIST_GETHURT_ANIMATION ASSETS_PATH("/img/Beetle/Dano.png")
#define PROTAGONIST_DEATH_SOUND ASSETS_PATH("/audio/Sounds/1. Besouro/Morrendo1.wav")
#define PROTAGONIST_ACID_SOUND ASSETS_PATH("/audio/Sounds/1. Besouro/AtirandoAcido.wav")
#define PROTAGONIST_ACID_HIT_SOUND ASSETS_PATH("/audio/Sounds/1. Besouro/AcertandoAcido.wav")
#define PROTAGONIST_PUNCH_SOUND ASSETS_PATH("/audio/Sounds/1. Besouro/Soco1.wav")
#define PROTAGONIST_PUNCH_HIT_SOUND ASSETS_PATH("/audio/Sounds/1. Besouro/AcertandoSoco.wav")
#define PROTAGONIST_SHIT_SOUND ASSETS_PATH("/audio/Sounds/1. Besouro/AtirandoBosta.wav")
#define PROTAGONIST_DASH_SOUND ASSETS_PATH("/audio/Sounds/1. Besouro/Dash.wav")
#define PROTAGONIST_FLY_SOUND ASSETS_PATH("/audio/Sounds/1. Besouro/Voo.wav")
#define PROTAGONIST_GETHURT_SOUND ASSETS_PATH("/audio/Sounds/1. Besouro/TomandoDano4.wav")

#define PVPSTATE_BACKGROUNDMUSIC_INTRO ASSETS_PATH("/audio/Musics/TemaPvPIntro.ogg")
#define PVPSTATE_BACKGROUNDMUSIC_LOOP ASSETS_PATH("/audio/Musics/TemaPvPLoop.ogg")
#define PLAYER2_IDLE_ANIMATION ASSETS_PATH("/img/Beetle2/Fightpose.png")
#define PLAYER2_RUN_ANIMATION ASSETS_PATH("/img/Beetle2/Run_sprite_.png")
#define PLAYER2_JUMP_ANIMATION ASSETS_PATH("/img/Beetle2/Jump Beetle2.png")
#define PLAYER2_SHITBALL_ANIMATION ASSETS_PATH("/img/Beetle2/PooAttack.png")
#define PLAYER2_ACID_ANIMATION ASSETS_PATH("/img/Beetle2/Acid.png")
#define PLAYER2_PUNCH_ANIMATION ASSETS_PATH("/img/Beetle2/Punch_spritesheet.png")
#define PLAYER2_DEATH_ANIMATION ASSETS_PATH("/img/Beetle2/Death.png")
#define PLAYER2_DASH_ANIMATION ASSETS_PATH("/img/Beetle2/Dash.png")
#define PLAYER2_FLY_ANIMATION ASSETS_PATH("/img/Beetle2/BeetleFly.png")
#define PLAYER2_GETHURT_ANIMATION ASSETS_PATH("/img/Beetle2/Dano.png")

#define STAGE1_BACKGROUND ASSETS_PATH("/img/Background/BG1.png")
#define STAGE1_TILESET ASSETS_PATH("/img/Tileset/Tileset1_small.png")
#define STAGE1_TILESET_WIDTH 32
#define STAGE1_TILESET_HEIGHT 32
#define STAGE1_BACKGROUNDMUSIC_INTRO ASSETS_PATH("/audio/Musics/TemadaFlorestaIntro.ogg")
#define STAGE1_BACKGROUNDMUSIC_LOOP ASSETS_PATH("/audio/Musics/TemadaFlorestaLoop.ogg")

#define STAGE1_GROUND_ENEMY_IDLE_ANIMATION ASSETS_PATH("/img/GroundEnemy1/Louva-God.png")
#define STAGE1_GROUND_ENEMY_RUN_ANIMATION ASSETS_PATH("/img/GroundEnemy1/LouvaRun.png")
#define STAGE1_GROUND_ENEMY_PUNCH_ANIMATION ASSETS_PATH("/img/GroundEnemy1/Punch Louvagod_spritesheet.png")
#define STAGE1_GROUND_ENEMY_JUMP_ANIMATION ASSETS_PATH("/img/GroundEnemy1/Jumping.png")
#define STAGE1_GROUND_ENEMY_DEATH_ANIMATION ASSETS_PATH("/img/GroundEnemy1/Enemy death.png")
#define STAGE1_GROUND_ENEMY_GETHURT_ANIMATION ASSETS_PATH("/img/GroundEnemy1/Enemy hit.png")
#define STAGE1_GROUND_ENEMY_ATTACK_SOUND ASSETS_PATH("/audio/Sounds/2. Louva-Deus/Ataque.wav")
#define STAGE1_GROUND_ENEMY_ATTACK_HIT_SOUND ASSETS_PATH("/audio/Sounds/2. Louva-Deus/Acerto.wav")
#define STAGE1_GROUND_ENEMY_DEATH_SOUND ASSETS_PATH("/audio/Sounds/2. Louva-Deus/InsetoPisado.wav")

#define STAGE1_FLYING_ENEMY_IDLE_ANIMATION ASSETS_PATH("/img/FlyingEnemy1/RedFly.png")
#define STAGE1_FLYING_ENEMY_ATTACK_ANIMATION ASSETS_PATH("/img/FlyingEnemy1/AttackRed.png")
#define STAGE1_FLYING_ENEMY_DEATH_ANIMATION ASSETS_PATH("/img/FlyingEnemy1/RedGodDeath.png")
#define STAGE1_FLYING_ENEMY_BULLET_ANIMATION ASSETS_PATH("/img/FlyingEnemy1/FireRed.png")
#define STAGE1_FLYING_ENEMY_BULLET_SOUND ASSETS_PATH("/audio/Sounds/3. Inimigo Aéreo/AtirandoFogo.wav")
#define STAGE1_FLYING_ENEMY_DEATH_SOUND ASSETS_PATH("/audio/Sounds/2. Louva-Deus/InsetoPisado.wav")

#define STAGE1_BOSS_IDLE_ANIMATION ASSETS_PATH("/img/Frog/Pose Boss.png")
#define STAGE1_BOSS_RUN_ANIMATION ASSETS_PATH("/img/Frog/WalkFrog.png")
#define STAGE1_BOSS_SMASH_ATTACK_ANIMATION ASSETS_PATH("/img/Frog/SMASH.png")
#define STAGE1_BOSS_DOWN_ATTACK_ANIMATION ASSETS_PATH("/img/Frog/LínguaParaBaixo.png")
#define STAGE1_BOSS_UP_ATTACK_ANIMATION ASSETS_PATH("/img/Frog/LínguaParaCima.png")
#define STAGE1_BOSS_DEATH_ANIMATION ASSETS_PATH("/img/Frog/DeathFrog_DeathFrog01.png")
#define STAGE1_BOSS_SMASH_ATTACK_SOUND ASSETS_PATH("/audio/Sounds/4. Grande Sapo/Pulo.wav")
#define STAGE1_BOSS_TONGUE_ATTACK_SOUND ASSETS_PATH("/audio/Sounds/4. Grande Sapo/Linguada.wav")
#define STAGE1_BOSS_LAND_SOUND ASSETS_PATH("/audio/Sounds/4. Grande Sapo/Queda.wav")
#define STAGE1_BOSS_BACKGROUND ASSETS_PATH("/img/Background/Boss1.png")
#define STAGE1_BOSS_BACKGROUNDMUSIC_INTRO ASSETS_PATH("/audio/Musics/TemaBossIntro.ogg")
#define STAGE1_BOSS_BACKGROUNDMUSIC_LOOP ASSETS_PATH("/audio/Musics/TemaBossLoop.ogg")

class Protagonist;

class GameData{
	public:
		GameData();
		~GameData();
		static bool playerVictory;
		static Protagonist* Player;
};
#endif
