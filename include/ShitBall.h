#ifndef SHITBALL
#define SHITBALL

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Collider.h"

class ShitBall : public Component{
	public:
		ShitBall(GameObject* associated, double angle, float speed, int damage, string sprite, int frameCount);
		~ShitBall();
		void Update(float dt);
		void Render();
		bool Is(string type);
		int GetDamage();
		void NotifyCollision(GameObject* other);
	private:
		Vec2 speed;
		int damage;
	
};

#endif