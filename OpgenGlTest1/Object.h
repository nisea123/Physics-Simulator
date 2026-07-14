#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include "Structs.h"
#include "Transform.h"

class Renderer;

enum class ObjectType
{
	Object = 0,
	Triangle = 1,
	Rectangle = 2,
	Circle = 3,
	Line = 4,
	Arrow = 5,
	Rotation = 6,
};

class Object
{
public:
	Transform Transform;
	Color Color;
	bool Visible = true;
	ObjectType ShapeType = ObjectType::Object;

	void OnDrag(Vec2f delta) {
		Transform.Position.x += delta.x;
		Transform.Position.y += delta.y;
	};
	virtual bool Contains(Vec2f p) = 0;
	virtual void Draw(Renderer& renderer) = 0;
};

class Triangle : public Object
{
public:
	Vec2f Size = { 0.0f, 0.0f };
	static constexpr ObjectType Type = ObjectType::Triangle;

	Triangle(Vec2f siz, Vec2f pos)
	{
		Size = siz;
		Transform.Position = pos;
		ShapeType = Type;
	};
	bool Contains(Vec2f p) override;

	void Draw(Renderer& renderer) override;
};

class Rectangle : public Object 
{
public:
	Vec2f Size;
	float CornerRadius = 0.f;
	static constexpr ObjectType Type = ObjectType::Rectangle;

	Rectangle() {
	 Size = Vec2f(10.0f ,10.0f);
	 Transform.Position = Vec2f(100.f, 100.f);
	 ShapeType = Type;
	}
	Rectangle(Vec2f siz, Vec2f pos) 
	{
		Size = siz;
		Transform.Position = pos;
		ShapeType = Type;
	};
	bool Contains(Vec2f p) override;

	void Draw(Renderer& renderer) override;
};

class Circle : public Object
{
public:
	float Radius = 1.f;
	static constexpr ObjectType Type = ObjectType::Circle;

	Circle(float rad, Vec2f pos) {
		Radius = rad;
		Transform.Position = pos;
		ShapeType = Type;
	}
	bool Contains(Vec2f p) override;

	void Draw(Renderer& renderer) override;
};

class Line : public Object
{
public:
	Vec2f Start = Vec2f(0,0);
	Vec2f End = Vec2f(0,1);
	float Thickness = 5.f;
	static constexpr ObjectType Type = ObjectType::Line;

	Line(Vec2f a, Vec2f b,float thick) {
		Start = a;
		End = b;
		Thickness = thick;
		ShapeType =	Type;
	}
	Line(Vec2f a, Vec2f b) {
		Start = a;
		End = b;
		ShapeType = Type;
	}
	Line() {}
	bool Contains(Vec2f p) override;

	void Draw(Renderer& renderer) override;
};

class Arrow : public Line
{
public:
	float ArrowWidth = 3.f;
	float ArrowHeight = 4.f;
	static constexpr ObjectType Type = ObjectType::Arrow;

	Arrow(Vec2f a, Vec2f b,float thick) : Line(a,b,thick){
		ShapeType = Type;
	}
	Arrow(Vec2f a, Vec2f b) : Line(a, b) {
		ShapeType = Type;
	}
	Arrow() {
		ShapeType = Type;
	}
	bool Contains(Vec2f p) override;

	void Draw(Renderer& renderer) override;
};

class Arc : public Arrow
{
public:
	float Radius = 50.f;
	float num = 50.f;
	float shownPercentage = .8; // how much of the arc to make, 1 is the full circle, .5 is half the circleW

	static constexpr ObjectType Type = ObjectType::Rotation;

	Arc(Vec2f pos) {
		ShapeType = Type;
		Transform.Position = pos;
	};
	Arc() {
		ShapeType = Type;
	}

	bool Contains(Vec2f p) override;

	void Draw(Renderer& renderer) override;
};

#endif