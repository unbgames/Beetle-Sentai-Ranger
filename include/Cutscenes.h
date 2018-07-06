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

				GameObject* cutscene;
				Sprite* spriteCutscene;

				GameObject* cutsceneDialog;
				Text* textCutsceneDialog;

				SDL_Color color = {255,255,255,0};

				int cutsceneIndex = 0;

				void PrintScene();
};

#endif
