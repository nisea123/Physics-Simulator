#pragma once

#include "Structs.h"

struct Transform
{
	Vec2f Position = { 0.0f, 0.0f };
	Angle Rotation = Angle::Degrees(0);
	Vec2f Scale = { 1.f, 1.f };

	Vec2f Apply(Vec2f point);
	Vec2f RotatePoint(Vec2f point, Angle angle);
	Vec2f RotateAroundPivot(Vec2f point, Vec2f pivot, float angle);
};