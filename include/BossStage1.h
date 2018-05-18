#ifndef BOSSSTAGE1
#define BOSSSTAGE1

#include "State.h"
#include "Sprite.h"
#include "Protagonist.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Music.h"
#include "TileSet.h"
#include "Platform.h"
#include "GroundEnemy.h"
#include "Collision.h"

class BossStage1 : public State{
	public:
		BossStage1(float x, float y);
		~BossStage1();
		
		void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();

    private:
        Music backgroundMusic;
        Vec2 PlayerPos;
};

#endif