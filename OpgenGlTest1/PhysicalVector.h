#pragma once

#include "Structs.h"

#include <string>

struct PhysicalVector {
	Vec2f Position;
	bool Visbile = true;

	PhysicalVector(Vec2f pos) : Position(pos) {};
};