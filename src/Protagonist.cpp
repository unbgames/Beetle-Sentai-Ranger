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

	Collider* colisor = new Collider(associated);
	associated->AddComponent(colisor);
}

void Protagonist::SetSprite(Sprite* newSprite){
	
	if (sprite != nullptr){
		sprite->SetEnabled(false);
	}
	sprite = newSprite;
	associated->Box.w = sprite->GetWidth();
	associated->Box.h = sprite->GetHeight();
	sprite->SetEnabled(true);
	sprite->SetFlip(flip);
}

Protagonist::~Protagonist(){}
void Protagonist::Update(float dt){

	InputManager& input = InputManager::GetInstance();

	if(input.KeyPress(SDLK_x)){
		state = PlayerState::DASHING;
	}

	if (state == PlayerState::PUNCHING){
		if (sprite->IsAnimationOver()){
			if (sprite->GetTag() != "ProtagJump"){
				SetSprite((Sprite*) associated->GetComponentByTag("ProtagIdle"));	
			}
			state = PlayerState::NORMAL;
		}
		speed.y += 20*dt;
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

		if (sprite->GetTag() != "ProtagJump"){
			SetSprite((Sprite*) associated->GetComponentByTag("ProtagIdle"));
		}

		if(input.KeyPress(SDLK_UP) && jumpCount < 1){
			SetSprite((Sprite*) associated->GetComponentByTag("ProtagJump"));
			jumpCount++;
			speed.y = -600*dt;
		}	
		if(input.IsKeyDown(SDLK_LEFT)){
			speed.x = -400*dt;
			flip = true;
			if (sprite->GetTag() == "ProtagIdle"){
				SetSprite((Sprite*) associated->GetComponentByTag("ProtagRun"));
			}
			else
				sprite->SetFlip(flip);
		}
		else if(input.IsKeyDown(SDLK_RIGHT)){
			speed.x = 400*dt;
			flip = false;
			if (sprite->GetTag() == "ProtagIdle"){
				SetSprite((Sprite*) associated->GetComponentByTag("ProtagRun"));
			}
			else
				sprite->SetFlip(flip);
		}

		if(input.KeyPress(SDLK_a)){
			Punch();
		}

		speed.y += 20*dt;
	}

	if (state == PlayerState::DASHING){
		speed.y = 0;
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
		Land();
		associated->Box.y = 600 - associated->Box.h;
	}

	if ((associated->Box.y) < 0){
		speed.y = 0;
		associated->Box.y = 0;
	}
	

	//Camera::pos.x = associated->Box.x+512;
}
void Protagonist::Render(){}
bool Protagonist::Is(string type){
	return(type == "Protagonist");
}
void Protagonist::Start(){
	Sprite* idle = new Sprite(associated, PROTAGONIST_IDLE_ANIMATION, 5, 0.3, 0);
	idle->SetTag("ProtagIdle");
	idle->SetEnabled(true);
	SetSprite(idle);
	associated->AddComponent(idle);

	Sprite* run = new Sprite(associated, PROTAGONIST_RUN_ANIMATION, 6, 0.2, 0);
	run->SetTag("ProtagRun");
	run->SetEnabled(false);
	associated->AddComponent(run);

	Sprite* jump = new Sprite(associated, PROTAGONIST_JUMP_ANIMATION, 11, 0.3, 0);
	jump->SetTag("ProtagJump");
	jump->SetEnabled(false);
	associated->AddComponent(jump);

	Sprite* punch = new Sprite(associated, PROTAGONIST_PUNCH_ANIMATION, 4, 0.1, 0);
	punch->SetTag("ProtagPunch");
	punch->SetEnabled(false);
	associated->AddComponent(punch);
}
void Protagonist::NotifyCollision(GameObject* other){
	Platform* base = (Platform*) other->GetComponent("Platform");
	if (base != nullptr){
		if ((associated->Box.y + associated->Box.h) >= other->Box.y && (associated->Box.y + associated->Box.h) <= (other->Box.y + (other->Box.h/2))){
			associated->Box.y = other->Box.y - associated->Box.h;
			Land();
		}

	}
}

//espera angulo em radianos
void Protagonist::ShootShit(float angle){

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	go->Box.Centralize(associated->Box.GetCenter().x , associated->Box.GetCenter().y);
	go->tag = "shitball";

	ShitBall* shitball = new ShitBall(go, angle, 200.0, 1,PROTAGONIST_SHITBALL_ANIMATION, 4);

	go->AddComponent(shitball);
	state->AddObject(go);
}

void Protagonist::Land(){
	speed.y = 0;
	jumpCount = 0;
	if (sprite->GetTag() == "ProtagJump"){
		SetSprite((Sprite*) associated->GetComponentByTag("ProtagIdle"));
	}
}

void Protagonist::Punch(){
	speed.x = 0;
	state = PlayerState::PUNCHING;
	SetSprite((Sprite*) associated->GetComponentByTag("ProtagPunch"));
	sprite->SetFrame(0);
}