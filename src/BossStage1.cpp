#include "BossStage1.h"

BossStage1::BossStage1(){
	quitRequested = false;
	popRequested = false;
}
BossStage1::~BossStage1(){
	backgroundMusic.Stop();
	ObjectArray.clear();
}

void BossStage1::LoadAssets(){
	GameObject* aux = new GameObject();

	aux->Box.x = 0;
	aux->Box.y = 0;
	
	Sprite* bg = new Sprite(aux, STAGE1_BOSS_BACKGROUND);

	aux->AddComponent(bg);

	ObjectArray.emplace_back(aux);

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

	ObjectArray.emplace_back(aux2);
}
void BossStage1::Update(float dt){

	InputManager& input = InputManager::GetInstance();
	
	if(input.QuitRequested())
		quitRequested = true;

	if (input.KeyPress(SDLK_ESCAPE))
		popRequested = true;

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