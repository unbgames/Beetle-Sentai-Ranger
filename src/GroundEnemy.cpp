#include "GroundEnemy.h"

int GroundEnemy::nEnemy = 0;

GroundEnemy::GroundEnemy(GameObject* associated, int HP) : Enemy(associated, HP){
	colisor->SetScale(Vec2(0.3,0.7));
	colisor->SetOffset(Vec2(0,15));

	AttackTimer.Restart();
}
GroundEnemy::~GroundEnemy(){}

void GroundEnemy::Update(float dt){
	AttackTimer.Update(dt);
	speed.x = 0;

	if (state == EnemyState::IDLE){
		if(GameData::Player == nullptr)
			return;

		Vec2 centro = associated->Box.GetCenter();

		Vec2 centroPlayer = GameData::Player->GetAssociated()->Box.GetCenter();

		Vec2 distance = centro - centroPlayer;

		if (abs(distance.x) > 250){
			int mod = rand()%2;
			if (mod){
				speed.x = 300*dt;
				flip = false;
				sprite->SetFlip(flip);
			}
			else{
				speed.x = -300*dt;
				flip = true;
				sprite->SetFlip(flip);
			}

		}
		else{
			state = EnemyState::SEARCHING;
		}
	}

	if (state == EnemyState::HURTING){
		if (sprite->IsAnimationOver()){
			SetSprite((Sprite*) associated->GetComponentByTag("EnemyIdle"));
			state = EnemyState::SEARCHING;
		}
	}

	if (state == EnemyState::ATTACKING){
		if (sprite->IsAnimationOver()){
			if (sprite->GetTag() != "EnemyJump"){
				SetSprite((Sprite*) associated->GetComponentByTag("EnemyIdle"));	
			}
			state = EnemyState::SEARCHING;
			if(Soco.lock() != nullptr)
				Soco.lock()->RequestDelete();
		}
	}

	if (state == EnemyState::SEARCHING){

		int move = 0;

		InputManager& input = InputManager::GetInstance();

		Vec2 centro = associated->Box.GetCenter();

		if(GameData::Player == nullptr)
			return;

		Vec2 centroPlayer = GameData::Player->GetAssociated()->Box.GetCenter();

		if (centroPlayer.x > centro.x && abs(centroPlayer.x - centro.x) >= 55){
			//andar para a direita
			move = 2;
		}
		else if(abs(centroPlayer.x - centro.x) >= 55){
			//andar para a esquerda
			move = 1;
		}

		if (abs(centroPlayer.x - centro.x) < 60 && AttackTimer.Get() > 1.5){
			//atacar
			AttackTimer.Restart();
			move = 3;

		}
		
		if(input.IsKeyDown(SDLK_q)){
			move = 0;
		}

		if(PathBlocked && jumpCount < 1){
			SetSprite((Sprite*) associated->GetComponentByTag("EnemyJump"));
			jumpCount++;
			speed.y = -450*dt;
			PathBlocked = false;
		}

		if(move == 1){
			if (sprite->GetTag() == "EnemyIdle")
				SetSprite((Sprite*) associated->GetComponentByTag("EnemyRun"));
			speed.x = -300*dt;
			flip = true;
			sprite->SetFlip(flip);
		}
		if(move == 2){
			if (sprite->GetTag() == "EnemyIdle")
				SetSprite((Sprite*) associated->GetComponentByTag("EnemyRun"));
			speed.x = 300*dt;
			flip = false;
			sprite->SetFlip(flip);
		}
		if(move == 3){
			Attack();
		}
	}

	PathBlocked = false;
	/*
	*
	*/
	speed.y += 20*dt;

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
void GroundEnemy::Start(){

	Sprite* idle = new Sprite(associated, STAGE1_GROUND_ENEMY_IDLE_ANIMATION, 5, 0.3, 0);
	idle->SetTag("EnemyIdle");
	idle->SetEnabled(true);
	SetSprite(idle);
	associated->AddComponent(idle);

	Sprite* run = new Sprite(associated, STAGE1_GROUND_ENEMY_RUN_ANIMATION, 6, 0.1, 0);
	run->SetTag("EnemyRun");
	run->SetEnabled(true);
	SetSprite(run);
	associated->AddComponent(run);

	Sprite* punch = new Sprite(associated, STAGE1_GROUND_ENEMY_PUNCH_ANIMATION, 4, 0.1, 0);
	punch->SetTag("EnemyPunch");
	punch->SetEnabled(false);
	associated->AddComponent(punch);

	Sprite* jump = new Sprite(associated, STAGE1_GROUND_ENEMY_JUMP_ANIMATION, 8, 0.1, 0);
	jump->SetTag("EnemyJump");
	jump->SetEnabled(false);
	associated->AddComponent(jump);

	Sprite* hurt = new Sprite(associated, STAGE1_GROUND_ENEMY_GETHURT_ANIMATION, 5, 0.06, 0);
	hurt->SetTag("EnemyHurt");
	hurt->SetEnabled(false);
	associated->AddComponent(hurt);
}
void GroundEnemy::NotifyCollision(GameObject* other){
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

}
void GroundEnemy::Attack(){
	speed.x = 0;
	state = EnemyState::ATTACKING;
	SetSprite((Sprite*) associated->GetComponentByTag("EnemyPunch"));
	sprite->SetFrame(0);

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	go->Box.w = 15;
	go->Box.h = 70;
	if (flip){
		go->Box.Centralize(associated->Box.GetCenter().x- 45, associated->Box.GetCenter().y+10);

	}
	else{
		go->Box.Centralize(associated->Box.GetCenter().x+ 45, associated->Box.GetCenter().y+5);

	}
	
	Punch* punch = new Punch(go,2, true);
	punch->SetHitSound(STAGE1_GROUND_ENEMY_ATTACK_HIT_SOUND);

	go->AddComponent(punch);

	Sound* sound = new Sound(go, STAGE1_GROUND_ENEMY_ATTACK_SOUND);
	sound->Play(1);
	go->AddComponent(sound);

	Soco = state->AddObject(go);
}
void GroundEnemy::Land(){
	speed.y = 0;
	jumpCount = 0;
	if (sprite->GetTag() == "EnemyJump"){
		sprite->SetFrame(0);
		SetSprite((Sprite*) associated->GetComponentByTag("EnemyIdle"));
	}
}

void GroundEnemy::TakeDamage(int dmg){
	hp-=dmg;
	if(hp <= 0){
		Kill();
	}
	SetSprite((Sprite*) associated->GetComponentByTag("EnemyHurt"));
	sprite->SetFrame(0);
	state = EnemyState::HURTING;
}

void GroundEnemy::Kill(){
	associated->RequestDelete();

	if (Soco.lock() != nullptr){
		Soco.lock()->RequestDelete();
	}

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();

	GameObject* go = new GameObject();
	go->Box.x = associated->Box.x;
	go->Box.y = associated->Box.y;
	state->AddObject(go);

	Sprite* sprite = new Sprite(go, STAGE1_GROUND_ENEMY_DEATH_ANIMATION,12,0.1,1.2);
	go->AddComponent(sprite);

	Sound* sound = new Sound(go, STAGE1_GROUND_ENEMY_DEATH_SOUND);
	sound->Play(1);
	go->AddComponent(sound);

	if (GroundEnemy::nEnemy > 0)
		GroundEnemy::nEnemy--;
}