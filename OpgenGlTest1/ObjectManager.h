#pragma once

#include <vector>
#include <memory>

#include "Object.h"
#include "UiRenderer.h"

class ObjectManager {
public:
	std::vector<std::unique_ptr<Object>> objects;

	template<typename T, typename... Args>
	T* SpawnWorld(Args&&... args) {
		auto obj = std::make_unique<T>(std::forward<Args>(args)...);
		T* ptr = obj.get();
		objects.push_back(std::move(obj));
		return ptr;
	};
};

