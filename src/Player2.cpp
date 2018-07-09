#include "Player2.h"

Player2::Player2(GameObject* associated) : Enemy(associated, 50){
	speed.x = 0;
	speed.y = 0;
	state = PlayerState::NORMAL;
	LastState = PlayerState::NORMAL;

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	state->AddObject(go);

	HealthBar* barra = new HealthBar(go, 5, HUD_HEALTHBAR);
	barra->SetPosition(Vec2(725,5));
	go->AddComponent(barra);
	HPBar = barra;

	limit = state->GetLimit();

	colisor->SetScale(Vec2(0.4,0.7));
	colisor->SetOffset(Vec2(0,15));
}

void Player2::SetSprite(Sprite* newSprite){

	if (sprite != nullptr){
		sprite->SetEnabled(false);
	}
	sprite = newSprite;
	associated->Box.w = sprite->GetWidth();
	associated->Box.h = sprite->GetHeight();

	sprite->SetEnabled(true);
	sprite->SetFlip(flip);
}

Player2::~Player2(){
	flySound->Stop();
}
void Player2::Update(float dt){

	InputManager& input = InputManager::GetInstance();

	if((input.KeyPress(SDLK_KP_4) || input.KeyPress(SDLK_0)) && dash->IsActive()){
		dash->Use();
		ChangeState(PlayerState::DASHING);
		SetSprite((Sprite*) associated->GetComponentByTag("ProtagDash"));

		Game* game = Game::GetInstance();
		State* state = game->GetCurrentState();

		GameObject* go = new GameObject();

		Sound* sound = new Sound(go, PROTAGONIST_DASH_SOUND);
		sound->Play(1);
		go->AddComponent(sound);

		state->AddObject(go);
	}

	if(input.KeyPress(SDLK_o)){
		TakeDamage(1);
	}

	if (state == PlayerState::HURTING){
		//SDL_Log("HURTING");
		if (sprite->IsAnimationOver()){
			if (LastState == PlayerState::FLYING){
				SetSprite((Sprite*) associated->GetComponentByTag("ProtagFly"));
			}
			else{
				SetSprite((Sprite*) associated->GetComponentByTag("ProtagIdle"));
			}

			ChangeState(LastState);
		}
		speed.y += 20*dt;
	}


	if (state == PlayerState::PUNCHING){
		//SDL_Log("PUNCHING");
		if (sprite->IsAnimationOver()){
			if (sprite->GetTag() != "ProtagJump"){
				SetSprite((Sprite*) associated->GetComponentByTag("ProtagIdle"));
			}
			ChangeState(PlayerState::NORMAL);
			if(Soco.lock() != nullptr)
				Soco.lock()->RequestDelete();
		}
		speed.y += 20*dt;
	}

	if (state == PlayerState::NORMAL){
		//SDL_Log("NORMAL");
		speed.x = 0;

		if(input.KeyPress(SDLK_KP_3) || input.KeyPress(SDLK_9)){
			if (flip){
				ShootAcid((8*PI)/6);
			}
			else{
				ShootAcid((10*PI)/6);
			}
		}
		if(input.KeyPress(SDLK_KP_2) || input.KeyPress(SDLK_8)){
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

		if(input.KeyPress(SDLK_KP_1) || input.KeyPress(SDLK_7)){
			Attack();
		}
		speed.y += 20*dt;
	}

	if (state == PlayerState::DASHING){
		//SDL_Log("DASHING");
		speed.y = 0;
		if (flip){
			speed.x = -1000*dt;
		}
		else{
			speed.x = 1000*dt;
		}

		counter.Update(dt);

		if (counter.Get() >= 0.5){
			counter.Restart();

			if (LastState == PlayerState::FLYING)
				SetSprite((Sprite*) associated->GetComponentByTag("ProtagFly"));
			else
				SetSprite((Sprite*) associated->GetComponentByTag("ProtagIdle"));

			ChangeState(LastState);
		}
	}

	if (state == PlayerState::FLYING){
		//SDL_Log("FLYING");
		speed.x = 0;
		speed.y = 0;
		SetSprite((Sprite*) associated->GetComponentByTag("ProtagFly"));

		if(fly->IsOnCooldown()){
			ChangeState(PlayerState::NORMAL);
			SetSprite((Sprite*) associated->GetComponentByTag("ProtagJump"));
		}
		if(input.KeyPress(SDLK_KP_3) || input.KeyPress(SDLK_9)){
			if (flip){
				ShootAcid((8*PI)/6);
			}
			else{
				ShootAcid((10*PI)/6);
			}
		}
		if(input.KeyPress(SDLK_KP_2) || input.KeyPress(SDLK_8)){
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
	else if((input.KeyPress(SDLK_KP_5) || input.KeyPress(SDLK_MINUS)) && fly->IsActive()){
		ChangeState(PlayerState::FLYING);
		fly->Use();
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
void Player2::Render(){}
void Player2::Start(){
	Sprite* idle = new Sprite(associated, PLAYER2_IDLE_ANIMATION, 5, 0.15, 0);
	idle->SetTag("ProtagIdle");
	idle->SetEnabled(true);
	idle->SetColorMod(254,0,167);
	SetSprite(idle);
	associated->AddComponent(idle);

	Sprite* run = new Sprite(associated, PLAYER2_RUN_ANIMATION, 6, 0.1, 0);
	run->SetTag("ProtagRun");
	run->SetEnabled(false);
	run->SetColorMod(254,0,167);
	associated->AddComponent(run);

	Sprite* jump = new Sprite(associated, PLAYER2_JUMP_ANIMATION, 8, 0.1, 0);
	jump->SetTag("ProtagJump");
	jump->SetEnabled(false);
	jump->StopOnFrame(7);
	jump->SetColorMod(254,0,167);
	associated->AddComponent(jump);

	Sprite* punch = new Sprite(associated, PLAYER2_PUNCH_ANIMATION, 6, 0.03, 0);
	punch->SetTag("ProtagPunch");
	punch->SetEnabled(false);
	punch->StopOnFrame(5);
	punch->SetColorMod(254,0,167);
	associated->AddComponent(punch);

	Sprite* Dash = new Sprite(associated, PLAYER2_DASH_ANIMATION, 8, 0.0625, 0);
	Dash->SetTag("ProtagDash");
	Dash->SetEnabled(false);
	Dash->SetColorMod(254,0,167);
	associated->AddComponent(Dash);

	Sprite* flying = new Sprite(associated, PLAYER2_FLY_ANIMATION, 8, 0.005, 0);
	flying->SetTag("ProtagFly");
	flying->SetEnabled(false);
	flying->SetColorMod(254,0,167);
	associated->AddComponent(flying);

	Sprite* hurt = new Sprite(associated, PLAYER2_GETHURT_ANIMATION, 6, 0.05, 0);
	hurt->SetTag("ProtagHurt");
	hurt->SetEnabled(false);
	hurt->SetColorMod(254,0,167);
	associated->AddComponent(hurt);

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();

	go->Box.x = 725;
	go->Box.y = 70;

	shit = new Skill(go, 1.0, HUD_SHIT_ICON, HUD_SHIT_COOLDOWN_ICON);
	state->AddObject(go);
	go->AddComponent(shit);

	GameObject* go2 = new GameObject();

	go2->Box.x = 790;
	go2->Box.y = 70;

	acid = new Skill(go2, 1.0, HUD_ACID_ICON, HUD_ACID_COOLDOWN_ICON);
	state->AddObject(go2);
	go2->AddComponent(acid);

	GameObject* go3 = new GameObject();

	go3->Box.x = 855;
	go3->Box.y = 70;

	dash = new Skill(go3, 4.0, HUD_DASH_ICON, HUD_DASH_COOLDOWN_ICON);
	state->AddObject(go3);
	go3->AddComponent(dash);

	GameObject* go4 = new GameObject();

	go4->Box.x = 920;
	go4->Box.y = 70;

	fly = new Skill(go4, 5.0, HUD_FLY_ICON, HUD_FLY_COOLDOWN_ICON);
	fly->SetDuration(5.0);
	fly->SetColor(0,0,0,0);
	state->AddObject(go4);
	go4->AddComponent(fly);

	flySound = new Sound(associated, PROTAGONIST_FLY_SOUND);
	associated->AddComponent(flySound);

}
void Player2::NotifyCollision(GameObject* other){
	Terreno* base = (Terreno*) other->GetComponent("Terreno");
	if (base != nullptr){

		Rect box1 = colisor->Box;
		Rect box2 = base->GetAssociated()->Box;

		float dx = box1.x - box2.x;
	    float px = (box2.w + box1.w) - abs(dx);//penetration depth in x

	    float offx = 0;
	    float offy = 0;

	    float dy = box1.y - box2.y;
	    float py = (box2.h + box1.h) - abs(dy);//penetration depth in y

	    if(dx < 0){
            offx = -box2.w;
        }
        else{
            offx = -box1.w;
        }
        px += offx;

        if(dy < 0){
            offy = -box2.h;
        }
        else{
			offy = -box1.h;
        }
        py += offy;

        if(px < py){
        	speed.x = 0;
            //project in x
            if(dx < 0){
            	//SDL_Log("esquerda");
                //project to the left
                px *= -1;
                py *= 0;
                //offx = box2.w;
            }
            else{
            	//SDL_Log("direita");
                //proj to right
                py = 0;
                //offx = -box1.w;
            }
        }
        else{
        	//SDL_Log("acima");
        	speed.y = 0;
            //project in y
            if(dy < 0){
                //project up
                px = 0;
                py *= -1;
                //offy = box2.h;
                Land();
            }
            else{
            	//SDL_Log("abaixo");
                //project down
                px = 0;
                //offy = -box1.h;

            }
        }
        // we get px and py , penetration vector
        //box1.x += px + offx;
        //box1.y += py + offy;
        box1.x += px;
        box1.y += py;

        //associated->Box.x += px + offx;
        //associated->Box.y += py + offy;

        associated->Box.x += px;
        associated->Box.y += py;

        colisor->Box = box1;

		//associated->Box.Centralize(colisor->Box.GetCenter());
	}
}

//espera angulo em radianos
void Player2::ShootShit(float angle){

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

	ShitBall* shitball = new ShitBall(go, angle, 700.0, 1, true, PROTAGONIST_SHITBALL_ANIMATION, PROTAGONIST_SHIT_SOUND, 3);

	go->AddComponent(shitball);
	state->AddObject(go);
}

void Player2::ShootAcid(double angle){

	if (!acid->IsActive()){
		return;
	}
	acid->Use();

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	go->tag = "acid";

	AcidSplash* acid = new AcidSplash(go, angle, 200.0, 1,PROTAGONIST_ACID_ANIMATION, 5, true);

	go->Box.Centralize(associated->Box.x + associated->Box.w/2 , associated->Box.y + associated->Box.h/4);

	go->AddComponent(acid);
	state->AddObject(go);
}

void Player2::Land(){
	speed.y = 0;
	jumpCount = 0;
	if (sprite->GetTag() == "ProtagJump"){
		sprite->SetFrame(0);
		SetSprite((Sprite*) associated->GetComponentByTag("ProtagIdle"));
	}
}

void Player2::Attack(){
	speed.x = 0;
	ChangeState(PlayerState::PUNCHING);
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

	Punch* punch = new Punch(go,2, true);

	go->AddComponent(punch);

	Sound* sound = new Sound(go, PROTAGONIST_PUNCH_SOUND);
	sound->Play(1);
	go->AddComponent(sound);

	Soco = state->AddObject(go);
}

void Player2::TakeDamage(int dmg){

	InputManager& input = InputManager::GetInstance();

	if(input.IsKeyDown(SDLK_e) || state == PlayerState::DASHING){
		return;
	}

	HPBar->AddHP(-dmg);
	if (HPBar->GetHP() <= 0){
		Die();
	}
	SetSprite((Sprite*) associated->GetComponentByTag("ProtagHurt"));
	sprite->SetFrame(0);
	ChangeState(PlayerState::HURTING);
}

void Player2::Die(){
	associated->RequestDelete();

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	go->Box.x = associated->Box.x;
	go->Box.y = associated->Box.y;
	state->AddObject(go);

	Sprite* sprite = new Sprite(go, PROTAGONIST_DEATH_ANIMATION,14,0.1,1.4);
	sprite->SetColorMod(219,0,147);
	go->AddComponent(sprite);

	Sound* sound = new Sound(go, PROTAGONIST_DEATH_SOUND);
	sound->Play(1);
	go->AddComponent(sound);
}

void Player2::ChangeState(PlayerState next){
	if (next == state){
		return;
	}
	if (state == PlayerState::FLYING){
		flySound->Stop();
	}
	if (next == PlayerState::FLYING){
		flySound->Play(-1);
	}
	LastState = state;
	state = next;
}
