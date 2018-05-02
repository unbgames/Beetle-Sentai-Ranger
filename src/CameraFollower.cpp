#include "CameraFollower.h"

CameraFollower::CameraFollower(GameObject* go) : Component(go){}
CameraFollower::~CameraFollower(){}
void CameraFollower::Update(float dt){
	associated->Box.x = -Camera::pos.x;
	associated->Box.y = -Camera::pos.y;
}
void CameraFollower::Render(){}
bool CameraFollower::Is(string type){
	return(type == "CameraFollower");
}