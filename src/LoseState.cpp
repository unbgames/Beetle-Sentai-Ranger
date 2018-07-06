#include "LoseState.h"

LoseState::LoseState() : State(){

	backgroundMusic.Open(LOSE_MUSIC);
	backgroundMusic.Play(1);

	GameObject* aux = new GameObject();

	Sprite* bg;
	bg = new Sprite(aux, LOSE_BACKGROUND);

	aux->AddComponent(bg);

	ObjectArray.emplace_back(aux);

	GameObject* aux2 = new GameObject();

	SDL_Color color = {255,255,255,0};
	Text* inst = new Text(aux2, FONT, 36, Text::TextStyle::SOLID,"Aperte SPACE ou ESC para voltar ao menu", color);

	aux2->Box.Centralize(512,300);
	aux2->Box.y = 500;

	aux2->AddComponent(inst);

	ObjectArray.emplace_back(aux2);

	popRequested = false;

}
LoseState::~LoseState(){
	//backgroundMusic.Stop();
	ObjectArray.clear();
}

void LoseState::LoadAssets(){}
void LoseState::Update(float dt){

	InputManager& input = InputManager::GetInstance();

	if(input.QuitRequested())
		quitRequested = true;

	if (input.KeyPress(SDLK_SPACE)  || input.KeyPress(SDLK_ESCAPE)){
		Game* game = Game::GetInstance();
		if (backgroundMusic.IsPlaying()){
			backgroundMusic.Stop();
		}
		game->Push(new MainMenu());
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
