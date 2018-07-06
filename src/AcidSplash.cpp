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
	colisor->SetScale(Vec2(0.5,0.1));
	colisor->SetOffset(Vec2(0,0));
	associated->AddComponent(colisor);

	state = AcidSplash::FLYING;

	Sound* sound = new Sound(associated, PROTAGONIST_ACID_SOUND);
	sound->Play(1);
	associated->AddComponent(sound);
}
AcidSplash::~AcidSplash(){}
void AcidSplash::Update(float dt){
	


	associated->Box.x += speed.x*dt;
	associated->Box.y += speed.y*dt;

	if (associated->Box.x > 6000 || associated->Box.x < 0 || associated->Box.y < 0 || associated->Box.y > 600){
		associated->RequestDelete();
	}
	speed.y += 200*dt;
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
		if (state == AcidSplash::FLYING){
			associated->angleDeg = 0;
			base->TakeDamage(damage);
			associated->Box.Centralize(base->GetAssociated()->Box.GetCenter());
			speed.x = 0;
			speed.y = 0;
			state = AcidSplash::STICKING;

			Sound* sound = new Sound(associated, PROTAGONIST_ACID_HIT_SOUND);
			sound->Play(1);
			associated->AddComponent(sound);
		}
		if (state == AcidSplash::STICKING){
			float aux = associated->Box.y;
			associated->Box.Centralize(base->GetAssociated()->Box.GetCenter());
			associated->Box.y = aux;
		}
	}
}