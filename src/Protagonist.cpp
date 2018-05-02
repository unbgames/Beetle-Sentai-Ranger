#include "Protagonist.h"

Protagonist::Protagonist(GameObject* associated, string file, int frameCount, int frameTime) : Component(associated){
	speed.x = 0;
	speed.y = 0;
	hp = 30;
	sprite = new Sprite(associated, file, frameCount, frameTime, 0);
	associated->Box.w = sprite->GetWidth();
	associated->Box.h = sprite->GetHeight();
	associated->AddComponent(sprite);
}
Protagonist::~Protagonist(){}
void Protagonist::Update(float dt){

	speed.x = 0;

	InputManager& input = InputManager::GetInstance();

	if(input.KeyPress(SDLK_w) && jumpCount == 0){
		jumpCount++;
		speed.y = -400*dt;
	}	
	if(input.IsKeyDown(SDLK_s)){
	}
	if(input.IsKeyDown(SDLK_a)){
		speed.x = -400*dt;
		sprite->SetFlip(true);
	}
	if(input.IsKeyDown(SDLK_d)){
		speed.x = 400*dt;
		sprite->SetFlip(false);
	}
	speed.y += 20*dt;

	associated->Box.x += speed.x;
	associated->Box.y += speed.y;

	if ((associated->Box.y+associated->Box.h) > 600){
		jumpCount = 0;
		associated->Box.y = 600 - associated->Box.h;
	}

	//Camera::pos.x = associated->Box.x;
}
void Protagonist::Render(){}
bool Protagonist::Is(string type){
	return(type == "Protagonist");
}
void Protagonist::Start(){}
void Protagonist::NotifyCollision(GameObject* other){}