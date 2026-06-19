#pragma once

#include "ObjectManager.h"
#include "UiManager.h"
#include "Gizmo.h"

class Scene
{
public:
	ObjectManager objects;
	UiManager ui;
	Gizmo gizmo;

	Scene() : ui(objects), gizmo() {};
};