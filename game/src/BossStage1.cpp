#include "BossStage1.h"

BossStage1::BossStage1(float x, float y){
	quitRequested = false;
	popRequested = false;

	backgroundIntro.Open(STAGE1_BOSS_BACKGROUNDMUSIC_INTRO);
	backgroundLoop.Open(STAGE1_BOSS_BACKGROUNDMUSIC_LOOP);
	backgroundIntro.Play(1);

	PlayerPos.x = x;
	PlayerPos.y = y;
}
BossStage1::~BossStage1(){
	/*if (!GameData::playerVictory){
		backgroundLoop.Stop(0);
	}*/
	ObjectArray.clear();
}

void BossStage1::LoadAssets(){
	GameObject* aux = new GameObject();

	aux->Box.x = 0;
	aux->Box.y = 0;

	Sprite* bg = new Sprite(aux, STAGE1_BOSS_BACKGROUND);

	aux->AddComponent(bg);

	ObjectArray.emplace_back(aux);

	limit = Rect(0, 0, bg->GetWidth(), bg->GetHeight());

	GameObject* aux2 = new GameObject();

	aux2->Box.x = PlayerPos.x;
	aux2->Box.y = PlayerPos.y;

	Protagonist* ranger = new Protagonist(aux2);
	//aux2->AddComponent(ranger);
	GameData::Player = ranger;

	ObjectArray.emplace_back(aux2);

	GameObject* aux4 = new GameObject();

	aux4->Box.x = 50;
	aux4->Box.y = -2000;

	Frog* enemy = new Frog(aux4, 50);

	ObjectArray.emplace_back(aux4);

	GameObject* aux5 = new GameObject();
	aux5->Box.x = 0;
	aux5->Box.y = 505+64;
	Terreno* terreno = new Terreno(aux5, STAGE1_TILESET, TERRAIN_CHAO);
	aux5->AddComponent(terreno);
	ObjectArray.emplace_back(aux5);
}
void BossStage1::Update(float dt){

	if (!backgroundIntro.IsPlaying()){
		backgroundIntro.Stop(0);
		backgroundLoop.Play(-1);
	}

	InputManager& input = InputManager::GetInstance();

	if(input.QuitRequested()){
		backgroundLoop.Stop(0);
		quitRequested = true;
	}

	if (input.KeyPress(SDLK_ESCAPE)){
		backgroundLoop.Stop(0);
		popRequested = true;
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
		backgroundLoop.Stop(0);
		counter.Update(dt);
		if (counter.Get() >= 1.4){
			Game* game = Game::GetInstance();
			game->Push(new LoseState());
			popRequested = true;
		}
		else
			return;
	}
	//SDL_Log("chegou aqui");
	if (GameData::playerVictory){
		backgroundLoop.Stop(0);
		counter.Update(dt);
		if (counter.Get() >= 8.0){
			Game* game = Game::GetInstance();
			game->Push(new CreditState(CREDIT_TEXT));
			popRequested = true;
		}
		else
			return;
	}

	//SDL_Log("%d", ObjectArray.size());
}
void BossStage1::Render(){
	RenderArray();
}

void BossStage1::Start(){
	Camera::Unfollow();
	Camera::pos.x = 0;
	Camera::pos.y = 0;
	LoadAssets();
	StartArray();
}
void BossStage1::Pause(){}
void BossStage1::Resume(){}
