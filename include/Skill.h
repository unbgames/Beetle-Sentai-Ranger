#ifndef SKILL
#define SKILL

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include "Text.h"
#include "CameraFollower.h"

class Skill : public Component{
	public:
		Skill(GameObject* associated, float Cooldown, string Activefile, string Cooldownfile);
		~Skill();
		void Update(float dt);
		void Render();
		bool Is(string type);
		void Start();
		bool IsActive();
		bool Use();
		
	private:
		bool Active = true;
		Timer timer;
		int CooldownTime = 0;
		Sprite* Activesprite = nullptr;
		Sprite* Cooldownsprite = nullptr;
		Text* display = nullptr;
};

#endif