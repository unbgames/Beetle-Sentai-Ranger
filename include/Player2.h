#ifndef PLAYER2
#define PLAYER2

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "ShitBall.h"
#include "Collider.h"
#include "Timer.h"
#include "Platform.h"
#include "Column.h"
#include "Terrain.h"
#include "State.h"
#include "HealthBar.h"
#include "Punch.h"
#include "AcidSplash.h"
#include "Skill.h"

class Player2 : public Enemy{
	public:
		Player2(GameObject* associated);
		~Player2();
		void Update(float dt);
		void Render();
		void Start();
		void NotifyCollision(GameObject* other);

		void TakeDamage(int dmg);
		void Die();

	private:
		typedef enum PlayerState {FLYING, DASHING, NORMAL, HURTING, PUNCHING};
		PlayerState state;
		PlayerState LastState;
		int hp;
		Vec2 speed;
		Sprite* sprite = nullptr;
		int jumpCount = 0;
		bool flip = false;
		bool OnGround = false;
		Timer counter;
		Rect limit;
		HealthBar* HPBar;
		weak_ptr<GameObject> Soco;
		Skill* shit = nullptr;
		Skill* dash = nullptr;
		Skill* fly = nullptr;
		Skill* acid = nullptr;
		Sound* flySound = nullptr;

		void ChangeState(PlayerState next);
		void SetSprite(Sprite* newSprite);
		void ShootShit(float angle);
		void ShootAcid(double angle);
		void Attack();
		void Land();
};

#endif
