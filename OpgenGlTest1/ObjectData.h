#pragma once

#include "Structs.h"
#include "Object.h"
#include "Font.h"
#include "FontManager.h"

#include <string>

struct ArrowDesc {
	Vec2f Start;
	Vec2f End;

	float ArrowWidth;
	float ArrowHeight;
	float Thickness;
	Color Color;
};

struct LineDesc {
	Vec2f Start;
	Vec2f End;

	float Thickness;
	Color Color;
};

struct TextDesc {
	std::string Content;
	Vec2f Position;

	Font& TextFont;

	TextDesc(Font& font) : TextFont(font) {
	};
};

//ArrowDesc toArrowDesc(const Arrow* object, float newThickness);