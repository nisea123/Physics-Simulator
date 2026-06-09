#pragma once

#include "Structs.h"

enum ShapeType
{
	SHAPE_TEXT = 0,
	SHAPE_TRIG = 1,
	SHAPE_RECT = 2,
	SHAPE_CIRCLE = 3,
};

struct ShapeInstance
{
	Vec2f position;
	Vec2f size;

	Color color;

	float radius;
	float type;
	float rotation;
};