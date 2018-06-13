#ifndef OPTIONS
#define OPTIONS

#define CURSOR_INDEX_OPTIONS_MAX 0 // Começa com o zero, que é Back

#include "State.h"
#include "Sprite.h"
#include "Protagonist.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Music.h"

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
        Music backgroundIntroOptions;
        Music backgroundLoopOptions;
				int cursorIndexOptions = 0;

				GameObject* cursorOptions;
				GameObject* buttonPressedOptions;
				Sprite* spriteCursorOptions;
				Sprite* spriteButtonOptions;
};

#endif
