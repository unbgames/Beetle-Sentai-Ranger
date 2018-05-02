#ifndef RECT
#define RECT

#include "Vec2.h"

class Rect{
	public:
		Rect();
		Rect(float X, float Y, float W, float H);
		~Rect();
		float x;
		float y;
		float w;
		float h;
		void Centralize(float X, float Y);
		void Centralize(Vec2 vec);
		bool Contains(float X, float Y);
		Vec2 GetCenter();
};

#endif