#include "Stage1.h"

Stage1::Stage1(){
	quitRequested = false;
	popRequested = false;
}
Stage1::~Stage1(){
	backgroundMusic.Stop();
	ObjectArray.clear();
}

void Stage1::LoadAssets(){

	GameObject* aux = new GameObject();

	aux->Box.x = 0;
	aux->Box.y = 0;
	
	Sprite* bg = new Sprite(aux, "assets/img/Front.png");

	aux->AddComponent(bg);

	ObjectArray.emplace_back(aux);

	GameObject* aux2 = new GameObject();

	aux2->Box.x = 200;
	aux2->Box.y = 500;
	
	Protagonist* ranger = new Protagonist(aux2, "assets/img/Fight Pose.png", 4, 0.3);

	aux2->AddComponent(ranger);

	Camera::Follow(aux2);

	ObjectArray.emplace_back(aux2);

}
void Stage1::Update(float dt){

	InputManager& input = InputManager::GetInstance();
	
	if(input.QuitRequested())
		quitRequested = true;

	if (input.KeyPress(SDLK_ESCAPE))
		popRequested = true;

	Camera::Update(dt);

	UpdateArray(dt);

	SDL_Log("%d", ObjectArray.size());


}
void Stage1::Render(){
	RenderArray();
}

void Stage1::Start(){
	LoadAssets();
	StartArray();
}
void Stage1::Pause(){}
void Stage1::Resume(){}
