#include "CollisionSystem.h"
#include "Object.h"
#include "ObjectCast.h"
#include <algorithm>

#include <iostream>

void CollisionSystem::DetectCollision(const std::vector<RigidBody*>& rigRegister, std::vector<Contact>& contactRegister) {
	int rigSize = rigRegister.size();
	//std::cout << rigSize << std::endl;
	bool hasCollision = false;
	for (int i = 0; i < rigSize;i++) {

		if (rigRegister[i]->owner->ShapeType != ObjectType::Rectangle && rigRegister[i]->owner->ShapeType != ObjectType::Circle) continue;

		for (int j = i + 1;j < rigSize;j++) {

			if (rigRegister[j]->owner->ShapeType != ObjectType::Rectangle && rigRegister[j]->owner->ShapeType != ObjectType::Circle) continue;

			RigidBody* A = rigRegister[i];
			RigidBody* B = rigRegister[j];

			auto func = collisionFunctions[
				static_cast<int>(A->owner->ShapeType)
			][static_cast<int>(B->owner->ShapeType)];

			if (!func) continue;

			Contact contact;

			bool collision = func(A->owner, B->owner, contact);

			if (collision) {

				contact.BodyA = A;
				contact.BodyB = B;

				contactRegister.push_back(contact);
			}
		}
	}
}

bool CollisionSystem::CheckContact(Rectangle* rectA, Rectangle* rectB,Contact& contact) {
	Vec2f topRightA = rectA->Transform.Position + rectA->Size / 2.f;
	Vec2f bottomLeftA = rectA->Transform.Position - rectA->Size / 2.f;

	Vec2f topRightB = rectB->Transform.Position + rectB->Size / 2.f;
	Vec2f bottomLeftB = rectB->Transform.Position - rectB->Size / 2.f;

	bool overlap = false;

	if((topRightA.x > bottomLeftB.x && bottomLeftA.x < topRightB.x) &&
	   (topRightA.y > bottomLeftB.y && bottomLeftA.y < topRightB.y)) overlap = true;

	Vec2f difference = rectB->Transform.Position - rectA->Transform.Position;
	Vec2f overlapVal = (rectA->Size + rectB->Size) / 2.f - abs(difference);

	if (overlapVal.x <= overlapVal.y) {
		contact.normal.x = difference.x > 0 ? 1 : -1;
		contact.normal.y = 0;
	}
	else {
		contact.normal.x = 0;
		contact.normal.y = difference.y > 0 ? 1 : -1;
	}

	contact.penetration = std::min(overlapVal.x, overlapVal.y);
	return contact.penetration > -.001f;
}

bool CollisionSystem::CheckContact(Circle* circleA, Circle* circleB, Contact& contact) {
	Vec2f difference = circleB->Transform.Position - circleA->Transform.Position;
	float distance = Length(difference);
	float radiusSum = circleA->Radius + circleB->Radius;
	if (distance < radiusSum) {
		contact.normal = Normalize(difference);
		contact.penetration = radiusSum - distance;
		return true;
	}
	return false;
}

bool CollisionSystem::CheckContact(Rectangle* rect, Circle* circle, Contact& contact)
{
	Vec2f circlePos = circle->Transform.Position;
	Vec2f rectPos = rect->Transform.Position;

	// Rectangle bounds
	float left = rectPos.x - rect->Size.x / 2.0f;
	float right = rectPos.x + rect->Size.x / 2.0f;
	float bottom = rectPos.y - rect->Size.y / 2.0f;
	float top = rectPos.y + rect->Size.y / 2.0f;

	// Closest point on rectangle to circle
	float closestX = std::clamp(circlePos.x, left, right);
	float closestY = std::clamp(circlePos.y, bottom, top);

	Vec2f difference = circlePos - Vec2f(closestX, closestY);

	float distanceSquared =
		difference.x * difference.x +
		difference.y * difference.y;

	if (distanceSquared < circle->Radius * circle->Radius)
	{
		float distance = sqrt(distanceSquared);

		if (distance != 0)
			contact.normal = difference / distance;
		else
			contact.normal = { 0, 1 }; // circle center inside rectangle

		contact.penetration = circle->Radius - distance;

		return true;
	}

	return false;
}