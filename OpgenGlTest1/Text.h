#pragma once

//#include "ft2build.h"
//#include  FT_FREETYPE_H

#include <glad/glad.h>
#include <string>
#include <functional>

#include "Structs.h"
#include "Transform.h"
#include "Object.h"

#include "Font.h"

class Text {
public:
	Font& font;
	Transform Transform;
	Color Color;
	std::string Content;
	float ShapeType = 0;

	Text(Font& f) : font(f) {};
};