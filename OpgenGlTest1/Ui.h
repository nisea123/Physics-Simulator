#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "Transform.h"
#include "CoordinateSpace.h"

class UiElement
{
public:

	UiTransform Transform;
	bool Visible = true;
	float CornerRadius = 0.f;
	CoordinateSpace Space = CoordinateSpace::Screen;

	std::vector<std::unique_ptr<UiElement>> Children;

	virtual bool Contains(Vec2f p);
	std::function<void()> OnClick;

	UiElement* getParent() const {
		return parent;
	}
	
	Vec2f getAbsoluteSize(Vec2f& windowSize) const {
		if (parent) {
			Vec2f newSize = parent->getAbsoluteSize(windowSize);
			return Transform.Size.ToAbsolute(newSize);
		}
		else {
			return Transform.Size.ToAbsolute(windowSize);
		}
	}

	Vec2f getAbsolutePosition(Vec2f& windowSize) const {
		if (parent) {
			Vec2f newSize = parent->getAbsoluteSize(windowSize);
			return parent->getAbsolutePosition(windowSize) + Transform.Position.ToAbsolute(newSize);
		}
		else {
			return Transform.Position.ToAbsolute();
		}
	}

	virtual ~UiElement() = default;
protected:
	UiElement* parent = nullptr;
};