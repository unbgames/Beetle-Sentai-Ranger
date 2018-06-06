#include "FlyingEnemy.h"

FlyingEnemy::FlyingEnemy(GameObject* associated, int HP) : Enemy(associated, HP){
	scaleAnimations.x = 1;
	scaleAnimations.y = 1;

	colisor->SetScale(Vec2(0.7*scaleAnimations.x,0.4*scaleAnimations.y));
	colisor->SetOffset(Vec2(10,15));
}
FlyingEnemy::~FlyingEnemy(){}
void FlyingEnemy::Update(float dt){
	speed.x = 0;
	speed.y = 0;

	InputManager& input = InputManager::GetInstance();

	if (state == EnemyState::ATTACKING){}

	if (state == EnemyState::SEARCHING){

		int move = rand()%5;

		if(input.IsKeyDown(SDLK_q)){
			move = 6;
		}

		if(move == 0){
			speed.x = -300*dt;
			flip = false;
			sprite->SetFlip(flip);
			colisor->SetOffset(Vec2(10,15));
		}

		if(move == 1){
			speed.x = 300*dt;
			flip = true;
			sprite->SetFlip(flip);
			colisor->SetOffset(Vec2(-10,15));
		}
		if(move == 2){
			speed.y = -300*dt;
		}
		if(move == 3){
			speed.y = 300*dt;
		}
		if(move == 4){
			Attack();
		}
	}

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
}
void FlyingEnemy::Start(){

	Sprite* idle = new Sprite(associated, STAGE1_FLYING_ENEMY_IDLE_ANIMATION, 6, 0.01, 0);
	idle->SetScaleX(scaleAnimations.x,scaleAnimations.y);
	idle->SetTag("EnemyIdle");
	idle->SetEnabled(true);
	SetSprite(idle);
	associated->AddComponent(idle);

	/*Sprite* punch = new Sprite(associated, STAGE1_FLYING_ENEMY_PUNCH_ANIMATION, 4, 0.1, 0);
	punch->SetTag("EnemyPunch");
	punch->SetEnabled(false);
	associated->AddComponent(punch);*/

}
void FlyingEnemy::NotifyCollision(GameObject* other){}
void FlyingEnemy::Attack(){}
void FlyingEnemy::Land(){}
void FlyingEnemy::Kill(){}