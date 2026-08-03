#pragma once

#include "Ui.h"
#include "Text.h"

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
	UiButton(Font& font, UDim2 size, UDim2 pos) : text(font, this) {
		Transform.Position = pos;
		Transform.Size = size;
	}
	
	//to do
};

class UiSlider : public UiElement
{
public:
	//to do
};