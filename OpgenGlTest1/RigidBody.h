#pragma once

#include <vector>

#include "Structs.h"
#include "Object.h"

class Object;

class RigidBody 
{		
public:
	Object* owner = nullptr;

	float Mass = 1.f;

	Vec2f Forces;
	Vec2f Velocity;
	Vec2f Acceleration;

	RigidBody(Object* obj) : owner(obj) {};
};