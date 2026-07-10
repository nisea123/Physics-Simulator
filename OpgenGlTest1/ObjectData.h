#pragma once

#include "Structs.h"
#include "Object.h"

struct ArrowDesc {
	Vec2f Start;
	Vec2f End;

	float ArrowWidth;
	float ArrowHeight;
	float Thickness;
	Color Color;
};

//ArrowDesc toArrowDesc(const Arrow* object, float newThickness);