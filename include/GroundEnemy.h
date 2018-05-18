#ifndef GROUNDENEMY
#define GROUNDENEMY

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "ShitBall.h"
#include "Collider.h"
#include "GameData.h"

class GroundEnemy : public Component{
	public:
		GroundEnemy(GameObject* associated, string file, int frameCount, float frameTime);
		GroundEnemy(GameObject* associated);
		~GroundEnemy();
		void Update(float dt);
		void Render();
		bool Is(string type);
		void Start();
		void NotifyCollision(GameObject* other);
		void SetSprite(Sprite* newSprite);
		void Attack();
		void Land();
		void Kill();

	private:
		typedef enum EnemyState {SEARCHING, ATTACKING};
		EnemyState state;
		int hp;
		Vec2 speed;
		Sprite* sprite = nullptr;
		int jumpCount = 0;
		bool flip;	
};

#endif