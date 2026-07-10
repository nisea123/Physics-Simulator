#include "Transform.h"
#include <math.h>

Vec2f Transform::Apply(Vec2f point)
{
	float cosR = cosf(Rotation.AsRadians());
	float sinR = sinf(Rotation.AsRadians());

	// Scale
	point.x *= Scale.x;
	point.y *= Scale.y;

	// Rotation
	float x = point.x * cosR - point.y * sinR;
	float y = point.x * sinR + point.y * cosR;

	//Translating
	x += Position.x;
	y += Position.y;

	return { x,y };
}

Vec2f Transform::RotatePoint(Vec2f point, Angle angle) {
	
	float s = sinf(angle.AsRadians());
	float c = cosf(angle.AsRadians());

	return {
		point.x * c - point.y * s,
		point.x * s + point.y * c
	};
}

Vec2f Transform::RotateAroundPivot(Vec2f point, Vec2f pivot, float angle) {
	return { 0,0 };
}