#pragma once

#include "RigidBody.h"

class CollisionSystem {
public:

	void DetectCollision(const std::vector<RigidBody*>& rigRegister, std::vector<Contact>& contactRegister);
private:
	bool CheckContact(Rectangle* rectA, Rectangle* rectB,Contact& contact);
};