#pragma once

#include "ObjectManager.h"
#include "Ui.h"

class UiManager
{
public:
	Font font = Font("OpenSans.ttf");
	ObjectManager& objects;
	std::vector<std::unique_ptr<UiElement>> ui;

	UiManager(ObjectManager& obj) : objects(obj) {
		Init();
	}

	template<typename T, typename... Args>
	T* SpawnUi(Args&&... args) {
		auto obj = std::make_unique<T>(std::forward<Args>(args)...);
		T* ptr = obj.get();
		ui.push_back(std::move(obj));
		return ptr;
	};
	void Init();
};