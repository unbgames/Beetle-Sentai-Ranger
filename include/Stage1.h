#ifndef STAGE1
#define STAGE1

#include "State.h"
#include "Sprite.h"
#include "Protagonist.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Music.h"
#include "TileSet.h"
#include "Platform.h"
#include "GroundEnemy.h"
#include "FlyingEnemy.h"
#include "Collision.h"
#include "BossStage1.h"

class Stage1 : public State{
	public:
		Stage1(int nEnemy);
		~Stage1();

		void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();

        void SpawnEnemy();
        void SpawnFlyingEnemy();

    private:
        Music backgroundIntro;
        Music backgroundLoop;
        int TotalEnemy;	
};

#endif