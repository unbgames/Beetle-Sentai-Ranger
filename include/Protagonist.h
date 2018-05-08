#ifndef PROTAGONIST
#define PROTAGONIST

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "ShitBall.h"
#include "Collider.h"

class Protagonist : public Component{
	public:
		Protagonist(GameObject* associated, string file, int frameCount, float frameTime);
		Protagonist(GameObject* associated);
		~Protagonist();
		void Update(float dt);
		void Render();
		bool Is(string type);
		void Start();
		void NotifyCollision(GameObject* other);
		void ShootShit(float angle);
		void SetSprite(Sprite* newSprite);

	private:
		int hp;
		Vec2 speed;
		Sprite* sprite;
		int jumpCount = 0;
		bool flip;

};

#endif