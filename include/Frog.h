#ifndef FROG
#define FROG

#include "Enemy.h"
#include "Timer.h"
#include "Protagonist.h"
#include "BossStage1.h"

class Frog : public Enemy{
	
	public:
		Frog(GameObject* associated, int HP);
		~Frog();
		void Update(float dt);
		void Start();
		void NotifyCollision(GameObject* other);
		void Attack();
		void Land();
		void Kill();
		void SetSprite(Sprite* newSprite);
		void TongueAttack(bool updown);
		void Smash();
		void TakeDamage(int dmg);

	private:
		typedef enum AttackType {SMASH, TONGUEUP, TONGUEDOWN};
		AttackType type;
		Timer SearchTimer;
		Vec2 distance;
};

#endif