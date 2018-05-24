#ifndef GROUNDENEMY
#define GROUNDENEMY

#include "Enemy.h"
#include "Sprite.h"
#include "Vec2.h"
#include "ShitBall.h"
#include "Collider.h"
#include "GameData.h"
#include "Punch.h"

class GroundEnemy : public Enemy{
	public:
		GroundEnemy(GameObject* associated, int HP);
		~GroundEnemy();
		void Update(float dt);
		void Start();
		void NotifyCollision(GameObject* other);
		void Attack();
		void Land();
		void Kill();
		static int nEnemy;

	private:
		weak_ptr<GameObject> Soco;
};

#endif