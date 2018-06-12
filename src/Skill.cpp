#include "Skill.h"

Skill::Skill(GameObject* associated, float Cooldown, string Activefile, string Cooldownfile) : Component(associated){
	CameraFollower* camera =  new CameraFollower(associated);
	camera->SetOffset(Vec2(associated->Box.x, associated->Box.y));
	associated->AddComponent(camera);

	Activesprite = new Sprite(associated, Activefile);
	Activesprite->SetTag("Active");
	associated->AddComponent(this->Activesprite);

	Cooldownsprite = new Sprite(associated, Cooldownfile);
	Cooldownsprite->SetTag("Cooldown");
	Cooldownsprite->SetEnabled(false);
	associated->AddComponent(this->Cooldownsprite);

	associated->Box.w = Activesprite->GetWidth();
	associated->Box.h = Activesprite->GetHeight();

	SDL_Color color = {255,255,255,0};
	display = new Text(associated, "assets/font/orange kid.ttf", 36, Text::TextStyle::SOLID," ", color);
	associated->AddComponent(display);

	timer.Restart();
	this->CooldownTime = Cooldown;

}
Skill::~Skill(){}
void Skill::Update(float dt){

	if(!Active){
		timer.Update(dt);
	}
	else{
		return;
	}

	float value = CooldownTime - timer.Get();

	if (value <= 0){
		timer.Restart();
		Active = true;
		Cooldownsprite->SetEnabled(false);
		Activesprite->SetEnabled(true);
		display->SetText(" ");
	}
	else{
		display->SetText(to_string((int)ceil(value)));
	}
}
void Skill::Render(){}
bool Skill::Is(string type){
	return(type == "Skill");
}
void Skill::Start(){
	display->SetOffset(Vec2(25, 5));
}
bool Skill::IsActive(){
	return(Active);
}
bool Skill::Use(){
	Active = false;
	Activesprite->SetEnabled(false);
	Cooldownsprite->SetEnabled(true);
}