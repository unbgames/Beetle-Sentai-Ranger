#include "Collider.h"

#ifdef DEBUG
#include "Camera.h"
#include "Game.h"

#include <SDL2/SDL.h>
#endif // DEBUG


Collider::Collider(GameObject* associated, Vec2 scale, Vec2 offset) : Component(associated){
	this->scale = scale;
	this->offset = offset;
}
Collider::~Collider(){}
void Collider::Update(float dt){

	box.w = associated->Box.w*scale.x;
	box.h = associated->Box.h*scale.y;

	box.Centralize(associated->Box.GetCenter());

	Vec2 rotated = offset.GetRotated(associated->angleDeg*(PI/180.0));

	box.x += rotated.x;
	box.y += rotated.y;
}
bool Collider::Is(string type){
	return(type == "Collider");
}
void Collider::SetScale(Vec2 scale){
	this->scale = scale;
}
void Collider::SetOffset(Vec2 offset){
	this->offset = offset;
}

void Collider::Render() {
#ifdef DEBUG
	Vec2 center( box.GetCenter() );
	SDL_Point points[5];
	
	Vec2 point = (Vec2(box.x, box.y) - center).Rotate( associated->angleDeg/(180/PI) )+ center+Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y) - center).Rotate( associated->angleDeg/(180/PI) )+ center+Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y + box.h) - center).Rotate( associated->angleDeg/(180/PI) )+ center+Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y + box.h) - center).Rotate( associated->angleDeg/(180/PI) )+ center+Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance()->GetRenderer(), points, 5);
#endif // DEBUG
}