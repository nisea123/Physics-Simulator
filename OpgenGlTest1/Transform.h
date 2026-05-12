#pragma once

#include "Structs.h"

struct Transform
{
	Vec2f Position = { 0.0f, 0.0f };
	float Rotation = 0.f;
	Vec2f Scale = { 1.f, 1.f };

	Vec2f Apply(Vec2f point);
};