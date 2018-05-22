#include "Frog.h"

Frog::Frog(GameObject* associated, int HP) : Enemy(associated, HP){}
Frog::~Frog(){}
void Frog::Update(float dt){

	
	speed.y += 20*dt;

	associated->Box.x += speed.x;
	associated->Box.y += speed.y;

	if ((associated->Box.x) < 0){
		associated->Box.x = 0;
	}
	if ((associated->Box.x+associated->Box.w) > 6000){
		associated->Box.x = 6000 - associated->Box.w;
	}

	if ((associated->Box.y+associated->Box.h) > 600){
		Land();
		associated->Box.y = 600 - associated->Box.h;
	}
}
void Frog::Start(){
	Sprite* idle = new Sprite(associated, STAGE1_BOSS_IDLE_ANIMATION, 5, 0.3, 0);
	idle->SetTag("EnemyIdle");
	idle->SetEnabled(true);
	SetSprite(idle);
	associated->AddComponent(idle);
}
void Frog::NotifyCollision(GameObject* other){}
void Frog::Attack(){}
void Frog::Land(){}
void Frog::Kill(){}