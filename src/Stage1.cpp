#include "Stage1.h"

Stage1::Stage1(int nEnemy) : State(){
	quitRequested = false;
	popRequested = false;
	backgroundMusic.Open(STAGE1_BACKGROUNDMUSIC);
	backgroundMusic.Play(-1);

	TotalEnemy = nEnemy;
}
Stage1::~Stage1(){
	backgroundMusic.Stop();
	ObjectArray.clear();
}

void Stage1::LoadAssets(){

	GameObject* backobj = new GameObject();

	backobj->Box.x = 0;
	backobj->Box.y = 0;

	Sprite* bg = new Sprite(backobj, STAGE1_BACKGROUND);

	backobj->AddComponent(bg);

	ObjectArray.emplace_back(backobj);

	GameObject* backobj2 = new GameObject();

	backobj2->Box.x = bg->GetWidth();
	backobj2->Box.y = 0;

	Sprite* bg2 = new Sprite(backobj2, STAGE1_BOSS_BACKGROUND);

	backobj2->AddComponent(bg2);

	ObjectArray.emplace_back(backobj2);

	limit = Rect(0, 0, bg->GetWidth() + bg2->GetWidth(), bg->GetHeight());

	/*
	*
	*/

	GameObject* aux3 = new GameObject();

	aux3->Box.x = 600;
	aux3->Box.y = 450;

	TileSet* set = new TileSet(aux3, 32, 32, STAGE1_TILESET);

	Platform* plataforma = new Platform(aux3, PLATFORM_TYPE1, set);

	aux3->AddComponent(plataforma);

	ObjectArray.emplace_back(aux3);

	GameObject* aux4 = new GameObject();

	aux4->Box.x = 400;
	aux4->Box.y = 500;

	TileSet* setColumn = new TileSet(aux4, 32, 32, STAGE1_TILESET);

	Column* coluna = new Column(aux4, COLUMN_TYPE1, setColumn);

	aux4->AddComponent(coluna);

	ObjectArray.emplace_back(aux4);

	GameObject* aux2 = new GameObject();

	aux2->Box.x = 200;
	aux2->Box.y = 500;

	Protagonist* ranger = new Protagonist(aux2);
	aux2->AddComponent(ranger);
	GameData::Player = ranger;

	Camera::Follow(aux2);

	ObjectArray.emplace_back(aux2);

}
void Stage1::Update(float dt){

	InputManager& input = InputManager::GetInstance();

	if(input.QuitRequested())
		quitRequested = true;

	if (input.KeyPress(SDLK_ESCAPE))
		popRequested = true;

	if (input.KeyPress(SDLK_p)){
		Game* game = Game::GetInstance();
		game->Push(new BossStage1(GameData::Player->GetAssociated()->Box.x - Camera::pos.x,GameData::Player->GetAssociated()->Box.y  - Camera::pos.y));
		popRequested = true;
	}

	/*if (GameData::Player == nullptr){
		SDL_Log("game over");
		popRequested = true;
	}*/

	if (GameData::Player != nullptr && GameData::Player->GetAssociated()->Box.x >= 6600){
		Game* game = Game::GetInstance();
		game->Push(new BossStage1(GameData::Player->GetAssociated()->Box.x - Camera::pos.x,GameData::Player->GetAssociated()->Box.y  - Camera::pos.y));
		popRequested = true;
	}

	if (GroundEnemy::nEnemy < TotalEnemy){
		SpawnEnemy();
	}

	Camera::Update(dt);

	UpdateArray(dt);

	for(int i = 0; i < ObjectArray.size(); i++){
		Collider* colisorI = (Collider*) ObjectArray[i]->GetComponent("Collider");

		for (int j=i+1; j < ObjectArray.size(); j++){
			Collider* colisorJ = (Collider*) ObjectArray[j]->GetComponent("Collider");

			if ((i != j) && (colisorI != nullptr) && (colisorJ != nullptr)){
				if(Collision::IsColliding(colisorI->box, colisorJ->box , ObjectArray[i]->angleDeg*(PI/180.0), ObjectArray[j]->angleDeg*(PI/180.0))){


					ObjectArray[i]->NotifyCollision(ObjectArray[j].get());
					ObjectArray[j]->NotifyCollision(ObjectArray[i].get());
				}
			}
		}
	}


	SDL_Log("obj: %d", ObjectArray.size());
	SDL_Log("enemy: %d", GroundEnemy::nEnemy);
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

void Stage1::SpawnEnemy(){
	GameObject* obj = new GameObject();

	obj->Box.x = GameData::Player->GetAssociated()->Box.x+600;
	obj->Box.y = 500;

	if (obj->Box.x >= limit.x+limit.w-1024){
		obj->Box.x = GameData::Player->GetAssociated()->Box.x-600;
	}

	GroundEnemy* enemy = new GroundEnemy(obj, 5);

	obj->AddComponent(enemy);

	AddObject(obj);

	GroundEnemy::nEnemy++;
}
