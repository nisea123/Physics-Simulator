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

		if (!(rigBody->Anchored || rigBody->owner->Selected)) {
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

		bool display = !(rigBody->Anchored || rigBody->owner->Selected);

		if (!display) continue;

		for (auto& [name, force] :rigBody->Forces) {

			float forceScale = Length(force.Position);
			float forceLength = logf(1.0f + forceScale) / logf(1.05f);

			Vec2f forceDirection = Normalize(force.Position);
			
			ArrowDesc ForceDesc;
			ForceDesc.Color = Color(0.3f, 0.f, 0.5f, 1.f);
			ForceDesc.Start = rigBody->owner->Transform.Position;
			ForceDesc.End = ForceDesc.Start + forceDirection * forceLength;

			ForceDesc.Thickness = std::min(.1f * forceScale, 10.f);
			renderer.DrawArrow(ForceDesc);

			TextDesc t(font);
			t.Content = name;
			t.Position = (ForceDesc.Start + ForceDesc.End) / 2.f;
			renderer.DrawText(t);
		}


		float netScale = Length(rigBody->netForce);
		float netLength = logf(1.0f + netScale) / logf(1.05f);

		Vec2f forceDirection = Normalize(rigBody->netForce);

		ArrowDesc NetForceDesc;
		NetForceDesc.Color = Color(0.6f, 0.2f, 1.f, 1.f);
		NetForceDesc.Start = rigBody->owner->Transform.Position;
		NetForceDesc.End = NetForceDesc.Start + forceDirection * netLength;

		NetForceDesc.Thickness = std::min(.01f * netScale, 25.f);
		renderer.DrawArrow(NetForceDesc);
	
		float accScale = Length(rigBody->Acceleration);
		float accLength = logf(1.0f + accScale) / logf(1.1f);

		Vec2f accDirection = Normalize(rigBody->Acceleration);

		ArrowDesc AccDesc;
		AccDesc.Color = Color(1.f, 1.f, 0.f, 1.f);
		AccDesc.Start = rigBody->owner->Transform.Position;
		AccDesc.End = AccDesc.Start + accDirection * accLength;;

		AccDesc.Thickness = std::min(.01f * accScale, 20.f);
		renderer.DrawArrow(AccDesc);

		float velScale = Length(rigBody->Velocity);
		float velLength = logf(1.0f + velScale) / logf(1.05f);

		Vec2f velDirection = Normalize(rigBody->Velocity);

		ArrowDesc VelDesc;
		float vecMulti = 5.f;

		VelDesc.Color = Color(0.f, 1.f, 0.f, 1.f);
		VelDesc.Start = rigBody->owner->Transform.Position;
		VelDesc.End = VelDesc.Start + velDirection * velLength;

		VelDesc.Thickness = std::min(.01f * velScale,20.f);
		renderer.DrawArrow(VelDesc);
	}
}

void PhysicsWorld::ResolveContact() {
	float u = .2f;
	float speedMulti = .5f;
	for (Contact& contact : contactRegister) {
		if (!contact.BodyA->Anchored && !contact.BodyB->Anchored) contact.penetration *= 0.5f;
		if (!contact.BodyA->Anchored) {
			if (contact.BodyA->Velocity.y != 0) {
				contact.BodyA->Velocity.y = -contact.BodyA->Velocity.y * speedMulti;
			}
			contact.BodyA->owner->Transform.Position -= contact.normal * contact.penetration;
			if (contact.normal.y == -1) {
				
				contact.BodyA->AddForce("Normal", -contact.BodyA->GetForce("Gravity").Position);

				if (contact.BodyA->Velocity.x > 0.01f || contact.BodyB->Velocity.x < -0.01f) {
					float fricDirection = contact.BodyA->Velocity.x > 0 ? -1.f: 1.f;
					Vec2f friction = Vec2f(contact.BodyA->GetForce("Normal").Position.y * u * fricDirection, 0.f);
					contact.BodyA->AddForce("Friction", friction);
				}
			}
		}
		if (!contact.BodyB->Anchored) {
			contact.BodyB->owner->Transform.Position += contact.normal * contact.penetration;
			if (contact.BodyB->Velocity.y != 0) {
				contact.BodyB->Velocity.y = -contact.BodyB->Velocity.y * speedMulti;
			}
			if (contact.normal.y == 1) {
				
				contact.BodyB->AddForce("Normal", -contact.BodyB->GetForce("Gravity").Position);
				if (contact.BodyB->Velocity.x > 0.01f || contact.BodyB->Velocity.x < -0.01f) {
					float fricDirection = contact.BodyB->Velocity.x > 0 ? -1.f : 1.f;
					Vec2f friction = Vec2f(contact.BodyB->GetForce("Normal").Position.y * u * fricDirection, 0.f);
					contact.BodyB->AddForce("Friction", friction);
				}
			}
		}
	}
	contactRegister.clear();
}

void PhysicsWorld::ClearCalculatedForces() {
	for (RigidBody* rigBody : rigidBodyRegister) {
		rigBody->RemoveForce("Normal");
		rigBody->RemoveForce("Friction");
	}
}