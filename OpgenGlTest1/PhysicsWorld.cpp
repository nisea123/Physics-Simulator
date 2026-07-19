#include "PhysicsWorld.h"
#include "Renderer.h"

#include <iostream>
#include <algorithm>

void PhysicsWorld::Step(float dt) {
	ApplyVectors(dt);
}

void PhysicsWorld::ApplyVectors(float dt) {
	for (RigidBody* rigBody : rigidBodyRegister) {
		rigBody->netForce = rigBody->CalculateNetForce();
		rigBody->Acceleration = rigBody->netForce / rigBody->Mass;
		rigBody->Velocity += rigBody->Acceleration * dt;
		rigBody->owner->Transform.Position += rigBody->Velocity * dt;

		//std::cout << "Force: x: " << rigBody->netForce.x << " y : " << rigBody->netForce.y << std::endl;
		//std::cout << "Acceleration: x: " << rigBody->Acceleration.x << " y: " << rigBody->Acceleration.y << std::endl;
		//std::cout << "Velocity: x: " << rigBody->Velocity.x << " y: " << rigBody->Velocity.y << std::endl;
		//std::cout << std::endl;
	}
}

void PhysicsWorld::DisplayArrows(Renderer& renderer) {
	for (RigidBody* rigBody : rigidBodyRegister) {
		for (Vec2f force : rigBody->Forces) {
			ArrowDesc ForceDesc;
			ForceDesc.Color = Color(0.3f, 0.f, 0.5f, 1.f);
			ForceDesc.Start = rigBody->owner->Transform.Position;
			ForceDesc.End = rigBody->owner->Transform.Position + force * 10.f;
			float forceScale = Length(force);

			ForceDesc.Thickness = std::min(.8f * forceScale, 25.f);
			ForceDesc.ArrowHeight = 5.f;
			ForceDesc.ArrowWidth = 3.f;
			renderer.DrawArrow(ForceDesc);
		}

		ArrowDesc NetForceDesc;
		NetForceDesc.Color = Color(0.6f, 0.2f, 1.f, 1.f);
		NetForceDesc.Start = rigBody->owner->Transform.Position;
		NetForceDesc.End = rigBody->owner->Transform.Position + rigBody->netForce * 10.f;
		float netScale = Length(rigBody->netForce);

		NetForceDesc.Thickness = std::min(1.f * netScale, 25.f);
		NetForceDesc.ArrowHeight = 5.f;
		NetForceDesc.ArrowWidth = 3.f;
		renderer.DrawArrow(NetForceDesc);

		ArrowDesc AccDesc;
		AccDesc.Color = Color(1.f, 1.f, 0.f, 1.f);
		AccDesc.Start = rigBody->owner->Transform.Position;
		AccDesc.End = rigBody->owner->Transform.Position + rigBody->Acceleration* 12.f;
		float accScale = Length(rigBody->Acceleration);

		AccDesc.Thickness = std::min(.5f * accScale, 20.f);
		AccDesc.ArrowHeight = 5.f;
		AccDesc.ArrowWidth = 3.f;
		renderer.DrawArrow(AccDesc);

		ArrowDesc VelDesc;
		float vecMulti = 5.f;
		VelDesc.Color = Color(0.f, 1.f, 0.f, 1.f);
		VelDesc.Start = rigBody->owner->Transform.Position;
		VelDesc.End = rigBody->owner->Transform.Position + rigBody->Velocity * vecMulti;
		
		float velScale = Length(rigBody->Velocity);

		VelDesc.Thickness = std::min(.2f * velScale,20.f);
		VelDesc.ArrowHeight = 5.f;
		VelDesc.ArrowWidth = 3.f;
		renderer.DrawArrow(VelDesc);
	}
}