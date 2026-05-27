#include "Object.h"

bool Triangle::Contains(Vec2f p)
{
	Vec2f pos = Transform.Position;
	Vec2f size = Size;
	return p.x >= pos.x &&
		p.x <= pos.x + size.x &&
		p.y <= pos.y &&
		p.y >= pos.y - size.y;
}

bool Rectangle::Contains(Vec2f p)
{
	Vec2f half = Size * 0.5f;

	Vec2f min = Transform.Position - half;
	Vec2f max = Transform.Position + half;

	return p.x >= min.x && p.x <= max.x &&
		p.y >= min.y && p.y <= max.y;
}

bool Circle::Contains(Vec2f p)
{
	Vec2f d = { p.x - Transform.Position.x, p.y - Transform.Position.y};
	return (d.x * d.x + d.y * d.y) <= Radius * Radius;
	return false;
}