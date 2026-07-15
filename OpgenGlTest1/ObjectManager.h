#pragma once

#include <vector>
#include <memory>

#include "Object.h"
#include "Ui.h"

class ObjectManager {
public:
	std::vector<std::unique_ptr<Object>> objects;
	std::function<RigidBody* (Object*)> assignRigidBody;

	ObjectManager(std::function<RigidBody* (Object*)> rigidFunc) : assignRigidBody(rigidFunc) {};

	template<typename T, typename... Args>	
	T* SpawnWorld(Args&&... args) {
		auto obj = std::make_unique<T>(std::forward<Args>(args)...);
		T* ptr = obj.get();
		objects.push_back(std::move(obj));
		return ptr;
	};

	template<typename N, typename... Args>
	N* SpawnPhysicsObject(Args&&... args) {
		N* obj = SpawnWorld<N>(std::forward<Args>(args)...);
		RigidBody* rigBody = assignRigidBody(obj);
		rigBody->Forces = Vec2f(1.f, 1.f);
		return obj;
	}
};

