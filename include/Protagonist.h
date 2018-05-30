#ifndef PROTAGONIST
#define PROTAGONIST

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "ShitBall.h"
#include "Collider.h"
#include "Timer.h"
#include "Platform.h"
#include "State.h"
#include "HealthBar.h"
#include "Punch.h"
#include "AcidSplash.h"

class Protagonist : public Component{
	public:
		Protagonist(GameObject* associated);
		~Protagonist();
		void Update(float dt);
		void Render();
		bool Is(string type);
		void Start();
		void NotifyCollision(GameObject* other);
		void SetSprite(Sprite* newSprite);
		void ShootShit(float angle);
		void ShootAcid(double angle);
		void Attack();
		void Land();
		void TakeDamage(int dmg);
		void Die();

	private:
		typedef enum PlayerState {FLYING, DASHING, NORMAL, BLOCKING, PUNCHING};
		PlayerState state;
		int hp;
		Vec2 speed;
		Sprite* sprite =nullptr;
		int jumpCount = 0;
		bool flip;
		Timer counter;
		Rect limit;
		HealthBar* HPBar;
		weak_ptr<GameObject> Soco;
		Collider* colisor = nullptr;
};

#endif