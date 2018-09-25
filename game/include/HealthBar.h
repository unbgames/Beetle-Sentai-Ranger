#ifndef HEALTHBAR
#define HEALTHBAR

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"

class HealthBar : public Component{
	public:
		HealthBar(GameObject* associated, int HP, string file);
		~HealthBar();
		void Update(float dt);
		void Render();
		bool Is(string type);
		void Start();
		int GetHP();
		void AddHP(int amount);
		void SetPosition(Vec2 nova);
		
	private:
		int hp;
		Sprite* sprite;
		Vec2 position;
};

#endif