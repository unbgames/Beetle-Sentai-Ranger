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
		void Attack();
		void Land();
		void Kill();
		static int nEnemy;

	private:
		bool PathBlocked = false;
		weak_ptr<GameObject> Soco;
};

#endif