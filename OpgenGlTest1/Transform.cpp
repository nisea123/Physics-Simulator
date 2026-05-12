#include "Transform.h"
#include <math.h>

Vec2f Transform::Apply(Vec2f p)
{
	float cosR = cos(Rotation);
	float sinR = sin(Rotation);

	// Scale
	p.x *= Scale.x;
	p.y *= Scale.y;

	// Rotation
	float x = p.x * cosR - p.y * sinR;
	float y = p.x * sinR + p.y * cosR;

	//Translating
	x += Position.x;
	y += Position.y;

	return { x,y };
}