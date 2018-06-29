#include "FlyingEnemy.h"

FlyingEnemy::FlyingEnemy(GameObject* associated, int HP) : Enemy(associated, HP){
	scaleAnimations.x = 1;
	scaleAnimations.y = 1;

	ShootTimer.Restart();

	colisor->SetScale(Vec2(0.4*scaleAnimations.x,0.6*scaleAnimations.y));
	colisor->SetOffset(Vec2(0,10));

	state = EnemyState::SEARCHING;
}
FlyingEnemy::~FlyingEnemy(){}
void FlyingEnemy::Update(float dt){
	ShootTimer.Update(dt);
	speed.x = 0;
	speed.y = 0;

	InputManager& input = InputManager::GetInstance();

	if (state == EnemyState::ATTACKING){
		if (sprite->IsAnimationOver()){
			SetSprite((Sprite*) associated->GetComponentByTag("EnemyIdle"));
			state = EnemyState::SEARCHING;
		}
	}

	if (state == EnemyState::SEARCHING){

		int move = 0;

		InputManager& input = InputManager::GetInstance();

		Vec2 centro = associated->Box.GetCenter();

		if(GameData::Player == nullptr)
			return;

		Vec2 centroPlayer = GameData::Player->GetAssociated()->Box.GetCenter();

		if (centroPlayer.x > centro.x && abs(centroPlayer.x - centro.x) > 55){
			//andar para a direita
			move = 2;
		}
		else if(abs(centroPlayer.x - centro.x) > 55){
			//andar para a esquerda
			move = 1;
		}

		if (abs(centroPlayer.x - associated->Box.x) < 600 && ShootTimer.Get() > 4.5){
			//atacar
			ShootTimer.Restart();
			move = 3;

		}

		if (PathBlocked){
			//pular
			move = 0;
		}

		if(input.IsKeyDown(SDLK_q)){
			move = 4;
		}

		if(move == 0 && jumpCount < 1){
			speed.y = -450*dt;
			PathBlocked = false;
		}

		if(move == 1){
			speed.x = -300*dt;
			flip = true;
			sprite->SetFlip(flip);
		}
		if(move == 2){
			speed.x = 300*dt;
			flip = false;
			sprite->SetFlip(flip);
		}
		if(move == 3){
			Attack(centroPlayer);
			state = EnemyState::ATTACKING;
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

	Sprite* idle = new Sprite(associated, STAGE1_FLYING_ENEMY_IDLE_ANIMATION, 8, 0.01, 0);
	idle->SetScaleX(scaleAnimations.x,scaleAnimations.y);
	idle->SetTag("EnemyIdle");
	idle->SetEnabled(true);
	SetSprite(idle);
	associated->AddComponent(idle);

	Sprite* punch = new Sprite(associated, STAGE1_FLYING_ENEMY_ATTACK_ANIMATION, 8, 0.01, 0);
	punch->SetTag("EnemyPunch");
	punch->SetEnabled(false);
	associated->AddComponent(punch);

}
void FlyingEnemy::NotifyCollision(GameObject* other){}
void FlyingEnemy::Attack(Vec2 target){

	SetSprite((Sprite*) associated->GetComponentByTag("EnemyPunch"));
	sprite->SetFrame(0);

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	go->Box.Centralize(associated->Box.GetCenter().x , associated->Box.GetCenter().y);
	double angle = associated->Box.GetCenter().GetAngle(target);
	go->tag = "bullet";

	ShitBall* bullet = new ShitBall(go, angle, 700, 1, true, STAGE1_FLYING_ENEMY_BULLET_ANIMATION,STAGE1_FLYING_ENEMY_BULLET_SOUND, 4);
	go->AddComponent(bullet);
	state->AddObject(go);
}
void FlyingEnemy::Land(){}

void FlyingEnemy::Kill(){
	associated->RequestDelete();

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	go->Box.x = associated->Box.x;
	go->Box.y = associated->Box.y;
	state->AddObject(go);

	Sprite* sprite = new Sprite(go, STAGE1_FLYING_ENEMY_DEATH_ANIMATION,5,0.2,1.0);
	go->AddComponent(sprite);

}