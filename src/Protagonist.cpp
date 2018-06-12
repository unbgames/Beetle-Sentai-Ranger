#include "Protagonist.h"

Protagonist::Protagonist(GameObject* associated) : Component(associated){
	associated->AddComponent(this);
	speed.x = 0;
	speed.y = 0;
	flip = false;
	state = PlayerState::NORMAL;

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	state->AddObject(go);

	HealthBar* barra = new HealthBar(go, 5, HUD_HEALTHBAR);
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

	if(input.KeyPress(SDLK_x) && dash->IsActive()){
		dash->Use();
		state = PlayerState::DASHING;
		SetSprite((Sprite*) associated->GetComponentByTag("ProtagFly"));
	}
	if(input.KeyPress(SDLK_w)){
		TakeDamage(1);
	}

	if (state == PlayerState::HURTING){
		if (sprite->IsAnimationOver()){
			SetSprite((Sprite*) associated->GetComponentByTag("ProtagIdle"));
			state = PlayerState::NORMAL;
		}
		speed.y += 20*dt;
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

	Sprite* flying = new Sprite(associated, PROTAGONIST_FLY_ANIMATION, 8, 0.005, 0);
	flying->SetTag("ProtagFly");
	flying->SetEnabled(false);
	associated->AddComponent(flying);

	Sprite* hurt = new Sprite(associated, PROTAGONIST_GETHURT_ANIMATION, 6, 0.05, 0);
	hurt->SetTag("ProtagHurt");
	hurt->SetEnabled(false);
	associated->AddComponent(hurt);

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();

	go->Box.x = 949;
	go->Box.y = 0;

	shit = new Skill(go, 1.0, HUD_SHIT_ICON, HUD_SHIT_COOLDOWN_ICON);
	state->AddObject(go);
	go->AddComponent(shit);

	GameObject* go2 = new GameObject();

	go2->Box.x = 874;
	go2->Box.y = 0;

	acid = new Skill(go2, 2.0, HUD_ACID_ICON, HUD_ACID_COOLDOWN_ICON);
	state->AddObject(go2);
	go2->AddComponent(acid);

	GameObject* go3 = new GameObject();

	go3->Box.x = 799;
	go3->Box.y = 0;

	dash = new Skill(go3, 2.0, HUD_DASH_ICON, HUD_DASH_COOLDOWN_ICON);
	state->AddObject(go3);
	go3->AddComponent(dash);

	GameObject* go4 = new GameObject();

	go4->Box.x = 724;
	go4->Box.y = 0;

	fly = new Skill(go4, 5.0, HUD_FLY_ICON, HUD_FLY_COOLDOWN_ICON);
	state->AddObject(go4);
	go4->AddComponent(fly);

}
void Protagonist::NotifyCollision(GameObject* other){
	Platform* base = (Platform*) other->GetComponent("Platform");
	if (base != nullptr){

		Rect box1 = colisor->Box;
		Rect box2 = base->GetAssociated()->Box;

		float dx = box1.x - box2.x;
	    float px = (box2.w + box1.w) - abs(dx);//penetration depth in x

	    float offx = 0;
	    float offy = 0;

	    float dy = box1.y - box2.y;
	    float py = (box2.h + box1.h) - abs(dy);//penetration depth in y

	            // Collision detected

	            if(px < py){
	            	speed.x = 0;
	                //project in x
	                if(dx < 0){
	                    //project to the left
	                    px *= -1;
	                    py *= 0;
	                    offx = box2.w;
	                }
	                else{
	                    //proj to right
	                    py = 0;
	                    offx = -box1.w;
	                }
	            }
	            else{
	            	speed.y = 0;
	                //project in y
	                if(dy < 0){
	                    //project up
	                    px = 0;
	                    py *= -1;
	                    offy = box2.h;
	                    Land();
	                }
	                else{
	                    //project down
	                    px = 0;
	                    offy = -box1.h;

	                }
	            }
	            // we get px and py , penetration vector
	            box1.x += px + offx;
	            box1.y += py + offy;

	            associated->Box.x += px + offx;
	            associated->Box.y += py + offy;

	            colisor->Box = box1;
				base->GetAssociated()->Box = box2;

				//associated->Box.Centralize(colisor->Box.GetCenter());
	}

	Column* coluna = (Column*) other->GetComponent("Column");
	if(coluna != nullptr)
	{
		Rect box1 = colisor->Box;
		Rect box2 = coluna->GetAssociated()->Box;

		float dx = box1.x - box2.x;
	  float px = (box2.w + box1.w) - abs(dx);//penetration depth in x

	  float offx = 0;
	  float offy = 0;

	  float dy = box1.y - box2.y;
	  float py = (box2.h + box1.h) - abs(dy);//penetration depth in y

	  // Collision detected

	  if(px < py){
	  	speed.x = 0;
	    //project in x
	    if(dx < 0){
	    	//project to the left
	      px *= -1;
	    	py *= 0;
	      offx = box2.w;
	    }
	    else
			{
	    	//proj to right
	      py = 0;
	      offx = -box1.w;
	    }
	  }
	  else{
	  	speed.y = 0;
	    //project in y
	    if(dy < 0){
	    	//project up
	      px = 0;
	      py *= -1;
	      offy = box2.h;
	      Land();
		}
	  else{
	  	//project down
	    px = 0;
	    offy = -box1.h;
    }
  }
		// we get px and py , penetration vector
		box1.x += px + offx;
		box1.y += py + offy;

		associated->Box.x += px + offx;
		associated->Box.y += py + offy;

		colisor->Box = box1;
		coluna->GetAssociated()->Box = box2;

		//associated->Box.Centralize(colisor->Box.GetCenter());
	}

	Terrain* terrain = (Terrain*) other->GetComponent("Terrain");
	if(terrain != nullptr)
	{
		Rect box1 = colisor->Box;
		Rect box2 = terrain->GetAssociated()->Box;

		float dx = box1.x - box2.x;
	  float px = (box2.w + box1.w) - abs(dx);//penetration depth in x

	  float offx = 0;
	  float offy = 0;

	  float dy = box1.y - box2.y;
	  float py = (box2.h + box1.h) - abs(dy);//penetration depth in y

	  // Collision detected

	  if(px < py){
	  	speed.x = 0;
	    //project in x
	    if(dx < 0){
	    	//project to the left
	      px *= -1;
	    	py *= 0;
	      offx = box2.w;
	    }
	    else
			{
	    	//proj to right
	      py = 0;
	      offx = -box1.w;
	    }
	  }
	  else{
	  	speed.y = 0;
	    //project in y
	    if(dy < 0){
	    	//project up
	      px = 0;
	      py *= -1;
	      offy = box2.h;
	      Land();
		}
	  else{
	  	//project down
	    px = 0;
	    offy = -box1.h;
    }
  }
		// we get px and py , penetration vector
		box1.x += px + offx;
		box1.y += py + offy;

		associated->Box.x += px + offx;
		associated->Box.y += py + offy;

		colisor->Box = box1;
		terrain->GetAssociated()->Box = box2;

		//associated->Box.Centralize(colisor->Box.GetCenter());
	}
}

//espera angulo em radianos
void Protagonist::ShootShit(float angle){

	if (!shit->IsActive()){
		return;
	}
	shit->Use();

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	go->Box.Centralize(associated->Box.GetCenter().x , associated->Box.GetCenter().y);
	go->Box.y -= 35;
	go->tag = "shitball";

	ShitBall* shitball = new ShitBall(go, angle, 700.0, 1, false, PROTAGONIST_SHITBALL_ANIMATION, PROTAGONIST_SHIT_SOUND, 3);

	go->AddComponent(shitball);
	state->AddObject(go);
}

void Protagonist::ShootAcid(double angle){

	if (!acid->IsActive()){
		return;
	}
	acid->Use();

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

	InputManager& input = InputManager::GetInstance();

	if(input.IsKeyDown(SDLK_e)){
		return;
	}

	HPBar->AddHP(-dmg);
	if (HPBar->GetHP() <= 0){
		Die();
	}
	SetSprite((Sprite*) associated->GetComponentByTag("ProtagHurt"));
	sprite->SetFrame(0);
	state = PlayerState::HURTING;
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
