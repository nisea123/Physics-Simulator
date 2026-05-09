#pragma once

#include "Structs.h"

struct Transform
{
	Vec2 Position = { 0.f, 0.f };
	float Rotation = 0.f;
	Vec2 Scale = { 1.f, 1.f };

	Vec2 Apply(Vec2 point);
};