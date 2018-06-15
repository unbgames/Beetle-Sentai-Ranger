#include "Frog.h"

Frog::Frog(GameObject* associated, int HP) : Enemy(associated, HP){
	SearchTimer.Restart();

	colisor->SetScale(Vec2(0.4,0.71));
	colisor->SetOffset(Vec2(320,80));
}
Frog::~Frog(){}

void Frog::SetSprite(Sprite* newSprite){
	if (sprite != nullptr){
		sprite->SetEnabled(false);
	}
	sprite = newSprite;
	associated->Box.w = sprite->GetWidth();
	associated->Box.h = sprite->GetHeight();

	associated->Box.w *= 0.5;

	sprite->SetEnabled(true);
	sprite->SetFlip(flip);
}

void Frog::Update(float dt){
	
	float hipo = dt*700;
	Rect limit = Game::GetInstance()->GetCurrentState()->GetLimit();

	speed.y += 20*dt;

	associated->Box.x += speed.x;
	associated->Box.y += speed.y;

	if (hp <= 0){
		Kill();
	}


	if ((colisor->Box.x) < limit.x){
		state = EnemyState::SEARCHING;
		associated->Box.x = limit.x - abs(colisor->Box.x - associated->Box.x);
	}

	if ((colisor->Box.x + colisor->Box.w) > limit.x + limit.w){
		state = EnemyState::SEARCHING;
		associated->Box.x = limit.x+limit.w - colisor->Box.w  - abs(colisor->Box.x - associated->Box.x);
	}

	if ((associated->Box.y + associated->Box.h) > limit.y+limit.h){
		Land();
		associated->Box.y = limit.y+limit.h - associated->Box.h;
	}

	if(state == EnemyState::SEARCHING){
		SetSprite((Sprite*) associated->GetComponentByTag("EnemyIdle"));
		//SDL_Log("searching");
		SearchTimer.Update(dt);
		if (SearchTimer.Get() < 3){
			return;
		}
		SearchTimer.Restart();
		SetSprite((Sprite*) associated->GetComponentByTag("EnemyRun"));
		
		if (GameData::Player == nullptr){
			return;
		}
		destination = GameData::Player->GetAssociated()->Box.GetCenter();
		
		Vec2 centro = colisor->Box.GetCenter();
		float angulo = centro.GetAngle(destination);

		speed.y = hipo*sin(angulo);
		speed.x = hipo*cos(angulo);
		
		if(speed.x >= 0){
			flip = true;
			colisor->SetOffset(Vec2(80,80));
		}
		else{
			flip = false;
			colisor->SetOffset(Vec2(310,80));
		}
		
		state = EnemyState::ATTACKING;
	}

	if(state == EnemyState::ATTACKING){
		//SDL_Log("attacking");
		Vec2 centro = colisor->Box.GetCenter();
		
		float dis = centro.Distance(destination);
		SDL_Log("%f", dis);
		if(dis <= hipo){
			associated->Box.Centralize(destination.x, destination.y);
		}
		else{
			//SDL_Log("%f %f", destination.x, destination.y);
			associated->Box.x += speed.x;
			associated->Box.y += speed.y;
			return;
		}

		state = EnemyState::SEARCHING;
	}
}
void Frog::Start(){
	Sprite* idle = new Sprite(associated, STAGE1_BOSS_IDLE_ANIMATION, 8, 0.3, 0);
	idle->SetTag("EnemyIdle");
	idle->SetEnabled(true);
	SetSprite(idle);
	associated->AddComponent(idle);

	Sprite* run = new Sprite(associated, STAGE1_BOSS_RUN_ANIMATION, 8, 0.3, 0);
	run->SetTag("EnemyRun");
	run->SetEnabled(false);
	associated->AddComponent(run);

	/*Sprite* smash = new Sprite(associated, STAGE1_BOSS_ATTACK1_ANIMATION, 16, 0.1, 0);
	smash->SetTag("EnemySmash");
	smash->SetEnabled(false);
	associated->AddComponent(smash);

	/*Sprite* baixo = new Sprite(associated, STAGE1_BOSS_ATTACK2_ANIMATION, 11, 0.1, 0);
	baixo->SetTag("EnemyBaixo");
	baixo->SetEnabled(false);
	associated->AddComponent(baixo);

	/*Sprite* alto = new Sprite(associated, STAGE1_BOSS_ATTACK3_ANIMATION, 11, 0.1, 0);
	alto->SetTag("EnemyAlto");
	alto->SetEnabled(false);
	associated->AddComponent(alto);*/

}
void Frog::NotifyCollision(GameObject* other){
	Protagonist* base = (Protagonist*) other->GetComponent("Protagonist");
	if (base != nullptr && state == EnemyState::ATTACKING){
		base->TakeDamage(1);
		associated->Box.x -= speed.x;
		associated->Box.y -= speed.y;
		speed.x = 0;
		speed.y = 0;
		state = EnemyState::SEARCHING;
	}
}
void Frog::Attack(){}
void Frog::Land(){
	speed.y = 0;
	jumpCount = 0;
}
void Frog::Kill(){
	GameData::playerVictory = true;
	associated->RequestDelete();

	/*Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	go->Box.x = associated->Box.x;
	go->Box.y = associated->Box.y;
	state->AddObject(go);

	Sprite* death = new Sprite(go, STAGE1_BOSS_DEATH_ANIMATION, 12, 0.3, 3.6);
	go->AddComponent(death);*/
}