#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include "Structs.h"
#include "Transform.h"

class Object
{
public:
	Transform Transform;
	Color Color;
	float ShapeType = 0;

	void OnDrag(Vec2f delta) {
		Transform.Position.x += delta.x;
		Transform.Position.y += delta.y;
	};
	virtual bool Contains(Vec2f p) = 0;
};

class Triangle : public Object
{
public:
	Vec2f Size = { 0.0f, 0.0f };

	Triangle(Vec2f siz, Vec2f pos)
	{
		Size = siz;
		Transform.Position = pos;
		ShapeType = 1;
	};
	bool Contains(Vec2f p) override;
};

class Rectangle : public Object 
{
public:
	Vec2f Size;
	float CornerRadius = 0.f;
	Rectangle() {
	 Size = { 0.0f ,0.0f };
	}
	Rectangle(Vec2f siz, Vec2f pos) 
	{
		Size = siz;
		Transform.Position = pos;
		ShapeType = 2;
	};
	bool Contains(Vec2f p) override;
};

class Circle : public Object
{
public:
	float Radius = 1.f;
	Circle(float rad, Vec2f pos) {
		Radius = rad;
		Transform.Position = pos;
		ShapeType = 3;
	}
	bool Contains(Vec2f p) override;
};

#endif