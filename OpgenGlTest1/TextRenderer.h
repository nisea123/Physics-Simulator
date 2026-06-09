#pragma once

#include <glad/glad.h>
#include <vector>

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "shaderClass.h"
#include "Ui.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TextRenderer
{
public:
	Shader& shader;

	vector<GLfloat> textVertices;
	vector<GLuint> textIndices;

	TextRenderer(Shader& s);
	void Render(const glm::mat4& proj); // Drawing the stuff on the screen
	void Destroy(); // Destroys the VBO VAO AND EBO at the end of the program
	void ClearBuffers();

private: 

	VBO textVBO;
	VAO textVAO;
	EBO textEBO;

};