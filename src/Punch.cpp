#include "Punch.h"

Punch::Punch(GameObject* associated, int damage) : Component(associated){
	this->damage = damage;
	Collider* colisor = new Collider(associated);
	associated->AddComponent(colisor);
}
Punch::~Punch(){}
void Punch::Update(float dt){}
void Punch::Render(){}
bool Punch::Is(string type){
	return(type == "Punch");
}
int Punch::GetDamage(){
	return(damage);
}
void Punch::NotifyCollision(GameObject* other){
	GroundEnemy* base = (GroundEnemy*) other->GetComponent("Enemy");
	if (base != nullptr){
		base->Kill();

	}
}