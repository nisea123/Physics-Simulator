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
		rigBody->AddForce("Gravity", Vec2f(0.f, -10.f));
		rigBody->AddForce("Wind", Vec2f(20.f, 0.f));
		rigBody->AddForce("Me", Vec2f(-30.f, 0.f));
		rigBody->AddForce("Also me", Vec2f(30.f, 10.f));
		rigBody->AddForce("Vyk", Vec2f(0.2f, 0.1f));
		//rigBody->Velocity = Vec2f(0.f, 1000.f);
		return obj;
	}
};