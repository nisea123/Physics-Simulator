#pragma once

#include <glad/glad.h>
#include "Object.h"
#include <vector>
#include "shaderClass.h"

class Renderer 
{
public:
	Shader& shader;

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	Renderer(Shader& s) : shader(s) {}

	void Draw(const Rectangle& item);
	void Draw(const Circle& item);
	void Draw(const Triangle& item);
	void Clear();
private:
	void DrawBorder(const Object& item);
};