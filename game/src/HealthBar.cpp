#include "HealthBar.h"

HealthBar::HealthBar(GameObject* associated, int HP, string file) : Component(associated){
	hp = HP;
	sprite = new Sprite(associated, file);
	associated->Box.w = sprite->GetWidth();
	associated->Box.h = sprite->GetHeight();

	position.x = 25;
	position.y = 5;
}
HealthBar::~HealthBar(){}
void HealthBar::Update(float dt){

}
void HealthBar::Render(){

	float x = position.x;
	float y = position.y;
	float w = sprite->GetWidth();

	for (int i = 0; i < hp; ++i){
		
		sprite->Render(x+(w*i),y);
	}
}
bool HealthBar::Is(string type){
	return(type == "Healthbar");
}
void HealthBar::Start(){
}
int HealthBar::GetHP(){
	return(hp);
}
void HealthBar::AddHP(int amount){
	hp += amount;
}

void HealthBar::SetPosition(Vec2 nova){
	position.x = nova.x;
	position.y = nova.y;
}