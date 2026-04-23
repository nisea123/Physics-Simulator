#pragma once

#include "Structs.h"

enum class ShapeType
{
	Rectangle,
	Circle
};

struct Renderer
{
	ShapeType shape;

	float width  = 1.0f;
	float height = 1.0f;
	float radius = 1.0f;

	

};