#include "CameraFollower.h"

CameraFollower::CameraFollower(GameObject* go) : Component(go){
	Offset.x = 0;
	Offset.y = 0;
}
CameraFollower::~CameraFollower(){}
void CameraFollower::Update(float dt){

	associated->Box.x = Camera::pos.x + Offset.x;
	associated->Box.y = Camera::pos.y + Offset.y;
}
void CameraFollower::Render(){}
bool CameraFollower::Is(string type){
	return(type == "CameraFollower");
}

void CameraFollower::SetOffset(Vec2 New){
	Offset.x = New.x;
	Offset.y = New.y;
}