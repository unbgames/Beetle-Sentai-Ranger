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
		virtual void Update(float dt);
		virtual void Render();
		bool Is(string type);
		virtual void Start();
		virtual void NotifyCollision(GameObject* other);
		virtual void SetSprite(Sprite* newSprite);
		virtual void Attack();
		virtual void Land();
		virtual void Kill();
		virtual void TakeDamage(int dmg);

	protected:
		typedef enum EnemyState {SEARCHING, ATTACKING};
		EnemyState state;
		int hp;
		Vec2 speed;
		Sprite* sprite = nullptr;
		int jumpCount = 0;
		bool flip;
		Collider* colisor = nullptr;
		Vec2 scaleAnimations;
};

#endif