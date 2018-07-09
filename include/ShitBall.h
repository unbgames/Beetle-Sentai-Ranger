#ifndef SHITBALL
#define SHITBALL

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Collider.h"
#include "Enemy.h"
#include "Protagonist.h"

class ShitBall : public Component{
	public:
		ShitBall(GameObject* associated, double angle, float speed, int damage, bool targetPlayer, string sprite, string sound,  int frameCount);
		~ShitBall();
		void Update(float dt);
		void Render();
		bool Is(string type);
		int GetDamage();
		void NotifyCollision(GameObject* other);
	private:
		bool targetPlayer = false;
		Vec2 speed;
		int damage;
	
};

#endif