#include "GroundEnemy.h"

GroundEnemy::GroundEnemy(GameObject* associated, string file, int frameCount, float frameTime) : Component(associated){
	speed.x = 0;
	speed.y = 0;
	hp = 5;
	sprite = new Sprite(associated, file, frameCount, frameTime, 0);
	associated->Box.w = sprite->GetWidth();
	associated->Box.h = sprite->GetHeight();
	associated->AddComponent(sprite);
	flip = false;
}
GroundEnemy::GroundEnemy(GameObject* associated) : Component(associated){
	speed.x = 0;
	speed.y = 0;
	hp = 5;
	flip = false;
	state = EnemyState::SEARCHING;

	Collider* colisor = new Collider(associated);
	associated->AddComponent(colisor);
}
GroundEnemy::~GroundEnemy(){}

void GroundEnemy::SetSprite(Sprite* newSprite){
	if (sprite != nullptr){
		sprite->SetEnabled(false);
	}
	sprite = newSprite;
	associated->Box.w = sprite->GetWidth();
	associated->Box.h = sprite->GetHeight();
	sprite->SetEnabled(true);
	sprite->SetFlip(flip);
}

void GroundEnemy::Update(float dt){

	speed.x = 0;

	if (state == EnemyState::ATTACKING){
		if (sprite->IsAnimationOver()){
			if (sprite->GetTag() != "EnemyJump"){
				SetSprite((Sprite*) associated->GetComponentByTag("EnemyIdle"));	
			}
			state = EnemyState::SEARCHING;
		}
		speed.y += 20*dt;
	}

	if (state == EnemyState::SEARCHING){

		int move = rand()%4;

		InputManager& input = InputManager::GetInstance();

		if(input.IsKeyDown(SDLK_q)){
			move = 4;
		}

		if(move == 0 && jumpCount < 1){
			jumpCount++;
			speed.y = -400*dt;
		}

		if(move == 1){
			speed.x = -400*dt;
			flip = true;
			sprite->SetFlip(flip);
		}
		if(move == 2){
			speed.x = 400*dt;
			flip = false;
			sprite->SetFlip(flip);
		}
		if(move == 3){
			Punch();
		}
	}
	speed.y += 20*dt;

	associated->Box.x += speed.x;
	associated->Box.y += speed.y;

	if ((associated->Box.x) < 0){
		associated->Box.x = 0;
	}
	if ((associated->Box.x+associated->Box.w) > 6000){
		associated->Box.x = 6000 - associated->Box.w;
	}

	if ((associated->Box.y+associated->Box.h) > 600){
		Land();
		associated->Box.y = 600 - associated->Box.h;
	}

	if ((associated->Box.y) < 0){
		speed.y = 0;
		associated->Box.y = 0;
	}
	

	//Camera::pos.x = associated->Box.x+512;
}
void GroundEnemy::Render(){}
bool GroundEnemy::Is(string type){
	return(type == "GroundEnemy");
}
void GroundEnemy::Start(){
	Sprite* idle = new Sprite(associated, STAGE1_GROUND_ENEMY_IDLE_ANIMATION, 5, 0.3, 0);
	idle->SetTag("EnemyIdle");
	idle->SetEnabled(true);
	SetSprite(idle);
	associated->AddComponent(idle);

	Sprite* punch = new Sprite(associated, STAGE1_GROUND_ENEMY_PUNCH_ANIMATION, 4, 0.1, 0);
	punch->SetTag("EnemyPunch");
	punch->SetEnabled(false);
	associated->AddComponent(punch);
}
void GroundEnemy::NotifyCollision(GameObject* other){}

void GroundEnemy::Punch(){
	speed.x = 0;
	state = EnemyState::ATTACKING;
	SetSprite((Sprite*) associated->GetComponentByTag("EnemyPunch"));
	sprite->SetFrame(0);
}
void GroundEnemy::Land(){
	speed.y = 0;
	jumpCount = 0;
}