#ifndef LOSESTATE
#define LOSESTATE

#include "State.h"
#include "GameObject.h"
#include "Text.h"
#include "Music.h"
#include "GameData.h"
#include "Sprite.h"

class LoseState : public State{
    public:
        LoseState();
        ~LoseState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();

    private:
        Music backgroundMusic;

};

#endif