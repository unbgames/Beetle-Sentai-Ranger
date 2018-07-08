#include "Stage1.h"

Stage1::Stage1(int nEnemy) : State(){
	quitRequested = false;
	popRequested = false;

	backgroundIntro.Open(STAGE1_BACKGROUNDMUSIC_INTRO);
	backgroundLoop.Open(STAGE1_BACKGROUNDMUSIC_LOOP);
	backgroundIntro.Play(1);

	TotalEnemy = nEnemy;
}
Stage1::~Stage1(){
	//if (backgroundLoop.IsOpen())
		//backgroundLoop.Stop();
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
	* LEVEL DESIGN (PLATAFORMAS E COLUNAS)
	*/

	/*
	GameObject* aux3 = new GameObject();
	aux3->Box.x = 100;
	aux3->Box.y = 450;
	TileSet* set = new TileSet(aux3, 32, 32, STAGE1_TILESET);
	Platform* plataforma = new Platform(aux3, PLATFORM_TYPE1, set);
	aux3->AddComponent(plataforma);
	ObjectArray.emplace_back(aux3);
	*/

	GameObject* aux2 = new GameObject();
	aux2->Box.x = 200;
	aux2->Box.y = 500;
	Protagonist* ranger = new Protagonist(aux2);
	//aux2->AddComponent(ranger);
	GameData::Player = ranger;
	Camera::Follow(aux2);
	ObjectArray.emplace_back(aux2);

	/*
	GameObject* auxTest = new GameObject();
	auxTest->Box.x = 200;
	auxTest->Box.y = 50;
	Terreno* terreno = new Terreno(auxTest, STAGE1_TILESET, COLUMN_TYPE1);
	auxTest->AddComponent(terreno);
	ObjectArray.emplace_back(auxTest);
	*/

	GameObject* aux3 = new GameObject();
	aux3->Box.x = 0;
	aux3->Box.y = 505+64;
	Terreno* terreno = new Terreno(aux3, STAGE1_TILESET, TERRAIN_CHAO);
	aux3->AddComponent(terreno);
	ObjectArray.emplace_back(aux3);

	GameObject* aux4 = new GameObject();
	aux4->Box.x = 400;
	aux4->Box.y = 505;
	terreno = new Terreno(aux4, STAGE1_TILESET, COLUMN_TYPE1);
	aux4->AddComponent(terreno);
	ObjectArray.emplace_back(aux4);

	GameObject* aux6 = new GameObject();
	aux6->Box.x = 650;
	aux6->Box.y = 505-96;
	terreno = new Terreno(aux6, STAGE1_TILESET, COLUMN_TYPE2);
	aux6->AddComponent(terreno);
	ObjectArray.emplace_back(aux6);

	//SpawnEnemy(1000, 500);

	GameObject* aux7 = new GameObject();
	aux7->Box.x = 1200;
	aux7->Box.y = 450;
	terreno = new Terreno(aux7, STAGE1_TILESET, PLATFORM_TYPE1);
	aux7->AddComponent(terreno);
	ObjectArray.emplace_back(aux7);

	GameObject* aux9 = new GameObject();
	aux9->Box.x = 1400;
	aux9->Box.y = 505-96;
	terreno = new Terreno(aux9, STAGE1_TILESET, COLUMN_TYPE2);
	aux9->AddComponent(terreno);
	ObjectArray.emplace_back(aux9);

	GameObject* aux10 = new GameObject();
	aux10->Box.x = 1600;
	aux10->Box.y = 450;
	terreno = new Terreno(aux10, STAGE1_TILESET, PLATFORM_TYPE1);
	aux10->AddComponent(terreno);
	ObjectArray.emplace_back(aux10);

	GameObject* aux11 = new GameObject();
	aux11->Box.x = 1800;
	aux11->Box.y = 350;
	terreno = new Terreno(aux11, STAGE1_TILESET, PLATFORM_TYPE1);
	aux11->AddComponent(terreno);
	ObjectArray.emplace_back(aux11);

	GameObject* aux12 = new GameObject();
	aux12->Box.x = 2000;
	aux12->Box.y = 350;
	terreno = new Terreno(aux12, STAGE1_TILESET, PLATFORM_TYPE1);
	aux12->AddComponent(terreno);
	ObjectArray.emplace_back(aux12);

	GameObject* aux13 = new GameObject();
	aux13->Box.x = 2200;
	aux13->Box.y = 350;
	terreno = new Terreno(aux13, STAGE1_TILESET, PLATFORM_TYPE1);
	aux13->AddComponent(terreno);
	ObjectArray.emplace_back(aux13);

	//SpawnEnemy(2100, 500);

	GameObject* aux14 = new GameObject();
	aux14->Box.x = 2400;
	aux14->Box.y = 505-96-96;
	terreno = new Terreno(aux14, STAGE1_TILESET, TERRAIN_TYPE3);
	aux14->AddComponent(terreno);
	ObjectArray.emplace_back(aux14);

	//SpawnEnemy(2700, 300);

	GameObject* aux17 = new GameObject();
	aux17->Box.x = 2880;
	aux17->Box.y = 505-96;
	terreno = new Terreno(aux17, STAGE1_TILESET, TERRAIN_TYPE2);
	aux17->AddComponent(terreno);
	ObjectArray.emplace_back(aux17);

	//SpawnEnemy(3000, 400);
	//SpawnEnemy(3200, 400);

	GameObject* aux19 = new GameObject();
	aux19->Box.x = 3360;
	aux19->Box.y = 505;
	terreno = new Terreno(aux19, STAGE1_TILESET, TERRAIN_TYPE1);
	aux19->AddComponent(terreno);
	ObjectArray.emplace_back(aux19);

	//SpawnEnemy(3500, 400);
	//SpawnEnemy(3700, 400);

	SpawnFlyingEnemy(3800, 50);

	GameObject* aux20 = new GameObject();
	aux20->Box.x = 4000;
	aux20->Box.y = 450;
	terreno = new Terreno(aux20, STAGE1_TILESET, PLATFORM_TYPE1);
	aux20->AddComponent(terreno);
	ObjectArray.emplace_back(aux20);

	GameObject* aux21 = new GameObject();
	aux21->Box.x = 4200;
	aux21->Box.y = 350;
	terreno = new Terreno(aux21, STAGE1_TILESET, PLATFORM_TYPE1);
	aux21->AddComponent(terreno);
	ObjectArray.emplace_back(aux21);

	GameObject* aux22 = new GameObject();
	aux22->Box.x = 4400;
	aux22->Box.y = 450;
	terreno = new Terreno(aux22, STAGE1_TILESET, PLATFORM_TYPE1);
	aux22->AddComponent(terreno);
	ObjectArray.emplace_back(aux22);

	SpawnFlyingEnemy(4600, 50);

	GameObject* aux23 = new GameObject();
	aux23->Box.x = 4600;
	aux23->Box.y = 450;
	terreno = new Terreno(aux23, STAGE1_TILESET, PLATFORM_TYPE1);
	aux23->AddComponent(terreno);
	ObjectArray.emplace_back(aux23);

	GameObject* aux24 = new GameObject();
	aux24->Box.x = 4700;
	aux24->Box.y = 350;
	terreno = new Terreno(aux24, STAGE1_TILESET, PLATFORM_TYPE1);
	aux24->AddComponent(terreno);
	ObjectArray.emplace_back(aux24);

	GameObject* aux25 = new GameObject();
	aux25->Box.x = 5000;
	aux25->Box.y = 505-96-96;
	terreno = new Terreno(aux25, STAGE1_TILESET, TERRAIN_TYPE3);
	aux25->AddComponent(terreno);
	ObjectArray.emplace_back(aux25);

	GameObject* aux28 = new GameObject();
	aux28->Box.x = 5480;
	aux28->Box.y = 505-96;
	terreno = new Terreno(aux28, STAGE1_TILESET, TERRAIN_TYPE2);
	aux28->AddComponent(terreno);
	ObjectArray.emplace_back(aux28);

	//SpawnEnemy(5600, 400);
	//SpawnEnemy(5800, 400);
}

