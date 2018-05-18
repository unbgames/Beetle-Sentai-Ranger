#ifndef PROTAGONIST
#define PROTAGONIST

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "ShitBall.h"
#include "Collider.h"
#include "Timer.h"
#include "Platform.h"
#include "State.h"
#include <HealthBar.h>

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
		void SetSprite(Sprite* newSprite);
		void ShootShit(float angle);
		void Punch();
		void Land();

	private:
		typedef enum PlayerState {FLYING, DASHING, NORMAL, BLOCKING, PUNCHING};
		PlayerState state;
		int hp;
		Vec2 speed;
		Sprite* sprite =nullptr;
		int jumpCount = 0;
		bool flip;
		Timer counter;
		Rect limit;
		weak_ptr<GameObject> HPBar;
};

#endif