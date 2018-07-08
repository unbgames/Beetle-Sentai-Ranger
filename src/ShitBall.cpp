#include "ShitBall.h"

ShitBall::ShitBall(GameObject* associated, double angle, float speed, int damage, bool targetPlayer, string sprite, string sound,  int frameCount) : Component(associated){
	
	Sprite* novo = new Sprite(associated, sprite,frameCount,0.3, 0);
	associated->Box.w = novo->GetWidth();
	associated->Box.h = novo->GetHeight();
	associated->angleDeg = angle*(180.0/PI);
	associated->AddComponent(novo);

	this->damage = damage;
	this->speed.y = speed*sin(angle);
	this->speed.x = speed*cos(angle);
	this->targetPlayer = targetPlayer;

	Collider* colisor = new Collider(associated);
	colisor->SetScale(Vec2(0.4,0.37));
	colisor->SetOffset(Vec2(13,0));
	associated->AddComponent(colisor);

	Sound* noise = new Sound(associated, sound);
	noise->Play(1);
	associated->AddComponent(noise);
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
	if (base != nullptr && !targetPlayer){
		base->TakeDamage(damage);
		associated->RequestDelete();
	}

	Protagonist* player = (Protagonist*) other->GetComponent("Protagonist");
	if (player != nullptr && targetPlayer){
		player->TakeDamage(damage);
		associated->RequestDelete();
	}
	
	Terreno* terrain = (Terreno*) other->GetComponent("Terreno");
	if(terrain != nullptr){
		associated->RequestDelete();
	}
}