void Stage1::Update(float dt){

	if (!backgroundIntro.IsPlaying()){
		backgroundIntro.Stop(0);
		backgroundLoop.Play(-1);
	}

	InputManager& input = InputManager::GetInstance();

	if(input.QuitRequested())
		quitRequested = true;

	if (input.KeyPress(SDLK_ESCAPE)){
		Game* game = Game::GetInstance();
		backgroundLoop.Stop();
		game->Push(new MainMenu());
		popRequested = true;
	}

	if (input.KeyPress(SDLK_p)){
		Game* game = Game::GetInstance();
		backgroundLoop.Stop();
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
				if(Collision::IsColliding(colisorI->Box, colisorJ->Box , ObjectArray[i]->angleDeg*(PI/180.0), ObjectArray[j]->angleDeg*(PI/180.0))){


					ObjectArray[i]->NotifyCollision(ObjectArray[j].get());
					ObjectArray[j]->NotifyCollision(ObjectArray[i].get());
				}
			}
		}
	}

	if (GameData::Player == nullptr){
		counter.Update(dt);
		if (counter.Get() >= 1.4){
			Game* game = Game::GetInstance();
			game->Push(new LoseState());
			popRequested = true;
		}
		else
			return;
	}

	if (GameData::Player != nullptr && GameData::Player->GetAssociated()->Box.x >= 6600){
		Game* game = Game::GetInstance();
		backgroundLoop.Stop();
		game->Push(new BossStage1(GameData::Player->GetAssociated()->Box.x - Camera::pos.x,GameData::Player->GetAssociated()->Box.y  - Camera::pos.y));
		popRequested = true;


	}

	//SDL_Log("obj: %d", ObjectArray.size());
	//SDL_Log("enemy: %d", GroundEnemy::nEnemy);
}
void Stage1::Render(){
	RenderArray();
}

