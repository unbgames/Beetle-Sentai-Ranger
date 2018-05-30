#ifndef MUSIC
#define MUSIC

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <string>
#include "Resources.h"

using namespace std;

class Music{
    public:
        Music();
        Music(string file);
        ~Music();
        
        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(string file);
        bool IsOpen();
        bool IsPlaying();

    private:
        Mix_Music* music = nullptr;
};

#endif