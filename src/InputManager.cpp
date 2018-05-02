#include "InputManager.h"

void InputManager::Update(){

	SDL_Event event;
	SDL_GetMouseState(&mouseX, &mouseY);
	quitRequested = false;
	updateCounter++;

	while (SDL_PollEvent(&event)){

		if(event.type == SDL_QUIT){
			quitRequested = true;
		}
		if(event.type == SDL_MOUSEBUTTONDOWN){
			mouseState[event.button.button] = true;
			mouseUpdate[event.button.button] = updateCounter;
		}
		if(event.type == SDL_MOUSEBUTTONUP){
			mouseState[event.button.button] = false;
			mouseUpdate[event.button.button] = updateCounter;
		}
		if(event.type == SDL_KEYDOWN && event.key.repeat == 0){
				keyState[event.key.keysym.sym] = true;
				keyUpdate[event.key.keysym.sym] = updateCounter;	
		}
		if(event.type == SDL_KEYUP){
			keyState[event.key.keysym.sym] = false;
			keyUpdate[event.key.keysym.sym] = updateCounter;
		}
	}
}
bool InputManager::KeyPress(int key){
	return(updateCounter == keyUpdate[key] && keyState[key]);
}
bool InputManager::KeyRelease(int key){
	return(updateCounter == keyUpdate[key] && !keyState[key]);
}
bool InputManager::IsKeyDown(int key){
	return(keyState[key]);
}

bool InputManager::MousePress(int button){
	return(updateCounter == mouseUpdate[button] && mouseState[button]);
}
bool InputManager::MouseRelease(int button){
	return(updateCounter == mouseUpdate[button] && !mouseState[button]);
}
bool InputManager::IsMouseDown(int button){
	return(mouseState[button]);
}

int InputManager::GetMouseX(){
	return(mouseX);
}
int InputManager::GetMouseY(){
	return(mouseY);
}
bool InputManager::QuitRequested(){
	return(quitRequested);
}
InputManager& InputManager::GetInstance(){

	static InputManager manager;
	return(manager);
}

InputManager::InputManager(){
	bool mouseState[6] = {0};
	int mouseUpdate[6] = {0};
}
InputManager::~InputManager(){}