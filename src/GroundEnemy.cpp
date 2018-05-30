#include "GroundEnemy.h"

int GroundEnemy::nEnemy = 0;

GroundEnemy::GroundEnemy(GameObject* associated, int HP) : Enemy(associated, HP){
	colisor->SetScale(Vec2(0.3,0.7));
	colisor->SetOffset(Vec2(0,15));
}
GroundEnemy::~GroundEnemy(){}

void GroundEnemy::Update(float dt){
	speed.x = 0;

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

		if (centroPlayer.x > centro.x){
			//andar para a direita
			move = 2;
		}
		else{
			//andar para a esquerda
			move = 1;
		}

		if (centroPlayer.Distance(centro) < 60){
			//atacar
			move = 3;
		}

		if (PathBlocked){
			//pular
			move = 0;
		}

		if(input.IsKeyDown(SDLK_q)){
			move = 4;
		}

		if(move == 0 && jumpCount < 1){
			SetSprite((Sprite*) associated->GetComponentByTag("EnemyJump"));
			jumpCount++;
			speed.y = -450*dt;
		}

		if(move == 1){
			speed.x = -300*dt;
			flip = true;
			sprite->SetFlip(flip);
		}
		if(move == 2){
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

	Sprite* punch = new Sprite(associated, STAGE1_GROUND_ENEMY_PUNCH_ANIMATION, 4, 0.1, 0);
	punch->SetTag("EnemyPunch");
	punch->SetEnabled(false);
	associated->AddComponent(punch);

	Sprite* jump= new Sprite(associated, STAGE1_GROUND_ENEMY_JUMP_ANIMATION, 8, 0.1, 0);
	jump->SetTag("EnemyJump");
	jump->SetEnabled(false);
	associated->AddComponent(jump);
}
void GroundEnemy::NotifyCollision(GameObject* other){
	Platform* base = (Platform*) other->GetComponent("Platform");
	if (base != nullptr){
		PathBlocked = true;

		Vec2 aux = base->GetAssociated()->Box.GetCenter();
		Vec2 aux2 = colisor->Box.GetCenter();

		/*if ((colisor->Box.y + colisor->Box.h) >= base->GetAssociated()->Box.y && (colisor->Box.y + colisor->Box.h) <= (base->GetAssociated()->Box.y + (base->GetAssociated()->Box.h/2))){
			colisor->Box.y = base->GetAssociated()->Box.y - colisor->Box.h;*/

		//Caso a plataforma esteja abaixo
		if (aux.y > aux2.y){
			SDL_Log("chegou aqui");
			colisor->Box.y = base->GetAssociated()->Box.y - colisor->Box.h;
			Land();
		}

		//Caso a plataforma esteja a direita
		else if (aux.x > aux2.x){
			colisor->Box.x = base->GetAssociated()->Box.x - colisor->Box.w;
		}

		//Caso a plataforma esteja a esquerda
		else if (aux.x < aux2.x){
			colisor->Box.x = base->GetAssociated()->Box.x + base->GetAssociated()->Box.w;
		}

		//Caso a plataforma esteja acima
		else if (aux.y < aux2.y){
			SDL_Log("chegou aqui4");
			colisor->Box.y = base->GetAssociated()->Box.y + base->GetAssociated()->Box.h;
			speed.y = 0;
		}
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

	if (GroundEnemy::nEnemy > 0)
		GroundEnemy::nEnemy--;
}