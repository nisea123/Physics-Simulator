#pragma once

#include "RigidBody.h"
#include "CollisionSystem.h"

#include <vector>

class PhysicsWorld 
{	
public:
	std::vector<RigidBody*> rigidBodyRegister;
	std::vector<Contact> contactRegister;

	CollisionSystem collisionSyst;

	void Step(float dt);
	void ApplyVectors(float dt);
	void RegisterRigidBody(RigidBody* rigBody) {
		rigidBodyRegister.push_back(rigBody);
	}
	void DisplayArrows(Renderer& renderer);
	void ResolveContact();
	void ClearCalculatedForces();
};

