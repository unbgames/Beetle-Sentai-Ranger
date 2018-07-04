#include "Frog.h"

Frog::Frog(GameObject* associated, int HP) : Enemy(associated, HP){
	SearchTimer.Restart();

	colisor->SetScale(Vec2(0.2,0.65));
	colisor->SetOffset(Vec2(120,55));
}
Frog::~Frog(){}

void Frog::SetSprite(Sprite* newSprite){
	if (sprite != nullptr){
		sprite->SetEnabled(false);
	}
	sprite = newSprite;
	associated->Box.w = sprite->GetWidth();
	associated->Box.h = sprite->GetHeight();

	//associated->Box.w *= 0.5;

	sprite->SetEnabled(true);
	sprite->SetFlip(flip);
}

void Frog::Update(float dt){
	
	float hipo = dt*700;
	Rect limit = Game::GetInstance()->GetCurrentState()->GetLimit();

	if (hp <= 0){
		Kill();
	}

	if (GameData::Player == nullptr){
		return;
	}

	if(state == EnemyState::HURTING){
		speed.y += 20*dt;
	}

	if(state == EnemyState::IDLE){
		speed.y += 20*dt;
		if (SearchTimer.Get() < 6){
			SearchTimer.Update(dt);
		}
		else{
			SearchTimer.Restart();
			state = EnemyState::SEARCHING;
		}	
	}

	if(state == EnemyState::SEARCHING){
		//SDL_Log("SEARCHING\n");
		speed.y += 20*dt;
		if (SearchTimer.Get() < 3){
			speed.x = 0;
			SearchTimer.Update(dt);
		}
		else{
			SearchTimer.Restart();
			
			Vec2 playerCenter = GameData::Player->GetAssociated()->Box.GetCenter();

			distance = playerCenter - associated->Box.GetCenter();

			if (abs(distance.x) < 300){
				type = AttackType::SMASH;
				SetSprite((Sprite*) associated->GetComponentByTag("EnemySmash"));
				speed.y = -500*dt;
				speed.x = 300*dt;
			}
			else if(distance.y < 0){
				type = AttackType::TONGUEUP;
				SetSprite((Sprite*) associated->GetComponentByTag("EnemyUp"));
				if(abs(distance.x) > 300){
					speed.x = (abs(distance.x) - 300)*dt;
				}
			}
			else{
				type = AttackType::TONGUEDOWN;
				SetSprite((Sprite*) associated->GetComponentByTag("EnemyDown"));
				if(abs(distance.x) > 300){
					speed.x = (abs(distance.x) - 300)*dt;
				}	
			}

			if(distance.x < 0){
				flip = false;
				sprite->SetFlip(flip);
				speed.x *= -1;
				colisor->SetOffset(Vec2(120,55));
			}
			else{
				flip = true;
				sprite->SetFlip(flip);
				colisor->SetOffset(Vec2(-120,55));
			}


			state = EnemyState::ATTACKING;
		}
	}

	if(state == EnemyState::ATTACKING){
		//SDL_Log("ATTACKING\n");
		Attack();
		speed.y += 20*dt;
	}

	if ((colisor->Box.x) < limit.x){
		//state = EnemyState::SEARCHING;
		associated->Box.x = limit.x - abs(colisor->Box.x - associated->Box.x);
	}

	if ((colisor->Box.x + colisor->Box.w) > limit.x + limit.w){
		//state = EnemyState::SEARCHING;
		associated->Box.x = limit.x+limit.w - colisor->Box.w  - abs(colisor->Box.x - associated->Box.x);
	}

	if ((associated->Box.y + associated->Box.h) > limit.y+limit.h){
		Land();
		associated->Box.y = limit.y+limit.h - associated->Box.h;
	}

	associated->Box.x += speed.x;
	associated->Box.y += speed.y;
}
void Frog::Start(){
	Sprite* idle = new Sprite(associated, STAGE1_BOSS_IDLE_ANIMATION, 8, 0.1, 0);
	idle->SetTag("EnemyIdle");
	idle->SetEnabled(true);
	SetSprite(idle);
	associated->AddComponent(idle);

	Sprite* run = new Sprite(associated, STAGE1_BOSS_RUN_ANIMATION, 8, 0.3, 0);
	run->SetTag("EnemyRun");
	run->SetEnabled(false);
	associated->AddComponent(run);

	Sprite* smash = new Sprite(associated, STAGE1_BOSS_SMASH_ATTACK_ANIMATION, 10, 0.1, 0);
	smash->SetTag("EnemySmash");
	smash->SetEnabled(false);
	associated->AddComponent(smash);

	Sprite* baixo = new Sprite(associated, STAGE1_BOSS_DOWN_ATTACK_ANIMATION, 10, 0.1, 0);
	baixo->SetTag("EnemyDown");
	baixo->SetEnabled(false);
	associated->AddComponent(baixo);

	Sprite* alto = new Sprite(associated, STAGE1_BOSS_UP_ATTACK_ANIMATION, 10, 0.1, 0);
	alto->SetTag("EnemyUp");
	alto->SetEnabled(false);
	associated->AddComponent(alto);

}
void Frog::NotifyCollision(GameObject* other){}
void Frog::Attack(){
	if(type == AttackType::SMASH){
		Smash();
	}

	if(type == AttackType::TONGUEUP){
		TongueAttack(true);
	}

	if(type == AttackType::TONGUEDOWN){
		TongueAttack(false);
	}
}

