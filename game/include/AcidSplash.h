#ifndef ACIDSPLASH
#define ACIDSPLASH

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Collider.h"
#include "Enemy.h"
#include "Sound.h"

class AcidSplash : public Component{
	public:
		AcidSplash(GameObject* associated, double angle, float speed, int damage, string sprite, int frameCount, bool target = false);
		~AcidSplash();
		void Update(float dt);
		void Render();
		bool Is(string type);
		int GetDamage();
		void NotifyCollision(GameObject* other);
	private:
		typedef enum AcidState {FLYING, STICKING};
		AcidState state;
		Vec2 speed;
		int damage;
		Timer timer;
		bool targetsPlayer = false;
	
};

#endif