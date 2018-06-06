#include "Protagonist.h"

Protagonist::Protagonist(GameObject* associated) : Component(associated){
	speed.x = 0;
	speed.y = 0;
	flip = false;
	state = PlayerState::NORMAL;

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	state->AddObject(go);

	HealthBar* barra = new HealthBar(go, 5, PROTAGONIST_HEALTHBAR);
	go->AddComponent(barra);
	HPBar = barra;

	limit = state->GetLimit();

	colisor = new Collider(associated);
	colisor->SetScale(Vec2(0.4,0.7));
	colisor->SetOffset(Vec2(0,15));
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
		SetSprite((Sprite*) associated->GetComponentByTag("ProtagFly"));
	}
	if(input.KeyPress(SDLK_w)){
		TakeDamage(1);
	}


	if (state == PlayerState::PUNCHING){
		if (sprite->IsAnimationOver()){
			if (sprite->GetTag() != "ProtagJump"){
				SetSprite((Sprite*) associated->GetComponentByTag("ProtagIdle"));
			}
			state = PlayerState::NORMAL;
			if(Soco.lock() != nullptr)
				Soco.lock()->RequestDelete();
		}
		if (!OnGround)
			speed.y += 20*dt;
	}

	if (state == PlayerState::NORMAL){

		speed.x = 0;

		if(input.KeyPress(SDLK_s)){
			if (flip){
				ShootAcid((8*PI)/6);
			}
			else{
				ShootAcid((10*PI)/6);
			}
		}
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
			OnGround = false;
			speed.y = -450*dt;
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
			Attack();
		}

		if (!OnGround)
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
			SetSprite((Sprite*) associated->GetComponentByTag("ProtagJump"));

		}
	}

	if (state == PlayerState::FLYING){
		OnGround = false;
		speed.x = 0;
		speed.y = 0;
		SetSprite((Sprite*) associated->GetComponentByTag("ProtagFly"));

		if(input.KeyPress(SDLK_c)){
			state = PlayerState::NORMAL;
			SetSprite((Sprite*) associated->GetComponentByTag("ProtagJump"));
		}
		if(input.KeyPress(SDLK_s)){
			if (flip){
				ShootAcid((8*PI)/6);
			}
			else{
				ShootAcid((10*PI)/6);
			}
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
		OnGround = false;
		state = PlayerState::FLYING;
	}

	associated->Box.x += speed.x;
	associated->Box.y += speed.y;

	if ((associated->Box.x) < limit.x){
		associated->Box.x = limit.x;
	}
	if ((associated->Box.x+associated->Box.w) > limit.x+limit.w){
		associated->Box.x = limit.x+limit.w - associated->Box.w;
	}

	if ((associated->Box.y+associated->Box.h) > limit.y+limit.h){
		Land();
		associated->Box.y = limit.y+limit.h - associated->Box.h;
	}

	if ((associated->Box.y) < limit.y){
		speed.y = 0;
		associated->Box.y = limit.y;
	}


	//Camera::pos.x = associated->Box.x+512;
}
void Protagonist::Render(){}
bool Protagonist::Is(string type){
	return(type == "Protagonist");
}
void Protagonist::Start(){
	Sprite* idle = new Sprite(associated, PROTAGONIST_IDLE_ANIMATION, 5, 0.15, 0);
	idle->SetTag("ProtagIdle");
	idle->SetEnabled(true);
	SetSprite(idle);
	associated->AddComponent(idle);

	Sprite* run = new Sprite(associated, PROTAGONIST_RUN_ANIMATION, 6, 0.1, 0);
	run->SetTag("ProtagRun");
	run->SetEnabled(false);
	associated->AddComponent(run);

	Sprite* jump = new Sprite(associated, PROTAGONIST_JUMP_ANIMATION, 8, 0.1, 0);
	jump->SetTag("ProtagJump");
	jump->SetEnabled(false);
	associated->AddComponent(jump);

	Sprite* punch = new Sprite(associated, PROTAGONIST_PUNCH_ANIMATION, 6, 0.03, 0);
	punch->SetTag("ProtagPunch");
	punch->SetEnabled(false);
	associated->AddComponent(punch);

	Sprite* fly = new Sprite(associated, PROTAGONIST_FLY_ANIMATION, 8, 0.005, 0);
	fly->SetTag("ProtagFly");
	fly->SetEnabled(false);
	associated->AddComponent(fly);
}
void Protagonist::NotifyCollision(GameObject* other){
	Platform* base = (Platform*) other->GetComponent("Platform");
	if (base != nullptr){

		bool D = false, E = false, A = false, B = false;

		Vec2 plat = base->GetAssociated()->Box.GetCenter();
		Vec2 protag = colisor->Box.GetCenter();

		/*if ((colisor->Box.y + colisor->Box.h) >= base->GetAssociated()->Box.y && (colisor->Box.y + colisor->Box.h) <= (base->GetAssociated()->Box.y + (base->GetAssociated()->Box.h/2))){
			colisor->Box.y = base->GetAssociated()->Box.y - colisor->Box.h;*/
		
		//Caso a plataforma esteja acima
		if(plat.y < protag.y){
			A = true;
		}
		//Caso a plataforma esteja abaixo
		if(plat.y > protag.y){
			B = true;
		}
		
		//Caso a plataforma esteja a direita
		if(plat.x > protag.x){
			D = true;
		}
		//Caso a plataforma esteja a esquerda
		if(plat.x < protag.x){
			E = true;
		}

		SDL_Log("A: %d B: %d D: %d E: %d", A, B, D, E);

		float subx = 0;
		float suby = 0;
		float offset = 5;
		if (!OnGround)
		{
			

			if (B && (protag.x > base->GetAssociated()->Box.x && protag.x < base->GetAssociated()->Box.x + base->GetAssociated()->Box.w)){
				colisor->Box.y = base->GetAssociated()->Box.y - (colisor->Box.h + offset);
				Land();
			}
			else if(A && (protag.x > base->GetAssociated()->Box.x && protag.x < base->GetAssociated()->Box.x + base->GetAssociated()->Box.w)){
				speed.y = 0;
				colisor->Box.y = base->GetAssociated()->Box.y + (base->GetAssociated()->Box.h + offset);
			}
			else if (A && D){
				subx = abs(colisor->Box.x + colisor->Box.w - base->GetAssociated()->Box.x);
				suby = abs(colisor->Box.y - base->GetAssociated()->Box.y + base->GetAssociated()->Box.h);
				
				if (suby > subx){
					speed.y = 0;
					colisor->Box.y = base->GetAssociated()->Box.y + base->GetAssociated()->Box.h + offset;
				}
				else{
					speed.x = 0;
					colisor->Box.x = base->GetAssociated()->Box.x - (colisor->Box.w + offset);
				}
			}
			else if (A && E){
				subx = abs(base->GetAssociated()->Box.x + base->GetAssociated()->Box.w - colisor->Box.x);
				suby = abs(colisor->Box.y - base->GetAssociated()->Box.y + base->GetAssociated()->Box.h);

				if (suby > subx){
					speed.y = 0;
					colisor->Box.y = base->GetAssociated()->Box.y + base->GetAssociated()->Box.h + offset;
				}
				else{
					speed.x = 0;
					colisor->Box.x = base->GetAssociated()->Box.x + base->GetAssociated()->Box.w + offset;
				}
				
			}
			else if (A){
				speed.y = 0;
				colisor->Box.y = base->GetAssociated()->Box.y + base->GetAssociated()->Box.h + offset;
			}

			if (B && D){
				subx = abs(colisor->Box.x + colisor->Box.w - base->GetAssociated()->Box.x);
				suby = abs(colisor->Box.y - base->GetAssociated()->Box.y + base->GetAssociated()->Box.h);

				if (suby > subx){
					SDL_Log("chegou no Y maior");
					speed.y = 0;
					colisor->Box.y = base->GetAssociated()->Box.y - (colisor->Box.h + offset);
					Land();
				}
				else{
					SDL_Log("chegou no X maior");
					speed.x = 0;
					colisor->Box.x = base->GetAssociated()->Box.x - (colisor->Box.w + offset);
				}
			}
			else if (B && E){
				subx = abs(base->GetAssociated()->Box.x + base->GetAssociated()->Box.w - colisor->Box.x);
				suby = abs(colisor->Box.y + colisor->Box.h - base->GetAssociated()->Box.y);

				if (suby > subx){
					speed.y = 0;
					colisor->Box.y = base->GetAssociated()->Box.y - (colisor->Box.h + offset);
					Land();
				}
				else{
					speed.x = 0;
					colisor->Box.x = base->GetAssociated()->Box.x + (base->GetAssociated()->Box.w + offset);
				}
			}
			else if (B){
				colisor->Box.y = base->GetAssociated()->Box.y - colisor->Box.h + offset;
				Land();
			}

				associated->Box.Centralize(colisor->Box.GetCenter());
		}
	
		
	}

	Column* coluna = (Column*) other->GetComponent("Column");
	if(coluna != nullptr)
	{
		//std::cout << "flip = " << flip << std::endl;
		if((other->Box.x) < (associated->Box.x + associated->Box.w)
		&& !flip
		&& !((associated->Box.y + associated->Box.h) >= other->Box.y && (associated->Box.y + associated->Box.h) <= (other->Box.y + (other->Box.h/2))))
		{
			associated->Box.x = other->Box.x + other->Box.w - associated->Box.w;
			speed.x = 0;
			speed.y = 0;
			SDL_Log("Colisão pela esquerda!");
		}

		if((other->Box.x + other->Box.w) > associated->Box.x
		&& flip
		&& !((associated->Box.y + associated->Box.h) >= other->Box.y && (associated->Box.y + associated->Box.h) <= (other->Box.y + (other->Box.h/2))))
		{
			associated->Box.x = other->Box.x;
			speed.x = 0;
			speed.y = 0;
			SDL_Log("Colisão pela direita!");
		}

		if ((associated->Box.y + associated->Box.h) >= other->Box.y && (associated->Box.y + associated->Box.h) <= (other->Box.y + (other->Box.h/2))){
			associated->Box.y = other->Box.y - associated->Box.h;
			speed.y = 0;
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

	ShitBall* shitball = new ShitBall(go, angle, 700.0, 1,PROTAGONIST_SHITBALL_ANIMATION, 4);

	go->AddComponent(shitball);
	state->AddObject(go);
}

void Protagonist::ShootAcid(double angle){
	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	go->tag = "acid";

	AcidSplash* acid = new AcidSplash(go, angle, 200.0, 1,PROTAGONIST_ACID_ANIMATION, 5);

	go->Box.Centralize(associated->Box.x + associated->Box.w/2 , associated->Box.y + associated->Box.h/4);

	go->AddComponent(acid);
	state->AddObject(go);
}

void Protagonist::Land(){
	speed.y = 0;
	jumpCount = 0;
	OnGround = true;
	if (sprite->GetTag() == "ProtagJump"){
		sprite->SetFrame(0);
		SetSprite((Sprite*) associated->GetComponentByTag("ProtagIdle"));
	}
}

void Protagonist::Attack(){
	speed.x = 0;
	state = PlayerState::PUNCHING;
	SetSprite((Sprite*) associated->GetComponentByTag("ProtagPunch"));
	sprite->SetFrame(0);

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	go->Box.w = 40;
	go->Box.h = 10;
	if (flip){
		go->Box.Centralize(associated->Box.GetCenter().x- 50, associated->Box.GetCenter().y+5);

	}
	else{
		go->Box.Centralize(associated->Box.GetCenter().x+ 50, associated->Box.GetCenter().y+5);

	}

	Punch* punch = new Punch(go,2);

	go->AddComponent(punch);

	Sound* sound = new Sound(go, PROTAGONIST_PUNCH_SOUND);
	sound->Play(1);
	go->AddComponent(sound);

	Soco = state->AddObject(go);
}

void Protagonist::TakeDamage(int dmg){
	HPBar->AddHP(-dmg);
	if (HPBar->GetHP() <= 0){
		Die();
	}
}

void Protagonist::Die(){
	Camera::Unfollow();
	associated->RequestDelete();
	GameData::Player = nullptr;

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	go->Box.x = associated->Box.x;
	go->Box.y = associated->Box.y;
	state->AddObject(go);

	Sprite* sprite = new Sprite(go, PROTAGONIST_DEATH_ANIMATION,14,0.1,1.4);
	go->AddComponent(sprite);

	Sound* sound = new Sound(go, PROTAGONIST_DEATH_SOUND);
	sound->Play(1);
	go->AddComponent(sound);
}
