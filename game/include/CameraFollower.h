#ifndef CAMERAFOLLOWER
#define CAMERAFOLLOWER

#include "Component.h"
#include "Camera.h"
#include "Vec2.h"

class CameraFollower : public Component{
	public:
		
		CameraFollower(GameObject* go);
		~CameraFollower();
		void Update(float dt);
		void Render();
		bool Is(string type);
		void SetOffset(Vec2 New);

	private:
		Vec2 Offset;
};

#endif