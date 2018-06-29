#include "Punch.h"

Punch::Punch(GameObject* associated, int damage, bool target, float secondsToSelfDestruct) : Component(associated){
	this->damage = damage;
	this->secondsToSelfDestruct = secondsToSelfDestruct;
	Collider* colisor = new Collider(associated);
	associated->AddComponent(colisor);

	targetsPlayer = target;
	if (targetsPlayer){
		//SDL_Log("true");
	}
}
Punch::~Punch(){}
void Punch::Update(float dt){
	if (secondsToSelfDestruct == 0){
		return;
	}
	time += dt;
	if (time >= secondsToSelfDestruct){
		associated->RequestDelete();
	}
}
void Punch::Render(){}
bool Punch::Is(string type){
	return(type == "Punch");
}
int Punch::GetDamage(){
	return(damage);
}
void Punch::NotifyCollision(GameObject* other){
	if(targetsPlayer){
		Protagonist* base2 = (Protagonist*) other->GetComponent("Protagonist");
		if (base2 != nullptr){
			base2->TakeDamage(damage);
			associated->RequestDelete();
		}
	}
	else{
		Enemy* base = (Enemy*) other->GetComponent("Enemy");
		if (base != nullptr){
			base->TakeDamage(damage);
			associated->RequestDelete();
		}
	}
}