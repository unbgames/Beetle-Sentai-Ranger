#ifndef OPTIONS
#define OPTIONS

#define CURSOR_INDEX_OPTIONS_MAX 1 // Começa com o zero, que é Back

#include "State.h"
#include "Sprite.h"
#include "Protagonist.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Music.h"
#include "Text.h"
#include <iostream>
#include <fstream>

class Options : public State{
	public:
		Options();
		~Options();

		void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();

    private:
       // Music backgroundIntroOptions;
        //Music backgroundLoopOptions;
				int cursorIndexOptions = 0;

				GameObject* cursorOptions;
				GameObject* buttonPressedOptions;
				GameObject* iconChange;
				Sprite* spriteCursorOptions;
				Sprite* spriteButtonOptions;
				Sprite* spriteIconChange;

				std::string keyPrint = " Key";

				bool configStart = false;
				bool iconChangeOnScreen = false;

				int configButtons [9];
				int indexConfig = 0;
};

#endif
