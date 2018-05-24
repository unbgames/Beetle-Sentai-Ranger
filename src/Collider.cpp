#include "Collider.h"

#define DEBUG
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

	Box.w = associated->Box.w*scale.x;
	Box.h = associated->Box.h*scale.y;

	Box.Centralize(associated->Box.GetCenter());

	Vec2 rotated = offset.GetRotated(associated->angleDeg*(PI/180.0));

	Box.x += rotated.x;
	Box.y += rotated.y;
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
	Vec2 center( Box.GetCenter() );
	SDL_Point points[5];
	
	Vec2 point = (Vec2(Box.x, Box.y) - center).Rotate( associated->angleDeg/(180/PI) )+ center-Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(Box.x + Box.w, Box.y) - center).Rotate( associated->angleDeg/(180/PI) )+ center-Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(Box.x + Box.w, Box.y + Box.h) - center).Rotate( associated->angleDeg/(180/PI) )+ center-Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(Box.x, Box.y + Box.h) - center).Rotate( associated->angleDeg/(180/PI) )+ center-Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance()->GetRenderer(), points, 5);
#endif // DEBUG
}