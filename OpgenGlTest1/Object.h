#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include "Structs.h"
#include "Transform.h"
#include "Renderer.h"

class Object
{
public:
	Vec2 Position = { 0.0f, 0.0f };
	Vec2 AnchorPoint = { 0.0f ,0.0f };
	float Rotation = 0.0f;
	Color Color;
};

class Square : public Object 
{
public:
	Vec2 Size = { 10.0f, 10.0f };
	Square(Vec2 siz, Vec2 pos) 
	{
		Size = siz;
		Position = pos;
	};
};

class Circle : public Object
{
public:
	float Radius = 1;
	Circle(float rad, Vec2 pos) {
		Radius = rad;
		Position = pos;
	}
};

#endif
