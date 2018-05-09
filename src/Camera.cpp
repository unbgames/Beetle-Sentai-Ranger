#include "Camera.h"

Vec2 Camera::pos(0,0);
Vec2 Camera::speed;
GameObject* Camera::focus = nullptr;

Camera::Camera(){}
Camera::~Camera(){}
void Camera::Follow(GameObject* newFocus){
	focus = newFocus;
}
void Camera::Unfollow(){
	focus = nullptr;
}
void Camera::Update(float dt){

	InputManager& input = InputManager::GetInstance();

	speed.x = 0;
	speed.y = 0;

	dt = dt*50;

	if (focus != nullptr){
		pos = Vec2(focus->Box.x-512, 0);
		if (pos.x < 0){
			pos.x = 0;
		}
		if (pos.x > 4976){
			pos.x = 4976;
		}
	}
}