#pragma once

#include "ObjectManager.h"
#include "UiRenderer.h"

class UiManager
{
public:
	ObjectManager& objects;
	std::vector<std::unique_ptr<UiElement>> ui;

	UiManager(ObjectManager& obj) : objects(obj) {}

	template<typename T, typename... Args>
	T* SpawnUi(Args&&... args) {
		auto obj = std::make_unique<T>(std::forward<Args>(args)...);
		T* ptr = obj.get();
		ui.push_back(std::move(obj));
		return ptr;
	};
	void Init();
};