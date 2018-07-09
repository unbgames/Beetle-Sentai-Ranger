#ifndef CUTSCENES
#define CUTSCENES

#include "State.h"
#include "Sprite.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Music.h"
#include "Text.h"
#include <iostream>
#include <fstream>

class Cutscenes : public State{
	public:
		Cutscenes();
		~Cutscenes();

		void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();

    private:
        Music cutsceneMusic;

				GameObject* cutscene = nullptr;
				Sprite* spriteCutscene = nullptr;

				GameObject* cutscenePanel = nullptr;
				Sprite* spriteCutscenePanel = nullptr;

				GameObject* cutsceneDialog = nullptr;
				Text* textCutsceneDialog = nullptr;

				SDL_Color color = {0,0,0,0};

				int cutsceneIndex = 0;

				void PrintScene();
};

#endif
