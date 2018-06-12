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
	state = SkillState::ACTIVE;

}
Skill::~Skill(){}
void Skill::Update(float dt){

	if (state == SkillState::RUNNING){

		timer.Update(dt);
		float value = duration - timer.Get();

		if (value <= 0){
			timer.Restart();
			state = SkillState::COOLDOWN;
			Activesprite->SetEnabled(false);
			Cooldownsprite->SetEnabled(true);
			display->SetText(" ");
		}
		else{
			display->SetText(to_string((int)ceil(value)));
		}
	}
	if (state == SkillState::COOLDOWN){

		timer.Update(dt);
		float value = CooldownTime - timer.Get();

		if (value <= 0){
			timer.Restart();
			state = SkillState::ACTIVE;
			Cooldownsprite->SetEnabled(false);
			Activesprite->SetEnabled(true);
			display->SetText(" ");
		}
		else{
			display->SetText(to_string((int)ceil(value)));
		}
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
	return(state == SkillState::ACTIVE);
}
bool Skill::IsOnCooldown(){
	return(state == SkillState::COOLDOWN);
}
bool Skill::Use(){
	if(duration < 0){
		state = SkillState::COOLDOWN;
		Activesprite->SetEnabled(false);
		Cooldownsprite->SetEnabled(true);
	}
	else{
		state = SkillState::RUNNING;
	}
}

void Skill::SetDuration(float val){
	duration = val;
}

void Skill::SetColor(int R, int G, int B, int alpha){
	SDL_Color color = {R,G,B,alpha};
	display->SetColor(color);
}