#include "PhysicsWorld.h"
#include <iostream>

void PhysicsWorld::Step(float dt) {
	ApplyVectors(dt);
}

void PhysicsWorld::ApplyVectors(float dt) {
	for (RigidBody* rigBody : rigidBodyRegister) {
		rigBody->Acceleration = rigBody->Forces / rigBody->Mass;
		rigBody->Velocity += rigBody->Acceleration * dt;
		rigBody->owner->Transform.Position += rigBody->Velocity * dt;
		std::cout << "Force: x: " << rigBody->Forces.x << " y : " << rigBody->Forces.y << std::endl;
		std::cout << "Acceleration: x: " << rigBody->Acceleration.x << " y: " << rigBody->Acceleration.y << std::endl;
		std::cout << "Velocity: x: " << rigBody->Velocity.x << " y: " << rigBody->Velocity.y << std::endl;
		std::cout << std::endl;
	}
}