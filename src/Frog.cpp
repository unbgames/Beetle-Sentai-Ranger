#include "Frog.h"

Frog::Frog(GameObject* associated, int HP) : Enemy(associated, HP){
	SearchTimer.Restart();
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

	float hipo = dt*1500;
	Rect limit = Game::GetInstance()->GetCurrentState()->GetLimit();

	speed.y += 20*dt;


	if ((associated->Box.x) < limit.x){
		state = EnemyState::SEARCHING;
		associated->Box.x = limit.x;
	}
	if ((associated->Box.x+associated->Box.w) > limit.x+limit.w){
		state = EnemyState::SEARCHING;
		associated->Box.x = limit.x+limit.w - associated->Box.w;
	}

	if ((associated->Box.y+associated->Box.h) > limit.y+limit.h){
		Land();
		associated->Box.y = limit.y+limit.h - associated->Box.h;
	}

	if (state == EnemyState::SEARCHING){
		SDL_Log("searching");
		SearchTimer.Update(dt);
		if (SearchTimer.Get() < 3){
			return;
		}
		SearchTimer.Restart();
		
		if (GameData::Player == nullptr){
			return;
		}
		destination = GameData::Player->GetAssociated()->Box.GetCenter();
		
		Vec2 centro = associated->Box.GetCenter();
		float angulo = centro.GetAngle(destination);

		speed.y = hipo*sin(angulo);
		speed.x = hipo*cos(angulo);
		
		state = EnemyState::ATTACKING;
	}

	if (state == EnemyState::ATTACKING){
		//SDL_Log("attacking");
		Vec2 centro = associated->Box.GetCenter();
		
		if (centro.Distance(destination) <= hipo){
			associated->Box.Centralize(destination.x, destination.y);
		}
		else{
			SDL_Log("%f %f", destination.x, destination.y);
			associated->Box.x += speed.x;
			associated->Box.y += speed.y;
			return;
		}

		state = EnemyState::SEARCHING;
	}
}
void Frog::Start(){
	Sprite* idle = new Sprite(associated, STAGE1_BOSS_IDLE_ANIMATION, 5, 0.3, 0);
	idle->SetTag("EnemyIdle");
	idle->SetEnabled(true);
	SetSprite(idle);
	associated->AddComponent(idle);
}
void Frog::NotifyCollision(GameObject* other){
	Protagonist* base = (Protagonist*) other->GetComponent("Protagonist");
	if (base != nullptr){
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
void Frog::Kill(){}