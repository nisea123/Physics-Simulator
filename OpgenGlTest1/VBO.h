#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include <vector>
#include "ShapeInstance.h"

using namespace std;

class VBO
{
public:
	GLuint ID;
	VBO(vector<GLfloat>* vertices);
	VBO(vector<ShapeInstance>* vertices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif