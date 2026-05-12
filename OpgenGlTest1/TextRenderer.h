#pragma once

//#include "ft2build.h"
//#include  FT_FREETYPE_H

#include <glad/glad.h>
#include "Structs.h"
#include "Transform.h"
#include "Object.h"
#include <string>
#include <map>

struct Character {
	Vec2i Size;
	Vec2i Bearing;
	unsigned int Advance;

	Vec2f UV1;
	Vec2f UV2;
};

class Font {
public:
	GLuint id;
	int lineHeight;
	std::map<char, Character> Characters;

	Font(const char* txt);

};

class Text {
public:
	Font& font;
	Transform Transform;
	Color Color;
	std::string Content;

	Text(Font& f) : font(f) {};
};

class UiBlock
{
public:
	Rectangle rect;
	Text text;

	UiBlock(Font& font, Vec2f size, Vec2f pos) : rect(size, pos), text(font) {
		text.Transform.Position = pos;
		rect.Transform.Position = pos;
	};
};