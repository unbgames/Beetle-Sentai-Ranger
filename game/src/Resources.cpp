#include "Resources.h"

unordered_map<string, SDL_Texture*> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;
unordered_map<string, TTF_Font*> Resources::fontTable;

Resources::Resources(){}
Resources::~Resources(){}
SDL_Texture* Resources::GetImage(string file){

	Game* game = Game::GetInstance();
	SDL_Texture* aux;
	unordered_map<string,SDL_Texture*>::const_iterator ancora = imageTable.find(file);

	if(ancora == imageTable.end()){
		aux = IMG_LoadTexture(game->GetRenderer(), file.c_str());
		if (aux == nullptr) {
	    	SDL_Log("Unable to initialize texture: %s", SDL_GetError());
	    	exit(1);
		}
		imageTable.emplace(file, aux);
	}
	else{
		aux = ancora->second;
	}
	
	return(aux);	
}
void Resources::ClearImages (){
	unordered_map<string,SDL_Texture*>::const_iterator aux;

	for (aux = imageTable.begin(); aux != imageTable.end(); ++aux){
		SDL_DestroyTexture(aux->second);
	}

	imageTable.clear();
}

Mix_Music* Resources::GetMusic(string file){
	Mix_Music* aux;
	unordered_map<string,Mix_Music*>::const_iterator ancora = musicTable.find (file);

	if(ancora == musicTable.end()){
		aux = Mix_LoadMUS(file.c_str());
		if (aux == nullptr){
	    	SDL_Log("Unable to initialize chunk: %s", Mix_GetError());
	    	exit(1);
		}
		musicTable.emplace(file, aux);
	}
	else{
		aux = ancora->second;
	}
	
	return(aux);
}
void Resources::ClearMusics (){

    unordered_map<string,Mix_Music*>::const_iterator aux;

	for (aux = musicTable.begin(); aux != musicTable.end(); ++aux){
		//aux->second->Mix_FadeOutMusic(1500);
		Mix_FreeMusic(aux->second);
	}

	musicTable.clear();
}

Mix_Chunk* Resources::GetSound(string file){
	Mix_Chunk* aux;
	unordered_map<string,Mix_Chunk*>::const_iterator ancora = soundTable.find (file);

	if(ancora == soundTable.end()){
		aux = Mix_LoadWAV(file.c_str());
		if (aux == nullptr){
	    	SDL_Log("Unable to initialize chunk: %s", Mix_GetError());
	    	exit(1);
		}
		soundTable.emplace(file, aux);
	}
	else{
		aux = ancora->second;
	}
	
	return(aux);
}
void Resources::ClearSounds (){
	
	unordered_map<string,Mix_Chunk*>::const_iterator aux;

	for (aux = soundTable.begin(); aux != soundTable.end(); ++aux){
		//Mix_HaltChannel();
		Mix_FreeChunk(aux->second);
	}

	soundTable.clear();
}

TTF_Font* Resources::GetFont(string file, int ptsize){
	TTF_Font* aux;
	unordered_map<string,TTF_Font*>::const_iterator ancora = fontTable.find(file + to_string(ptsize));

	if(ancora == fontTable.end()){
		aux = TTF_OpenFont(file.c_str(), ptsize);
		if (aux == nullptr){
	    	SDL_Log("Unable to initialize font: %s", TTF_GetError());
	    	exit(1);
		}
		fontTable.emplace(file + to_string(ptsize), aux);
	}
	else{
		aux = ancora->second;
	}
	
	return(aux);
}
void Resources::ClearFonts(){

	unordered_map<string,TTF_Font*>::const_iterator aux;

	for (aux = fontTable.begin(); aux != fontTable.end(); ++aux){
		TTF_CloseFont(aux->second);
	}

	fontTable.clear();
}