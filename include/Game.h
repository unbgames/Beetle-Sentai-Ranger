#ifndef GAME
#define GAME

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include <iostream>
#include "State.h"
#include "InputManager.h"
#include "Resources.h"
#include <string>
#include <time.h>

using namespace std;

class State;

class Game{
    public:
        static Game* GetInstance();
        SDL_Renderer* GetRenderer();
        State* GetCurrentState();
        void Push(State* state);
        float GetDeltaTime();   

        ~Game();
        void Run();

    private:
        static Game* instance;
        SDL_Renderer* renderer;
        State* storedState;
        SDL_Window* window;
        int frameStart = 0;
        float dt;
        stack<unique_ptr<State>> stateStack;
        void CalculateDeltaTime();
        Game(string title, int width, int height);   
};

#endif