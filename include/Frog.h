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

	private:
		Timer SearchTimer;
		Vec2 destination;
};

#endif