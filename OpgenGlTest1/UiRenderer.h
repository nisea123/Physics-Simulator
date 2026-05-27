#include <memory>

#include "Object.h"
#include "TextRenderer.h"

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