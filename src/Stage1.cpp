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
	
	Sprite* bg = new Sprite(aux, "assets/img/6000x600.png");

	aux->AddComponent(bg);

	ObjectArray.emplace_back(aux);

	GameObject* aux3 = new GameObject();

	aux3->Box.x = 600;
	aux3->Box.y = 290;

	TileSet* set = new TileSet(aux3, 64, 64, "assets/img/tileset.png");
	
	Platform* plataforma = new Platform(aux3, "assets/map/Platform.txt", set);

	aux3->AddComponent(plataforma);

	ObjectArray.emplace_back(aux3);

	GameObject* aux2 = new GameObject();

	aux2->Box.x = 200;
	aux2->Box.y = 500;
	
	Protagonist* ranger = new Protagonist(aux2, "assets/img/Fightpose.png", 5, 0.3);

	aux2->AddComponent(ranger);

	Camera::Follow(aux2);

	ObjectArray.emplace_back(aux2);

	GameObject* aux4 = new GameObject();

	aux4->Box.x = 2000;
	aux4->Box.y = 500;
	
	GroundEnemy* enemy = new GroundEnemy(aux4, "assets/img/Louva-God.png", 5, 0.3);

	aux4->AddComponent(enemy);

	ObjectArray.emplace_back(aux4);

}
void Stage1::Update(float dt){

	InputManager& input = InputManager::GetInstance();
	
	if(input.QuitRequested())
		quitRequested = true;

	if (input.KeyPress(SDLK_ESCAPE))
		popRequested = true;

	Camera::Update(dt);

	UpdateArray(dt);

	//SDL_Log("%d", ObjectArray.size());


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
