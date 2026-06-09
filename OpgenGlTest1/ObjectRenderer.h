#pragma once

#include <glad/glad.h>
#include <vector>

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "shaderClass.h"
#include "ShapeInstance.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ObjectRenderer
{
public:
	Shader& shader;

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	std::vector<ShapeInstance> shapeInstances;

	ObjectRenderer(Shader& s);

	// Used to draw objects
	void Render(const glm::mat4& proj); // Drawing the stuff on the screen
	void ClearBuffers();
	void Destroy(); // Destroys the VBO VAO AND EBO at the end of the program

	//GPU stuff binding and stuff

private:

	VBO quadVBO;
	VBO instanceVBO;
	VAO objVAO;
	EBO objEBO;

	void PushQuad();
};