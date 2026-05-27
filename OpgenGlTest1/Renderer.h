#pragma once

#include <glad/glad.h>
#include "Object.h"
#include <vector>
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "shaderClass.h"
#include "UiRenderer.h"
#include <map>

class Renderer 
{
public:
	Shader& shader;

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	static constexpr int VERTEX_SIZE = 9;

	Renderer(Shader& s);

	// Used to draw objects
	void Draw(const Rectangle& item);
	void Draw(const Circle& item);
	void Draw(const Triangle& item);
	void Draw(const Text& txt);
	void Draw(const UiElement& item);

	//GPU stuff binding and stuff
	void Render(); // Drawing the stuff on the screen
	void Clear();
	void Destroy(); // Destroys the VBO VAO AND EAO at the end of the program
private:
	VBO VBO1;
	VAO VAO1;
	EBO EBO1;

	void UploadBuffers(); // Uploading to GPU
	void DrawBuffers();
	void ClearScreen(); // Clearing screen
	void ClearBuffers(); // Clearing vertices and indices
};