#pragma once

#include "ObjectManager.h"
#include "UiManager.h"

class Scene
{
public:
	ObjectManager objects;
	UiManager ui;

	Scene() : ui(objects) {};
};