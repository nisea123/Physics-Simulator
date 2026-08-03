#pragma once

#include "ObjectManager.h"
#include "UiManager.h"
#include "Gizmo.h"
#include "PhysicsWorld.h"

#include "Renderer.h"
#include "ObjectCast.h"
#include "Mouse.h"

class Scene
{
public:
	ObjectManager objects;
	UiManager ui;
	Gizmo gizmo; 
	PhysicsWorld physicsWorld;
	Mouse mouse;

	Camera& camera;

	// In the future i will  all of these Objects to their respective manager for now i will keep it here for simplicity

	Object* selectedObject = nullptr;
	Object* holdingObject = nullptr;
	Object* hoveredObject = nullptr;

	UiElement* hoveredUi = nullptr;

	GizmoHandle* holdingHandle = nullptr;
	GizmoHandle* hoveredHandle = nullptr;
	GizmoHandle* lastHoveredHandle = nullptr;

	Scene(FontManager& fontManager,Camera& camera) : objects([this](Object* obj) {return AssignRigidBody(obj);}), ui(objects,fontManager), gizmo(), camera(camera) {};

	void Draw(Renderer& renderer);
	void Update(float dt);
	void UpdateHover();
	void UpdateSelection();
	void UpdateDragging();
	void UpdateGizmo();

	RigidBody* AssignRigidBody(Object* obj);
};