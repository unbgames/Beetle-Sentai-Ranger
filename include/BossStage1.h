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
#include "Frog.h"
#include "LoseState.h"
#include "CreditState.h"

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
        Music backgroundIntro;
        Music backgroundLoop;
        Vec2 PlayerPos;
};

#endif