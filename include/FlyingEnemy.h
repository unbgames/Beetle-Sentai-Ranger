#ifndef FLYINGENEMY
#define FLYINGENEMY

#include "Enemy.h"
#include "Sprite.h"
#include "Vec2.h"
#include "ShitBall.h"
#include "Collider.h"
#include "GameData.h"
#include "Punch.h"

class FlyingEnemy : public Enemy{
	public:
		FlyingEnemy(GameObject* associated, int HP);
		~FlyingEnemy();
		void Update(float dt);
		void Start();
		void NotifyCollision(GameObject* other);
		void Attack(Vec2 target);
		void Land();
		void Kill();
		static int nEnemy;

	private:
		Timer ShootTimer;
		bool PathBlocked = false;
		weak_ptr<GameObject> Soco;
};

#endif