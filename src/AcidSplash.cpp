#include "AcidSplash.h"

AcidSplash::AcidSplash(GameObject* associated, double angle, float speed, int damage, string sprite, int frameCount) : Component(associated){
	Sprite* novo = new Sprite(associated, sprite,frameCount,0.3, 0);
	associated->Box.w = novo->GetWidth();
	associated->Box.h = novo->GetHeight();
	associated->angleDeg = angle*(180.0/PI);
	associated->AddComponent(novo);

	this->damage = damage;
	this->speed.x = speed*cos(angle);
	this->speed.y = speed*sin(angle);

	Collider* colisor = new Collider(associated);
	associated->AddComponent(colisor);
}
AcidSplash::~AcidSplash(){}
void AcidSplash::Update(float dt){
	speed.y += 20*dt;

	associated->Box.x += speed.x*dt;
	associated->Box.y += speed.y*dt;

	if (associated->Box.x > 6000 || associated->Box.x < 0 || associated->Box.y < 0 || associated->Box.y > 600){
		associated->RequestDelete();
	}
}
void AcidSplash::Render(){}
bool AcidSplash::Is(string type){
	return(type == "AcidSplash");
}
int AcidSplash::GetDamage(){
	return(damage);
}
void AcidSplash::NotifyCollision(GameObject* other){
	Enemy* base = (Enemy*) other->GetComponent("Enemy");
	if (base != nullptr){
		base->TakeDamage(damage);
		speed.x = 0;
	}
}