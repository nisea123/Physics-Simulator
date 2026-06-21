#include <algorithm>

#include "Object.h"

bool Triangle::Contains(Vec2f p)
{
	if (!Visible) return false;
	Vec2f pos = Transform.Position;
	Vec2f size = Size;
	return p.x >= pos.x &&
		p.x <= pos.x + size.x &&
		p.y <= pos.y &&
		p.y >= pos.y - size.y;
}

bool Rectangle::Contains(Vec2f p)
{
	if (!Visible) return false;
	Vec2f half = Size * 0.5f;

	Vec2f min = Transform.Position - half;
	Vec2f max = Transform.Position + half;

	return p.x >= min.x && p.x <= max.x &&
		p.y >= min.y && p.y <= max.y;
}

bool Circle::Contains(Vec2f p)
{
	if (!Visible) return false;
	Vec2f d = { p.x - Transform.Position.x, p.y - Transform.Position.y};
	return (d.x * d.x + d.y * d.y) <= Radius * Radius / 4;
	return false;
}

bool Line::Contains(Vec2f p)
{
	if (!Visible) return false;
	Vec2f ab = End - Start;
	Vec2f ap = p - Start;

	float t = Dot(ap, ab) / Dot(ab, ab);
	t = std::clamp(t, 0.0f, 1.0f);

	Vec2f closest = Start + ab * t;

	return Length(p - closest) <= Thickness * 1.1f;
}

bool Arrow::Contains(Vec2f p) 
{
	if (!Visible) return false;
	return Line::Contains(p);
}