#pragma once

#include "RigidBody.h"
#include <vector>

class PhysicsWorld 
{	
public:
	std::vector<RigidBody*> rigidBodyRegister;

	void Step(float dt);
	void ApplyVectors(float dt);
	void RegisterRigidBody(RigidBody* rigBody) {
		rigidBodyRegister.push_back(rigBody);
	}
};

