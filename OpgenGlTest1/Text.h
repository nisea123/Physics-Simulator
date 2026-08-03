#pragma once

//#include "ft2build.h"
//#include  FT_FREETYPE_H

#include <glad/glad.h>
#include <string>
#include <functional>

#include "Structs.h"
#include "Transform.h"
#include "Object.h"
#include "Ui.h"

#include "Font.h"

class Text : public UiElement {
public:
	Font& font;
	std::string Content;
	float ShapeType = 0;

	Text(Font& f, UiElement* par = nullptr) : font(f) {
		Transform.Position = UDim2(Vec2f(0.f), Vec2f(0.f));
		Transform.Size = UDim2(Vec2f(1.f), Vec2f(0.f));
		parent = par;
	};
};

class Tracker : public Text {
public:
	std::string StartText;
	std::string EndText;
	float* Value = nullptr;

	Tracker(Font& f, float& v, std::string start, std::string end) : Text(f), Value(&v), StartText(start), EndText(end) {};
	Tracker(Font& f, float& v) : Text(f), Value(&v) {};
	Tracker(Font& f) : Text(f) {};
	
	void SetValue(float& v) {
		Value = &v;
	}
};