void Frog::TongueAttack(bool updown){
	SDL_Log("TONGUE");
	if (sprite->IsAnimationOver()){
		sprite->SetFrame(0);
		SetSprite((Sprite*) associated->GetComponentByTag("EnemyIdle"));
		state = EnemyState::SEARCHING;
		return;
	}

	if (sprite->GetFrame() == 5){
		Game* game = Game::GetInstance();
		State* state = game->GetCurrentState();

		GameObject* go = new GameObject();
		go->Box.w = 40;
		go->Box.h = 40;

		if (flip){
			go->Box.Centralize(associated->Box.GetCenter().x+ 300, associated->Box.GetCenter().y);

		}
		else{
			go->Box.Centralize(associated->Box.GetCenter().x- 300, associated->Box.GetCenter().y);

		}

		if (updown){
			go->Box.y -= 140;
		}
		else{
			go->Box.y += 140;
		}
		
		Punch* punch = new Punch(go,2, true, 0.1);

		go->AddComponent(punch);

		/*Sound* sound = new Sound(go, STAGE1_BOSS_SMASH_ATTACK_SOUND);
		sound->Play(1);
		go->AddComponent(sound);*/

		state->AddObject(go);

	}

	
}

void Frog::Smash(){
	//SDL_Log("SMASH");

	if (sprite->GetFrame() == 6){
		speed.y = 400;

		Game* game = Game::GetInstance();
		State* state = game->GetCurrentState();

		GameObject* go = new GameObject();
		go->Box.w = 90;
		go->Box.h = 15;
		if (flip){
			go->Box.Centralize(associated->Box.GetCenter().x + 130, colisor->Box.y+colisor->Box.h);

		}
		else{
			go->Box.Centralize(associated->Box.GetCenter().x - 130, colisor->Box.y+colisor->Box.h);

		}
		
		Punch* punch = new Punch(go,2, true, 1.0);

		go->AddComponent(punch);

		/*Sound* sound = new Sound(go, STAGE1_BOSS_TONGUE_ATTACK_SOUND);
		sound->Play(1);
		go->AddComponent(sound);*/

		state->AddObject(go);

	}
	
	if (sprite->IsAnimationOver()){
		sprite->SetFrame(0);
		SetSprite((Sprite*) associated->GetComponentByTag("EnemyIdle"));
		state = EnemyState::SEARCHING;
		return;
	}
}

void Frog::TakeDamage(int dmg){
	if (state == EnemyState::IDLE){
		return;
	}

	hp-=dmg;
	if(hp <= 0){
		Kill();
	}
}

void Frog::Land(){
	speed.y = 0;
	jumpCount = 0;
}
void Frog::Kill(){
	GameData::playerVictory = true;
	associated->RequestDelete();

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	go->Box.x = associated->Box.x;
	go->Box.y = associated->Box.y;
	state->AddObject(go);

	Sprite* death = new Sprite(go, STAGE1_BOSS_DEATH_ANIMATION, 9, 0.1, 0.8);
	death->SetFlip(flip);
	go->AddComponent(death);

	GameObject* go2 = new GameObject();

	Sound* sound = new Sound(go2, WIN_MUSIC);
	sound->Play(1);
	go2->AddComponent(sound);

	state->AddObject(go2);
}