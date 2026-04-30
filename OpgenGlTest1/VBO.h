#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include <vector>

using namespace std;

class VBO
{
public:
	GLuint ID;
	VBO(vector<GLfloat>* vertices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif