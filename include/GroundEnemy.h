#ifndef GROUNDENEMY
#define GROUNDENEMY

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "ShitBall.h"
#include "Collider.h"

class GroundEnemy : public Component{
	public:
		GroundEnemy(GameObject* associated, string file, int frameCount, float frameTime);
		~GroundEnemy();
		void Update(float dt);
		void Render();
		bool Is(string type);
		void Start();
		void NotifyCollision(GameObject* other);

	private:
		int hp;
		Vec2 speed;
		Sprite* sprite;
		int jumpCount = 0;
		bool flip;	
};

#endif