#include "LoseState.h"

LoseState::LoseState() : State(){

	GameObject* aux = new GameObject();

	Sprite* bg;
	bg = new Sprite(aux, LOSE_BACKGROUND);

	aux->AddComponent(bg);

	ObjectArray.emplace_back(aux);

	GameObject* aux2 = new GameObject();
	aux2->Box.x = 100;
	aux2->Box.y = 30;
	
	SDL_Color color = {0,0,0,0};
	Text* inst = new Text(aux2, FONT, 36, Text::TextStyle::SOLID,"Aperte SPACE para jogar denovo ou ESC para sair", color);

	aux2->AddComponent(inst);

	ObjectArray.emplace_back(aux2);

	popRequested = false;

}
LoseState::~LoseState(){}

void LoseState::LoadAssets(){}
void LoseState::Update(float dt){

	InputManager& input = InputManager::GetInstance();
	
	if(input.QuitRequested() || input.KeyPress(SDLK_ESCAPE))
		quitRequested = true;

	if (input.KeyPress(SDLK_SPACE)){
		popRequested = true;
	}

	UpdateArray(dt);
}
void LoseState::Render(){
	RenderArray();
}

void LoseState::Start(){}
void LoseState::Pause(){}
void LoseState::Resume(){
	Camera::pos.x = 0;
	Camera::pos.y = 0;
}