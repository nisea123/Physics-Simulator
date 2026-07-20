#pragma once

#include <unordered_map>

#include "Object.h"
#include "PhysicalVector.h"

class Object;

class RigidBody 
{		
public:
	Object* owner = nullptr;
	
	float Mass = 1.f;

	std::unordered_map<std::string,PhysicalVector> Forces;
	Vec2f netForce = { 0,0 };
	Vec2f Acceleration = { 0,0 };
	Vec2f Velocity = { 0,0 };

	RigidBody(Object* obj) : owner(obj) {};
	Vec2f CalculateNetForce() const {
		Vec2f newForce = { 0 };
		for (auto [name, force]:Forces) {
			newForce += force.Position;
		}
		return newForce;
	};
	void AddForce(std::string name,Vec2f position) {
		Forces.emplace(name,PhysicalVector(position));
	}
	void RemoveForce(std::string name) {
		if (Forces.contains(name)) {
			Forces.erase(name);
		}
	}
};