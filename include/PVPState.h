#ifndef PVPSTATE
#define PVPSTATE

#include "State.h"
#include "Sprite.h"
#include "Protagonist.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Music.h"
#include "Collision.h"
#include "MainMenu.h"
#include "Player1.h"
#include "Player2.h"

class PVPState : public State{
	public:
		PVPState();
		~PVPState();

		void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();

    private:
        Music backgroundIntro;
        Music backgroundLoop;
};

#endif
