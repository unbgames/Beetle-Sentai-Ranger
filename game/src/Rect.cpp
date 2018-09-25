#include "Rect.h"

Rect::Rect(){
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}
Rect::Rect(float X, float Y, float W, float H){
	x = X;
	y = Y;
	w = W;
	h = H;
}
Rect::~Rect(){}

bool Rect::Contains(float X, float Y){
	return((X > x) && (X < x+w) && (Y > y) && (Y < y+h));
}
void Rect::Centralize(float X, float Y){
	x = X - (w/2);
	y = Y - (h/2);
}
void Rect::Centralize(Vec2 vec){
	x = vec.x - (w/2);
	y = vec.y - (h/2);
}
Vec2 Rect::GetCenter(){
	return(Vec2((x + w/2),(y + h/2)));
}

Rect Rect::operator=(Rect rec){
	x = rec.x;
	y = rec.y;
	w = rec.w;
	h = rec.h;
	return(*this);
}