#ifndef MAINMENU
#define MAINMENU

#define CURSOR_INDEX_MAX 3 // Começa com o zero, que é Play

#include "State.h"
#include "Sprite.h"
#include "Protagonist.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Music.h"
#include "Sound.h"
#include "CreditState.h"
#include "PVPState.h"

class MainMenu : public State{
	public:
		MainMenu();
		~MainMenu();

		void LoadAssets();
	    void Update(float dt);
	    void Render();

	    void Start();
	    void Pause();
	    void Resume();

    private:
        Music backgroundIntro;
        Music backgroundLoop;
		int cursorIndex = 0;

		GameObject* cursor;
		GameObject* buttonPressed;
		Sprite* spriteCursor;
		Sprite* spriteButton;
};

#endif
