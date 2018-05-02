#include "Vec2.h"
#include "iostream"

Vec2::Vec2(){

}

Vec2::Vec2(int X, int Y){
	x = X;
	y = Y;
}

Vec2::~Vec2(){}

Vec2 Vec2::GetRotated(float angulo){
	return( Vec2( (x*cos(angulo) - y*sin(angulo)) , (y*cos(angulo) + x*sin(angulo))) );
}

Vec2 Vec2::Rotate(float angulo){
	Vec2 rotate = GetRotated(angulo);
	x = rotate.x;
	y = rotate.y;
	return(rotate);
}

Vec2 Vec2::operator+(Vec2 vec){
	Vec2 ret;
	ret.x = this->x + vec.x;
	ret.y = this->y + vec.y;
	return(ret);
}
Vec2 Vec2::operator-(Vec2 vec){
	Vec2 ret;
	ret.x = this->x - vec.x;
	ret.y = this->y - vec.y;
	return(ret);
}

Vec2 Vec2::operator=(Vec2 vec){
	x = vec.x;
	y = vec.y;
	return(*this);
}

Vec2 Vec2::operator*(const float rhs) const {
    return Vec2(x * rhs, y * rhs);
}

float Vec2::GetAngle(Vec2 vec){
	return(atan2((vec.y - y) , (vec.x - x)));
}

float Vec2::GetAngle(float X, float Y){
	return(atan2((Y - y) , (X - x)));
}

float Vec2::Distance(Vec2 vec){
	return( sqrt( pow((x - vec.x),2)+ pow((y - vec.y),2)) );
}