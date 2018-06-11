#include "Enemy.h"

Enemy::Enemy(GameObject* associated, int HP) : Component(associated){
	speed.x = 0;
	speed.y = 0;
	hp = HP;
	flip = false;
	state = EnemyState::SEARCHING;
	scaleAnimations.x = 1;
	scaleAnimations.y = 1;

	colisor = new Collider(associated);
	associated->AddComponent(colisor);
}
Enemy::~Enemy(){}
void Enemy::Update(float dt){}
void Enemy::Render(){}
bool Enemy::Is(string type){
	return(type == "Enemy");
}
void Enemy::Start(){}
void Enemy::NotifyCollision(GameObject* other){}
void Enemy::SetSprite(Sprite* newSprite){
	if (sprite != nullptr){
		sprite->SetEnabled(false);
	}
	sprite = newSprite;
	associated->Box.w = sprite->GetWidth();
	associated->Box.h = sprite->GetHeight();
	sprite->SetEnabled(true);
	sprite->SetFlip(flip);
}
void Enemy::Attack(){}
void Enemy::Land(){}
void Enemy::Kill(){
	associated->RequestDelete();
}
void Enemy::TakeDamage(int dmg){
	hp-=dmg;
	if(hp <= 0){
	Kill();
	}
}