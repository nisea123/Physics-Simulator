#include "CollisionSystem.h"
#include "Object.h"
#include "ObjectCast.h"

#include <iostream>

void CollisionSystem::DetectCollision(const std::vector<RigidBody*>& rigRegister, std::vector<Contact>& contactRegister) {
	int rigSize = rigRegister.size();
	//std::cout << rigSize << std::endl;
	bool hasCollision = false;
	for (int i = 0; i < rigSize;i++) {

		if (rigRegister[i]->owner->ShapeType != ObjectType::Rectangle) continue;

		for (int j = i + 1;j < rigSize;j++) {

			if (rigRegister[j]->owner->ShapeType != ObjectType::Rectangle) continue;

			RigidBody* A = rigRegister[i];
			RigidBody* B = rigRegister[j];

			Rectangle* rectA = As<Rectangle>(A->owner);
			Rectangle* rectB = As<Rectangle>(B->owner);

			if (!rectA || !rectB) continue;

			Contact contact;

			bool collision = CheckContact(rectA, rectB, contact);

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