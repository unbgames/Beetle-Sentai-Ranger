#ifndef PUNCH
#define PUNCH

#include "Component.h"
#include "GameObject.h"
#include "Rect.h"
#include "Collider.h"
#include "Enemy.h"
#include "Protagonist.h"

class Punch : public Component{
	public:
		Punch(GameObject* associated, int damage, bool target = false);
		~Punch();
		void Update(float dt);
		void Render();
		bool Is(string type);
		int GetDamage();
		void NotifyCollision(GameObject* other);

	private:
		int damage;
		bool targetsPlayer = false;
};

#endif