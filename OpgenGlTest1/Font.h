#pragma once

#include <glad/glad.h>
#include <map>

#include "Structs.h"

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

	Font() {
		Font("OpenSans.ttf");
	};
	Font(const char* txt);

};