#pragma once

#include "Structs.h"

struct Camera {
	Vec2f position = Vec2f(0.f, 0.f);
	Vec2f lastPosition = Vec2f(0.f, 0.f);
	Vec2f zoom = Vec2f(1.f, 1.f);
};