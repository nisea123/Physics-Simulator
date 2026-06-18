#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include "Structs.h"
#include "Transform.h"

class Object
{
public:
	Transform Transform;
	Color Color;
	bool Visible = true;
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

class Line : public Object
{
public:
	Vec2f Start = Vec2f(0,0);
	Vec2f End = Vec2f(0,1);
	float Thickness = 5.f;
	Line(Vec2f a, Vec2f b,float thick) {
		Start = a;
		End = b;
		Thickness = thick;
		ShapeType = 4;
	}
	Line(Vec2f a, Vec2f b) {
		Start = a;
		End = b;
		ShapeType = 4;
	}
	Line() {}
	bool Contains(Vec2f p) override;
};

class Arrow : public Line
{
public:
	float ArrowWidth = 3.f;
	float ArrowHeight = 4.f;
	Arrow(Vec2f a, Vec2f b,float thick) : Line(a,b,thick){
		ShapeType = 5;
	}
	Arrow(Vec2f a, Vec2f b) : Line(a, b) {
		ShapeType = 5;
	}
	Arrow() {}
	bool Contains(Vec2f p) override;
};
#endif