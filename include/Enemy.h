#ifndef ENEMY
#define ENEMY

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "ShitBall.h"
#include "Collider.h"
#include "GameData.h"

class Enemy : public Component{
	public:
		Enemy(GameObject* associated, int HP);
		~Enemy();
		void Update(float dt);
		void Render();
		bool Is(string type);
		void Start();
		void NotifyCollision(GameObject* other);
		void SetSprite(Sprite* newSprite);
		void Attack();
		void Land();
		void Kill();

	protected:
		typedef enum EnemyState {SEARCHING, ATTACKING};
		EnemyState state;
		int hp;
		Vec2 speed;
		Sprite* sprite = nullptr;
		int jumpCount = 0;
		bool flip;
};

#endif