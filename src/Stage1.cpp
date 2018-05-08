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
	
	Sprite* bg = new Sprite(aux, STAGE1_BACKGROUND);

	aux->AddComponent(bg);

	ObjectArray.emplace_back(aux);

	GameObject* aux3 = new GameObject();

	aux3->Box.x = 600;
	aux3->Box.y = 290;

	TileSet* set = new TileSet(aux3, 64, 64, STAGE1_TILESET);
	
	Platform* plataforma = new Platform(aux3, PLATFORM_TYPE1, set);

	aux3->AddComponent(plataforma);

	ObjectArray.emplace_back(aux3);

	GameObject* aux2 = new GameObject();

	aux2->Box.x = 200;
	aux2->Box.y = 500;
	
	Protagonist* ranger = new Protagonist(aux2);
	aux2->AddComponent(ranger);

	Sprite* idle = new Sprite(aux2, PROTAGONIST_IDLE_ANIMATION, 5, 0.3, 0);
	idle->SetTag("ProtagIdle");
	idle->SetEnabled(true);
	ranger->SetSprite(idle);
	aux2->AddComponent(idle);

	Sprite* run = new Sprite(aux2, PROTAGONIST_RUN_ANIMATION, 6, 0.3, 0);
	run->SetTag("ProtagRun");
	run->SetEnabled(false);
	aux2->AddComponent(run);

	Camera::Follow(aux2);

	ObjectArray.emplace_back(aux2);

	GameObject* aux4 = new GameObject();

	aux4->Box.x = 2000;
	aux4->Box.y = 500;
	
	GroundEnemy* enemy = new GroundEnemy(aux4, STAGE1_GROUND_ENEMY_IDLE_ANIMATION, 5, 0.3);

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
