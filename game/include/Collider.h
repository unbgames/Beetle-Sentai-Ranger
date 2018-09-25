#ifndef COLLIDER
#define COLLIDER

#include "Component.h"
#include "Sprite.h"
#include "Rect.h"
#include <memory>
#include "InputManager.h"

class Collider : public Component{
	public:
		Collider(GameObject* associated, Vec2 scale = Vec2(1,1), Vec2 offset = Vec2(0,0));
		~Collider();
		Rect Box;
		void Update(float dt);
		void Render();
		bool Is(string type);
		void SetScale(Vec2 scale);
		void SetOffset(Vec2 offset);

	private:
		Vec2 scale;
		Vec2 offset;
		
};

#endif