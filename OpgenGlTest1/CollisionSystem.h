#pragma once

#include "RigidBody.h"
#include "ObjectCast.h"
#include <functional>

using CollisionFunction = std::function<bool(Object*, Object*, Contact&)>;

class CollisionSystem {
public:
	CollisionFunction collisionFunctions[5][5] = { {nullptr} };

	CollisionSystem() {
		collisionFunctions[static_cast<int>(ObjectType::Rectangle)][static_cast<int>(ObjectType::Rectangle)
		] = 
				[this](Object* a, Object* b, Contact& contact) {
			return CheckContact(As<Rectangle>(a), As<Rectangle>(b), contact);
			};
		collisionFunctions[static_cast<int>(ObjectType::Circle)][static_cast<int>(ObjectType::Rectangle)
		] =
			[this](Object* a, Object* b, Contact& contact) {
			return CheckContact(As<Rectangle>(b), As<Circle>(a), contact);
			};
		collisionFunctions[static_cast<int>(ObjectType::Rectangle)][static_cast<int>(ObjectType::Circle)
		] =
			[this](Object* a, Object* b, Contact& contact) {
			return CheckContact(As<Rectangle>(a), As<Circle>(b), contact);
			};
		collisionFunctions[static_cast<int>(ObjectType::Circle)][static_cast<int>(ObjectType::Circle)
		] =
			[this](Object* a, Object* b, Contact& contact) {
			return CheckContact(As<Circle>(a), As<Circle>(b), contact);
			};
	}
	void DetectCollision(const std::vector<RigidBody*>& rigRegister, std::vector<Contact>& contactRegister);
private:
	bool CheckContact(Rectangle* rectA, Rectangle* rectB,Contact& contact);
	bool CheckContact(Circle* circleA, Circle* circleB, Contact& contact);
	bool CheckContact(Rectangle* rect, Circle* circle, Contact& contact);
};