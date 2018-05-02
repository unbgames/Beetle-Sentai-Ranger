#ifndef CAMERAFOLLOWER
#define CAMERAFOLLOWER

#include "Component.h"
#include "Camera.h"

class CameraFollower : public Component{
	public:
		
		CameraFollower(GameObject* go);
		~CameraFollower();
		void Update(float dt);
		void Render();
		bool Is(string type);
};

#endif