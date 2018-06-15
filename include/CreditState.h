#ifndef CREDITSTATE
#define CREDITSTATE

#include "State.h"
#include "GameObject.h"
#include "Text.h"
#include "Music.h"
#include "GameData.h"
#include "Sprite.h"
#include "Timer.h"
#include <fstream>

using namespace std;

class CreditState : public State{
    public:
        CreditState(string File);
        ~CreditState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();

    private:
        Music backgroundMusic;
        ifstream file;
        Timer wait;

};

#endif