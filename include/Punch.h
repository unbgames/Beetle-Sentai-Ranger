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
		Punch(GameObject* associated, int damage, bool target = false, float secondsToSelfDestruct = 0);
		~Punch();
		void Update(float dt);
		void Render();
		bool Is(string type);
		int GetDamage();
		void NotifyCollision(GameObject* other);
		void SetHitSound(string sound);

	private:
		float secondsToSelfDestruct;
		int damage;
		float time = 0;
		bool targetsPlayer = false;
		string hitSound;
};

#endif