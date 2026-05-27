#pragma once

//#include "ft2build.h"
//#include  FT_FREETYPE_H

#include <glad/glad.h>
#include "Structs.h"
#include "Transform.h"
#include "Object.h"
#include <string>
#include <map>
#include <functional>

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
	float ShapeType = -1;

	Text(Font& f) : font(f) {};
};