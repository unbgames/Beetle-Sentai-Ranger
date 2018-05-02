#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "Music.h"

Music::Music(){
    music = nullptr;
}

Music::Music(string file){
    music = nullptr;
    Open(file);
}

Music::~Music(){}

void Music::Play(int times){
    Mix_PlayMusic(music, times);
}

void Music::Stop(int msToStop){
    Mix_FadeOutMusic(msToStop);
}  

void Music::Open(string file){
    music = Resources::GetMusic(file);
}
bool Music::IsOpen(){
    if (music == nullptr)
        return(false);
    else
        return(true);
    
}
