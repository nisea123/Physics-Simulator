#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "Object.h"
#include "Text.h"

class UiElement
{
public:
	Rectangle rect;
	bool Visible = true;
	UiElement* parent = nullptr;

	std::vector<std::unique_ptr<UiElement>> Children;

	virtual bool Contains(Vec2f p) { return rect.Contains(p); };
	std::function<void()> OnClick;

	virtual ~UiElement() = default;
};

class UiFrame : public UiElement
{
public:
	//to do
};

class UiButton : public UiElement
{
public:
	Text text;
	bool isChecked = false;
	UiButton(Font& font, Vec2f size, Vec2f pos) : text(font) {
		rect = Rectangle(size, pos);
		text.Transform.Position = Vec2f(pos.x - size.x / 2.f,pos.y + size.y / 2.f);
	}
	//to do
};

class UiSlider : public UiElement
{
public:
	//to do
};

class UiText : public UiElement
{
public:
	Text text;
};