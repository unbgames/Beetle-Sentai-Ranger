#ifndef PROTAGONIST
#define PROTAGONIST

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"

class Protagonist : public Component{
	public:
		Protagonist(GameObject* associated, string file, int frameCount, int frameTime);
		~Protagonist();
		void Update(float dt);
		void Render();
		bool Is(string type);
		void Start();
		void NotifyCollision(GameObject* other);

	private:
		int hp;
		Vec2 speed;
		Sprite* sprite;

};

#endif