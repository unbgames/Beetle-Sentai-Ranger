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

	hitSound = PROTAGONIST_PUNCH_HIT_SOUND;
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

	bool hit = false;

	if(targetsPlayer){
		Protagonist* base2 = (Protagonist*) other->GetComponent("Protagonist");
		if (base2 != nullptr){
			base2->TakeDamage(damage);
			hit = true;
		}
	}
	else{
		Enemy* base = (Enemy*) other->GetComponent("Enemy");
		if (base != nullptr){
			base->TakeDamage(damage);		
			hit = true;
		}
	}

	if (hit){
		associated->RequestDelete();

		Game* game = Game::GetInstance();
		State* state = game->GetCurrentState();

		GameObject* go = new GameObject();

		Sound* sound = new Sound(go, hitSound);
		sound->Play(1);
		go->AddComponent(sound);

		state->AddObject(go);
	}
}

void Punch::SetHitSound(string sound){
	hitSound = sound;
}