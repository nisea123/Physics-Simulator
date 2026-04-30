#pragma once

#include <glad/glad.h>
#include "Object.h"
#include <vector>

class Renderer 
{
public:

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	void Draw(const Square& item);
	void Draw(const Circle& item);
	void Draw(const Triangle& item);
	void Clear();
};