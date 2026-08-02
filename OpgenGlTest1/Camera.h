#pragma once

#include "Structs.h"

class Camera {
public:

	Vec2f position = Vec2f(0.f, 0.f);
	Vec2f lastPosition = Vec2f(0.f, 0.f);
	Vec2f zoom = Vec2f(1.f, 1.f);

	Vec2f ScreenToWorld(Vec2f screenPos, Vec2f screenSize) {
		Vec2f worldPos = (screenPos - (screenSize * 0.5f)) / zoom + position;
		return worldPos;
	}
};