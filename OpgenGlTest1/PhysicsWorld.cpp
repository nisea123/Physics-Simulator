#include "PhysicsWorld.h"
#include "Renderer.h"

#include <iostream>
#include <algorithm>

void PhysicsWorld::Step(float dt) {

	ClearCalculatedForces();
	collisionSyst.DetectCollision(rigidBodyRegister, contactRegister);
	ResolveContact();
	ApplyVectors(dt);
}

void PhysicsWorld::ApplyVectors(float dt) {
	for (RigidBody* rigBody : rigidBodyRegister) {
		rigBody->netForce = rigBody->CalculateNetForce();

		if (!rigBody->Anchored) {
			rigBody->Acceleration = rigBody->netForce / rigBody->Mass;
			rigBody->Velocity += rigBody->Acceleration * dt;
			rigBody->owner->Transform.Position += rigBody->Velocity * dt;
		}

		//std::cout << "Force: x: " << rigBody->netForce.x << " y : " << rigBody->netForce.y << std::endl;
		//std::cout << "Acceleration: x: " << rigBody->Acceleration.x << " y: " << rigBody->Acceleration.y << std::endl;
		//std::cout << "Velocity: x: " << rigBody->Velocity.x << " y: " << rigBody->Velocity.y << std::endl;
		//std::cout << std::endl;
	}
}

void PhysicsWorld::DisplayArrows(Renderer& renderer) {
	Font& font = renderer.fontManager.GetDefaultFont();
	for (RigidBody* rigBody : rigidBodyRegister) {

		bool display = !rigBody->Anchored;

		if (!display) continue;

		for (auto& [name, force] :rigBody->Forces) {
			ArrowDesc ForceDesc;
			ForceDesc.Color = Color(0.3f, 0.f, 0.5f, 1.f);
			ForceDesc.Start = rigBody->owner->Transform.Position;
			ForceDesc.End = rigBody->owner->Transform.Position + force.Position * 2;

			float forceScale = Length(force.Position);

			ForceDesc.Thickness = std::min(.2f * forceScale, 25.f);
			ForceDesc.ArrowHeight = 5.f;
			ForceDesc.ArrowWidth = 3.f;
			renderer.DrawArrow(ForceDesc);

			TextDesc t(font);
			t.Content = name;
			t.Position = (ForceDesc.Start + ForceDesc.End) / 2.f;
			renderer.DrawText(t);
		}

		ArrowDesc NetForceDesc;
		NetForceDesc.Color = Color(0.6f, 0.2f, 1.f, 1.f);
		NetForceDesc.Start = rigBody->owner->Transform.Position;
		NetForceDesc.End = rigBody->owner->Transform.Position + rigBody->netForce * 2;

		float netScale = Length(rigBody->netForce);

		NetForceDesc.Thickness = std::min(.2f * netScale, 25.f);
		NetForceDesc.ArrowHeight = 5.f;
		NetForceDesc.ArrowWidth = 3.f;
		renderer.DrawArrow(NetForceDesc);

		ArrowDesc AccDesc;
		AccDesc.Color = Color(1.f, 1.f, 0.f, 1.f);
		AccDesc.Start = rigBody->owner->Transform.Position;
		AccDesc.End = rigBody->owner->Transform.Position + rigBody->Acceleration;

		float accScale = Length(rigBody->Acceleration);

		AccDesc.Thickness = std::min(.1f * accScale, 20.f);
		AccDesc.ArrowHeight = 5.f;
		AccDesc.ArrowWidth = 3.f;
		renderer.DrawArrow(AccDesc);

		ArrowDesc VelDesc;
		float vecMulti = 5.f;

		VelDesc.Color = Color(0.f, 1.f, 0.f, 1.f);
		VelDesc.Start = rigBody->owner->Transform.Position;
		VelDesc.End = rigBody->owner->Transform.Position + rigBody->Velocity * vecMulti;
		
		float velScale = Length(rigBody->Velocity);

		VelDesc.Thickness = std::min(.05f * velScale,20.f);
		VelDesc.ArrowHeight = 5.f;
		VelDesc.ArrowWidth = 3.f;
		renderer.DrawArrow(VelDesc);
	}
}

void PhysicsWorld::ResolveContact() {
	for (Contact& contact : contactRegister) {
		if (!contact.BodyA->Anchored && !contact.BodyB->Anchored) contact.penetration *= 0.5f;
		if (!contact.BodyA->Anchored) {
			contact.BodyA->owner->Transform.Position -= contact.normal * contact.penetration;
			if (contact.normal.y == -1) {
				contact.BodyA->Velocity.y = 0;
				contact.BodyA->AddForce("Normal", -contact.BodyA->GetForce("Gravity").Position);
			}
		}
		if (!contact.BodyB->Anchored) {
			contact.BodyB->owner->Transform.Position += contact.normal * contact.penetration;
			if (contact.normal.y == 1) {
				contact.BodyB->Velocity.y = 0;
				contact.BodyB->AddForce("Normal", -contact.BodyB->GetForce("Gravity").Position);
			}
		}
	}
	contactRegister.clear();
}

void PhysicsWorld::ClearCalculatedForces() {
	for (RigidBody* rigBody : rigidBodyRegister) {
		rigBody->RemoveForce("Normal");
	}
}