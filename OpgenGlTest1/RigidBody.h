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

	std::vector<Vec2f> Forces;
	Vec2f netForce = { 0,0 };
	Vec2f Acceleration = { 0,0 };
	Vec2f Velocity = { 0,0 };

	RigidBody(Object* obj) : owner(obj) {};
	Vec2f CalculateNetForce() const {
		Vec2f newForce = { 0 };
		for (const Vec2f& force : Forces) {
			newForce += force;
		}
		return newForce;
	};
};