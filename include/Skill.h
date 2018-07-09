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
		bool IsOnCooldown();
		bool Use();
		void SetDuration(float val);
		void SetColor(int R, int G, int B, int alpha);
		
	private:
		typedef enum SkillState {ACTIVE, COOLDOWN, RUNNING};
		SkillState state;
		Timer timer;
		float CooldownTime = 0;
		float duration = -1;
		Sprite* Activesprite = nullptr;
		Sprite* Cooldownsprite = nullptr;
		Text* display = nullptr;
};

#endif