#ifndef FROG
#define FROG

#include "Enemy.h"

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
};

#endif