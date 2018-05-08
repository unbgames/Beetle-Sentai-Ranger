#include "Protagonist.h"

Protagonist::Protagonist(GameObject* associated, string file, int frameCount, float frameTime) : Component(associated){
	speed.x = 0;
	speed.y = 0;
	hp = 5;
	sprite = new Sprite(associated, file, frameCount, frameTime, 0);
	associated->Box.w = sprite->GetWidth();
	associated->Box.h = sprite->GetHeight();
	associated->AddComponent(sprite);
	flip = false;
	state = PlayerState::NORMAL;
}

Protagonist::Protagonist(GameObject* associated) : Component(associated){
	speed.x = 0;
	speed.y = 0;
	hp = 5;
	flip = false;
	state = PlayerState::NORMAL;
}

void Protagonist::SetSprite(Sprite* newSprite){
	sprite = newSprite;
	associated->Box.w = sprite->GetWidth();
	associated->Box.h = sprite->GetHeight();
}

Protagonist::~Protagonist(){}
void Protagonist::Update(float dt){

	InputManager& input = InputManager::GetInstance();

	if(input.KeyPress(SDLK_x)){
		state = PlayerState::DASHING;
	}

	if (state == PlayerState::NORMAL){
	
		speed.x = 0;

		if(input.KeyPress(SDLK_z)){
			if (flip){
				ShootShit(PI);
			}
			else{
				ShootShit(0);
			}
		}

		if(input.KeyPress(SDLK_UP) && jumpCount < 3){
			jumpCount++;
			speed.y = -400*dt;
		}	
		if(input.IsKeyDown(SDLK_LEFT)){
			if (sprite->GetTag() == "ProtagIdle"){
				sprite->SetEnabled(false);
				SetSprite((Sprite*) associated->GetComponentByTag("ProtagRun"));
				sprite->SetEnabled(true);
			}
			speed.x = -400*dt;
			flip = true;
			sprite->SetFlip(flip);
		}
		else if(input.IsKeyDown(SDLK_RIGHT)){

			if (sprite->GetTag() == "ProtagIdle"){
				sprite->SetEnabled(false);
				SetSprite((Sprite*) associated->GetComponentByTag("ProtagRun"));
				sprite->SetEnabled(true);
			}
			speed.x = 400*dt;
			flip = false;
			sprite->SetFlip(flip);
		}
		else{
			if (sprite->GetTag() == "ProtagRun"){
				sprite->SetEnabled(false);
				SetSprite((Sprite*) associated->GetComponentByTag("ProtagIdle"));
				sprite->SetEnabled(true);
				sprite->SetFlip(flip);
			}
		}
		speed.y += 20*dt;
	}

	if (state == PlayerState::DASHING){
		if (flip){
			speed.x = -1000*dt;
		}
		else{
			speed.x = 1000*dt;
		}

		counter.Update(dt);

		if (counter.Get() >= 0.5){
			state = PlayerState::NORMAL;
			counter.Restart();
		}
	}

	if (state == PlayerState::FLYING){
		speed.x = 0;
		speed.y = 0;
		SDL_Log("voando");

		if(input.KeyPress(SDLK_c)){
			state = PlayerState::NORMAL;
		}
		if(input.KeyPress(SDLK_z)){
			if (flip){
				ShootShit(PI);
			}
			else{
				ShootShit(0);
			}
		}

		if(input.IsKeyDown(SDLK_UP)){
			speed.y = -400*dt;
		}	
		if(input.IsKeyDown(SDLK_DOWN)){
			speed.y = 400*dt;
		}
		if(input.IsKeyDown(SDLK_LEFT)){
			speed.x = -400*dt;
			flip = true;
			sprite->SetFlip(flip);
		}
		if(input.IsKeyDown(SDLK_RIGHT)){
			speed.x = 400*dt;
			flip = false;
			sprite->SetFlip(flip);
		}
	}
	else if(input.KeyPress(SDLK_c)){
		state = PlayerState::FLYING;
	}

	associated->Box.x += speed.x;
	associated->Box.y += speed.y;

	if ((associated->Box.x) < 0){
		associated->Box.x = 0;
	}
	if ((associated->Box.x+associated->Box.w) > 6000){
		associated->Box.x = 6000 - associated->Box.w;
	}

	if ((associated->Box.y+associated->Box.h) > 600){
		jumpCount = 0;
		associated->Box.y = 600 - associated->Box.h;
	}
	

	//Camera::pos.x = associated->Box.x+512;
}
void Protagonist::Render(){}
bool Protagonist::Is(string type){
	return(type == "Protagonist");
}
void Protagonist::Start(){}
void Protagonist::NotifyCollision(GameObject* other){}

//espera angulo em radianos
void Protagonist::ShootShit(float angle){

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	go->Box.Centralize(associated->Box.GetCenter().x , associated->Box.GetCenter().y);
	go->tag = "shitball";

	ShitBall* shitball = new ShitBall(go, angle, 200.0, 1,"assets/img/shitball.png", 4);

	go->AddComponent(shitball);
	state->AddObject(go);
}