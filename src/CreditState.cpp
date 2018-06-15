#include "CreditState.h"

CreditState::CreditState(string File) : State(){
	file.open(File);
	if (!file.is_open()){
		SDL_Log("falha ao abrir o arquivo de texto");
	}
	wait.Restart();
	wait.Update(2.0);
}
CreditState::~CreditState(){
	file.close();
}

void CreditState::LoadAssets(){}
void CreditState::Update(float dt){

	InputManager& input = InputManager::GetInstance();
	
	if(input.QuitRequested()){
		quitRequested = true;
	}
	
	if (input.KeyPress(SDLK_SPACE) || input.KeyPress(SDLK_ESCAPE)){
		popRequested = true;
	}

	string linha = " ";
	wait.Update(dt);

	if (wait.Get() >= 2.0){
		if(getline(file,linha)){/*Problema com linhas vazias*/
		wait.Restart();

		GameObject* go = new GameObject();
		
		SDL_Color color = {255,255,255,0};
		Text* inst = new Text(go, FONT, 42, Text::TextStyle::SOLID,linha, color);
		go->AddComponent(inst);

		go->Box.Centralize(512,300);
		go->Box.y = 800;

		ObjectArray.emplace_back(go);
		}
	}
	
	

	for (int i = 0; i < ObjectArray.size(); ++i){
		ObjectArray[i]->Box.y -= 50*dt;
		if (ObjectArray[i]->Box.y < -100){
			ObjectArray[i]->RequestDelete();
		}
	}

	if (ObjectArray.size() == 0){
		popRequested = true;
	}

	UpdateArray(dt);
	SDL_Log("obj: %d", ObjectArray.size());
}
void CreditState::Render(){
	SDL_RenderClear(Game::GetInstance()->GetRenderer());
	RenderArray();
}

void CreditState::Start(){
}
void CreditState::Pause(){}
void CreditState::Resume(){
	Camera::pos.x = 0;
	Camera::pos.y = 0;
}