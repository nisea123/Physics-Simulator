#pragma once

#include "ObjectManager.h"
#include "Ui.h"
#include "Font.h"
#include "FontManager.h"

class UiManager
{
public:
	FontManager& Fonts;
	ObjectManager& objects;
	std::vector<std::unique_ptr<UiElement>> ui;

	UiManager(ObjectManager& obj, FontManager& fontManager) : objects(obj), Fonts(fontManager) {
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