void Stage1::Start(){
	LoadAssets();
	StartArray();
	GroundEnemy::nEnemy = 0;
	GameData::playerVictory = false;
}
void Stage1::Pause(){}
void Stage1::Resume(){}

void Stage1::SpawnEnemy(){
	GameObject* obj = new GameObject();

	int offset = 600 + rand()%1500;

	obj->Box.x = GameData::Player->GetAssociated()->Box.x+offset;
	obj->Box.y = 500;

	if (obj->Box.x >= limit.x+limit.w-1024){
		obj->Box.x = GameData::Player->GetAssociated()->Box.x-offset;
	}

	GroundEnemy* enemy = new GroundEnemy(obj, 5);

	AddObject(obj);

	GroundEnemy::nEnemy++;
}

void Stage1::SpawnEnemy(int positionX, int positionY)
{
	GameObject* obj = new GameObject();

	obj->Box.x = positionX;
	obj->Box.y = positionY;

	GroundEnemy* enemy = new GroundEnemy(obj, 5);

	AddObject(obj);

	GroundEnemy::nEnemy++;
}

void Stage1::SpawnFlyingEnemy(){
	GameObject* obj = new GameObject();

	int offsetX = 600 + rand()%1500;
	int offsetY = 100 + rand()%300;

	obj->Box.x = GameData::Player->GetAssociated()->Box.x+offsetX;
	obj->Box.y = offsetY;

	if (obj->Box.x >= limit.x+limit.w-1024){
		obj->Box.x = GameData::Player->GetAssociated()->Box.x-offsetX;
	}

	FlyingEnemy* enemy = new FlyingEnemy(obj, 5);

	AddObject(obj);
}

void Stage1::SpawnFlyingEnemy(int positionX, int positionY)
{
	GameObject* obj = new GameObject();

	int offsetX = positionX;
	int offsetY = positionY;

	obj->Box.x = offsetX;
	obj->Box.y = offsetY;

	FlyingEnemy* enemy = new FlyingEnemy(obj, 5);

	AddObject(obj);
}
