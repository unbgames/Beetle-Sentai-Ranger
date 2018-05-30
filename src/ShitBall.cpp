#include "ShitBall.h"

ShitBall::ShitBall(GameObject* associated, double angle, float speed, int damage, string sprite, int frameCount) : Component(associated){
	
	Sprite* novo = new Sprite(associated, sprite,frameCount,0.3, 0);
	associated->Box.w = novo->GetWidth();
	associated->Box.h = novo->GetHeight();
	associated->angleDeg = angle*(180.0/PI);
	associated->AddComponent(novo);

	this->damage = damage;
	this->speed.x = speed*cos(angle)/2;
	this->speed.y = 0;

	Collider* colisor = new Collider(associated);
	colisor->SetScale(Vec2(0.4,0.37));
	colisor->SetOffset(Vec2(13,0));
	associated->AddComponent(colisor);

	Sound* sound = new Sound(associated, PROTAGONIST_SHIT_SOUND);
	sound->Play(1);
	associated->AddComponent(sound);
}
ShitBall::~ShitBall(){}
void ShitBall::Update(float dt){

	speed.y += 20*dt;

	associated->Box.x += speed.x*dt;
	associated->Box.y += speed.y*dt;

	if (associated->Box.x > 6000 || associated->Box.x < 0 || associated->Box.y < 0 || associated->Box.y > 600){
		associated->RequestDelete();
	}

}
void ShitBall::Render(){}
bool ShitBall::Is(string type){
	return(type == "ShitBall");
}
int ShitBall::GetDamage(){
	return(damage);
}
void ShitBall::NotifyCollision(GameObject* other){
	Enemy* base = (Enemy*) other->GetComponent("Enemy");
	if (base != nullptr){
		base->TakeDamage(damage);
		associated->RequestDelete();
	}
}