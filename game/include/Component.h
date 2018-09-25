#ifndef COMPONENT
#define COMPONENT

#define INCLUDE_SDL
#include "SDL_include.h"
#include <string>

using namespace std;

class GameObject;

class Component{
	public:
		Component(GameObject* associated);
		virtual ~Component();
		void virtual Update(float dt) = 0;
		void virtual Render() = 0;
		bool virtual Is(string type) = 0;
		void virtual Start();
		void virtual NotifyCollision(GameObject* other);
		GameObject* GetAssociated();
		bool IsEnabled();
		void SetEnabled(bool enable);
		string GetTag();
		void SetTag(string tag);

	protected:
		GameObject* associated;
		bool enabled = true;
		string tag;
};

#endif