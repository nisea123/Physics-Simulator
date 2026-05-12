#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include "Structs.h"
#include "Transform.h"

struct Border
{
	float Thickness = 0.02f;
	Color Color = { 0.f,0.f,0.f,0.f };
};

class Object
{
public:
	Transform Transform;
	Color Color;
	Border Border;
	int ShapeType;
};

class Triangle : public Object
{
public:
	Vec2f Size = { 0.0f, 0.0f };

	Triangle(Vec2f siz, Vec2f pos)
	{
		Size = siz;
		Transform.Position = pos;
		ShapeType = 0;
	};
};


class Rectangle : public Object 
{
public:
	Vec2f Size;
	Rectangle() {
	 Size = { 0.0f ,0.0f };
	}
	Rectangle(Vec2f siz, Vec2f pos) 
	{
		Size = siz;
		Transform.Position = pos;
		ShapeType = 1;
		//AnchorPoint = { Size.x / 2.f, Size.y / 2.f };
	};
};

class Circle : public Object
{
public:
	float Radius = 1;
	Circle(float rad, Vec2f pos) {
		Radius = rad;
		Transform.Position = pos;
		ShapeType = 2;
	}
};
#endif
