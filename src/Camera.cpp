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

	Game* game = Game::GetInstance();
	State* state = game->GetCurrentState();
	Rect limit = state->GetLimit();

	speed.x = 0;
	speed.y = 0;


	if (focus != nullptr){
		pos = Vec2(focus->Box.x-512, 0);
		if (pos.x < limit.x){
			pos.x = limit.x;
		}
		if (pos.x > limit.x+limit.w - 1024){
			pos.x = limit.x+limit.w - 1024;
		}
	}
}