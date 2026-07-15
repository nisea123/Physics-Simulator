#include "Scene.h"
#include "RigidBody.h"

RigidBody* Scene::AssignRigidBody(Object* obj) {
	obj->PhysicsBody = make_unique<RigidBody>(obj);

	RigidBody* body = obj->PhysicsBody.get();

	physicsWorld.RegisterRigidBody(body);

	return body;
}