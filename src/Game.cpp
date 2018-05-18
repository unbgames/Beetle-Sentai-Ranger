#include "Game.h"

Game* Game::instance = nullptr;

Protagonist* GameData::Player = nullptr;

Game* Game::GetInstance(){
	if (instance == nullptr){
		instance = new Game("Beetle Sentai Ranger", 1024, 600);
	}
	return(instance);
}

State* Game::GetCurrentState(){
	return(stateStack.top().get());
}

SDL_Renderer* Game::GetRenderer(){
	return(renderer);
}

void Game::Push(State* state){
	storedState = state;
}

void Game::Run(){

	State* state;
	InputManager& input = InputManager::GetInstance();

	if (storedState == nullptr){
		return;
	}

	state = storedState;
	stateStack.push(unique_ptr<State>(storedState));
	storedState = nullptr;
	
	state->Start();
	
	while(!(state->QuitRequested() || stateStack.empty())){
		CalculateDeltaTime();
		SDL_Log("%d", stateStack.size());

		state = stateStack.top().get();
		
		input.Update();
		state->Update(dt);
		state->Render();
		SDL_RenderPresent(renderer);

		if(state->PopRequested()){
			stateStack.pop();
			
			if(!stateStack.empty()){
				state = stateStack.top().get();
				state->Resume();
			}
		}

		if(storedState != nullptr){
			if(!stateStack.empty())
				state->Pause();
			
			stateStack.push(unique_ptr<State>(storedState));
			storedState->Start();
			storedState = nullptr;

			state = stateStack.top().get();
			state->Resume();
		}

		SDL_Delay(33);
	}

	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();
}

Game::~Game(){

	if (storedState != nullptr){
		delete storedState;
	}
	while(!stateStack.empty()){
		stateStack.pop();
	}

	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

Game::Game(string title, int width, int height){
	if (instance == nullptr){
		instance = this;
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
    	SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    	exit(1);
	}

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
    	SDL_Log("Unable to initialize IMG: %s", IMG_GetError());
    	exit(1);
	}

	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	Mix_AllocateChannels(32);

	if (TTF_Init() != 0){
		SDL_Log("Unable to initialize TTF: %s", TTF_GetError());
    	exit(1);
	}
	
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if(window == 0) {
    	SDL_Log("Unable to initialize window: %s", SDL_GetError());
    	exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == 0) {
    	SDL_Log("Unable to initialize renderer: %s", SDL_GetError());
    	exit(1);
	}

	storedState = nullptr;

}

void Game::CalculateDeltaTime(){
	int aux = SDL_GetTicks();

	dt = aux - frameStart;
	frameStart = aux;

	dt = dt/1000; 
}

float Game::GetDeltaTime(){
	return(dt);
}