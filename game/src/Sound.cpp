#include "Sound.h"

Sound::Sound(GameObject* associated)  : Component(associated){
	chunk = nullptr;
	this->associated = associated;
}
Sound::Sound(GameObject* associated, string file)  : Component(associated){
	chunk = nullptr;
	this->associated = associated;
	Open(file);	
}

Sound::~Sound(){}

void Sound::Play (int times){
	channel = Mix_PlayChannel(-1, chunk, times-1);
}

void Sound::Stop(){

	Mix_HaltChannel(channel);
}

void Sound::Open(string file){

	chunk = Resources::GetSound(file);
}
bool Sound::IsOpen(){
	if (chunk == nullptr)
        return(false);
    else
        return(true);
}
void Sound::Update(float dt){
	if (DieOnFinish && !Mix_Playing(channel)){
		associated->RequestDelete();
	}
}
void Sound::Render(){}
bool Sound::Is(string type){
	return(type == "sound");
}

void Sound::KillOnFinish(){
	DieOnFinish = true;
}