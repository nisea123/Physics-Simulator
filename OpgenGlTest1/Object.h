#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include "Structs.h"
#include "Transform.h"

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
	Vec2 Size = { 0.0f ,0.0f };
	Square(Vec2 siz, Vec2 pos) 
	{
		Size = siz;
		Position = pos;
		AnchorPoint = { Size.x / 2.f, Size.y / 2.f };
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

class Triangle : public Object
{
public:
	Vec2 Size = { 0.0f, 0.0f };
	Triangle(Vec2 siz, Vec2 pos)
	{
		Size = siz;
		Position = pos;
	};
};

#endif
