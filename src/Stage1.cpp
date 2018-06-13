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
	*
	*/
	
	GameObject* aux4 = new GameObject();
	aux4->Box.x = 400;
	aux4->Box.y = 505;
	TileSet* setColumn = new TileSet(aux4, 32, 32, STAGE1_TILESET);
	Column* coluna = new Column(aux4, COLUMN_TYPE1, setColumn);
	aux4->AddComponent(coluna);
	ObjectArray.emplace_back(aux4);

	GameObject* aux6 = new GameObject();
	aux6->Box.x = 650;
	aux6->Box.y = 505-96;
	setColumn = new TileSet(aux6, 32, 32, STAGE1_TILESET);
	coluna = new Column(aux6, COLUMN_TYPE1, setColumn);
	aux6->AddComponent(coluna);
	ObjectArray.emplace_back(aux6);

	GameObject* aux5 = new GameObject();
	aux5->Box.x = 650;
	aux5->Box.y = 505;
	TileSet* setColumn2 = new TileSet(aux5, 32, 32, STAGE1_TILESET);
	coluna = new Column(aux5, COLUMN_TYPE2, setColumn2);
	aux5->AddComponent(coluna);
	ObjectArray.emplace_back(aux5);

	//SpawnEnemy(1000, 500);

	GameObject* aux7 = new GameObject();
	aux7->Box.x = 1200;
	aux7->Box.y = 450;
	TileSet* set = new TileSet(aux7, 32, 32, STAGE1_TILESET);
	Platform* plataforma = new Platform(aux7, PLATFORM_TYPE1, set);
	aux7->AddComponent(plataforma);
	ObjectArray.emplace_back(aux7);

	GameObject* aux9 = new GameObject();
	aux9->Box.x = 1400;
	aux9->Box.y = 505-96;
	setColumn = new TileSet(aux9, 32, 32, STAGE1_TILESET);
	coluna = new Column(aux9, COLUMN_TYPE1, setColumn);
	aux9->AddComponent(coluna);
	ObjectArray.emplace_back(aux9);

	GameObject* aux8 = new GameObject();
	aux8->Box.x = 1400;
	aux8->Box.y = 505;
	setColumn2 = new TileSet(aux8, 32, 32, STAGE1_TILESET);
	coluna = new Column(aux8, COLUMN_TYPE2, setColumn2);
	aux8->AddComponent(coluna);
	ObjectArray.emplace_back(aux8);

	GameObject* aux10 = new GameObject();
	aux10->Box.x = 1600;
	aux10->Box.y = 450;
	set = new TileSet(aux10, 32, 32, STAGE1_TILESET);
	plataforma = new Platform(aux10, PLATFORM_TYPE1, set);
	aux10->AddComponent(plataforma);
	ObjectArray.emplace_back(aux10);

	GameObject* aux11 = new GameObject();
	aux11->Box.x = 1800;
	aux11->Box.y = 350;
	set = new TileSet(aux11, 32, 32, STAGE1_TILESET);
	plataforma = new Platform(aux11, PLATFORM_TYPE1, set);
	aux11->AddComponent(plataforma);
	ObjectArray.emplace_back(aux11);

	GameObject* aux12 = new GameObject();
	aux12->Box.x = 2000;
	aux12->Box.y = 350;
	set = new TileSet(aux12, 32, 32, STAGE1_TILESET);
	plataforma = new Platform(aux12, PLATFORM_TYPE1, set);
	aux12->AddComponent(plataforma);
	ObjectArray.emplace_back(aux12);

	GameObject* aux13 = new GameObject();
	aux13->Box.x = 2200;
	aux13->Box.y = 350;
	set = new TileSet(aux13, 32, 32, STAGE1_TILESET);
	plataforma = new Platform(aux13, PLATFORM_TYPE1, set);
	aux13->AddComponent(plataforma);
	ObjectArray.emplace_back(aux13);

	//SpawnEnemy(2100, 500);

	GameObject* aux14 = new GameObject();
	aux14->Box.x = 2400;
	aux14->Box.y = 505-96-96;
	setColumn = new TileSet(aux14, 32, 32, STAGE1_TILESET);
	Terrain* terrain = new Terrain(aux14, COLUMN_TYPE1, setColumn);
	aux14->AddComponent(terrain);
	ObjectArray.emplace_back(aux14);

	GameObject* aux15 = new GameObject();
	aux15->Box.x = 2400;
	aux15->Box.y = 505-96;
	setColumn = new TileSet(aux15, 32, 32, STAGE1_TILESET);
	terrain = new Terrain(aux15, COLUMN_TYPE2, setColumn);
	aux15->AddComponent(terrain);
	ObjectArray.emplace_back(aux15);

	GameObject* aux16 = new GameObject();
	aux16->Box.x = 2400;
	aux16->Box.y = 505;
	setColumn = new TileSet(aux16, 32, 32, STAGE1_TILESET);
	terrain = new Terrain(aux16, COLUMN_TYPE2, setColumn);
	aux16->AddComponent(terrain);
	ObjectArray.emplace_back(aux16);

	//SpawnEnemy(2700, 300);

	GameObject* aux17 = new GameObject();
	aux17->Box.x = 2880;
	aux17->Box.y = 505-96;
	setColumn = new TileSet(aux17, 32, 32, STAGE1_TILESET);
	terrain = new Terrain(aux17, COLUMN_TYPE1, setColumn);
	aux17->AddComponent(terrain);
	ObjectArray.emplace_back(aux17);

	GameObject* aux18 = new GameObject();
	aux18->Box.x = 2880;
	aux18->Box.y = 505;
	setColumn = new TileSet(aux18, 32, 32, STAGE1_TILESET);
	terrain = new Terrain(aux18, COLUMN_TYPE2, setColumn);
	aux18->AddComponent(terrain);
	ObjectArray.emplace_back(aux18);

	//SpawnEnemy(3000, 400);
	//SpawnEnemy(3200, 400);

	GameObject* aux19 = new GameObject();
	aux19->Box.x = 3360;
	aux19->Box.y = 505;
	setColumn = new TileSet(aux19, 32, 32, STAGE1_TILESET);
	terrain = new Terrain(aux19, COLUMN_TYPE1, setColumn);
	aux19->AddComponent(terrain);
	ObjectArray.emplace_back(aux19);

	//SpawnEnemy(3500, 400);
	//SpawnEnemy(3700, 400);

	SpawnFlyingEnemy(3800, 50);

	GameObject* aux20 = new GameObject();
	aux20->Box.x = 4000;
	aux20->Box.y = 450;
	set = new TileSet(aux20, 32, 32, STAGE1_TILESET);
	plataforma = new Platform(aux20, PLATFORM_TYPE1, set);
	aux20->AddComponent(plataforma);
	ObjectArray.emplace_back(aux20);

	GameObject* aux21 = new GameObject();
	aux21->Box.x = 4200;
	aux21->Box.y = 350;
	set = new TileSet(aux21, 32, 32, STAGE1_TILESET);
	plataforma = new Platform(aux21, PLATFORM_TYPE1, set);
	aux21->AddComponent(plataforma);
	ObjectArray.emplace_back(aux21);

	GameObject* aux22 = new GameObject();
	aux22->Box.x = 4400;
	aux22->Box.y = 450;
	set = new TileSet(aux22, 32, 32, STAGE1_TILESET);
	plataforma = new Platform(aux22, PLATFORM_TYPE1, set);
	aux22->AddComponent(plataforma);
	ObjectArray.emplace_back(aux22);

	SpawnFlyingEnemy(4600, 50);

	GameObject* aux23 = new GameObject();
	aux23->Box.x = 4600;
	aux23->Box.y = 450;
	set = new TileSet(aux23, 32, 32, STAGE1_TILESET);
	plataforma = new Platform(aux23, PLATFORM_TYPE1, set);
	aux23->AddComponent(plataforma);
	ObjectArray.emplace_back(aux23);

	GameObject* aux24 = new GameObject();
	aux24->Box.x = 4700;
	aux24->Box.y = 350;
	set = new TileSet(aux24, 32, 32, STAGE1_TILESET);
	plataforma = new Platform(aux24, PLATFORM_TYPE1, set);
	aux24->AddComponent(plataforma);
	ObjectArray.emplace_back(aux24);

	GameObject* aux25 = new GameObject();
	aux25->Box.x = 5000;
	aux25->Box.y = 505-96-96;
	setColumn = new TileSet(aux25, 32, 32, STAGE1_TILESET);
	terrain = new Terrain(aux25, COLUMN_TYPE1, setColumn);
	aux25->AddComponent(terrain);
	ObjectArray.emplace_back(aux25);

	GameObject* aux26 = new GameObject();
	aux26->Box.x = 5000;
	aux26->Box.y = 505-96;
	setColumn = new TileSet(aux26, 32, 32, STAGE1_TILESET);
	terrain = new Terrain(aux26, COLUMN_TYPE2, setColumn);
	aux26->AddComponent(terrain);
	ObjectArray.emplace_back(aux26);

	GameObject* aux27 = new GameObject();
	aux27->Box.x = 5000;
	aux27->Box.y = 505;
	setColumn = new TileSet(aux27, 32, 32, STAGE1_TILESET);
	terrain = new Terrain(aux27, COLUMN_TYPE2, setColumn);
	aux27->AddComponent(terrain);
	ObjectArray.emplace_back(aux27);

	GameObject* aux28 = new GameObject();
	aux28->Box.x = 5480;
	aux28->Box.y = 505-96;
	setColumn = new TileSet(aux28, 32, 32, STAGE1_TILESET);
	terrain = new Terrain(aux28, COLUMN_TYPE1, setColumn);
	aux28->AddComponent(terrain);
	ObjectArray.emplace_back(aux28);

	GameObject* aux29 = new GameObject();
	aux29->Box.x = 5480;
	aux29->Box.y = 505;
	setColumn = new TileSet(aux29, 32, 32, STAGE1_TILESET);
	terrain = new Terrain(aux29, COLUMN_TYPE2, setColumn);
	aux29->AddComponent(terrain);
	ObjectArray.emplace_back(aux29);

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
		popRequested = true;
		backgroundLoop.Stop();
	}

	if (input.KeyPress(SDLK_p)){
		Game* game = Game::GetInstance();
		backgroundLoop.Stop();
		game->Push(new BossStage1(GameData::Player->GetAssociated()->Box.x - Camera::pos.x,GameData::Player->GetAssociated()->Box.y  - Camera::pos.y));
		popRequested = true;
	}

	/*if (GameData::Player == nullptr){
		SDL_Log("game over");
		popRequested = true;
	}*/

	if (GameData::Player != nullptr && GameData::Player->GetAssociated()->Box.x >= 6600){
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


	//SDL_Log("obj: %d", ObjectArray.size());
	//SDL_Log("enemy: %d", GroundEnemy::nEnemy);
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

	int offset = 600 + rand()%1500;

	obj->Box.x = GameData::Player->GetAssociated()->Box.x+offset;
	obj->Box.y = 500;

	if (obj->Box.x >= limit.x+limit.w-1024){
		obj->Box.x = GameData::Player->GetAssociated()->Box.x-offset;
	}

	GroundEnemy* enemy = new GroundEnemy(obj, 5);

	obj->AddComponent(enemy);

	AddObject(obj);

	GroundEnemy::nEnemy++;
}

void Stage1::SpawnEnemy(int positionX, int positionY)
{
	GameObject* obj = new GameObject();

	obj->Box.x = positionX;
	obj->Box.y = positionY;

	GroundEnemy* enemy = new GroundEnemy(obj, 5);

	obj->AddComponent(enemy);

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

	obj->AddComponent(enemy);

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

	obj->AddComponent(enemy);

	AddObject(obj);
}
