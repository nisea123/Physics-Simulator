#pragma once

#include "ObjectManager.h"
#include "UiManager.h"
#include "Gizmo.h"

#include "Renderer.h"
#include "ObjectCast.h"
#include "Mouse.h"

class Scene
{
public:
	ObjectManager objects;
	UiManager ui;
	Gizmo gizmo; 

	// In the future i will  all of these Objects to their respective manager for now i will keep it here for simplicity

	Object* selectedObject = nullptr;
	Object* holdingObject = nullptr;
	Object* hoveredObject = nullptr;

	UiElement* hoveredUi = nullptr;

	GizmoHandle* holdingHandle = nullptr;
	GizmoHandle* hoveredHandle = nullptr;
	GizmoHandle* lastHoveredHandle = nullptr;

	Scene() : ui(objects), gizmo() {};

	void Draw(Renderer& renderer);
	void Update(Mouse& mouse);
	void UpdateHover(Mouse& mouse);
	void UpdateSelection(Mouse& mouse);
	void UpdateDragging(Mouse& mouse);
	void UpdateGizmo(Mouse& mouse);
};