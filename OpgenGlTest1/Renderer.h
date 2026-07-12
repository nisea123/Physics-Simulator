#pragma once

#include "shaderClass.h"
#include "ObjectRenderer.h"
#include "TextRenderer.h"
#include "Object.h"
#include "ObjectData.h"
#include "Ui.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer
{
public:
	ObjectRenderer objRenderer;
	TextRenderer txtRenderer;

	Renderer(Shader& objShader, Shader& txtShader) : objRenderer(objShader), txtRenderer(txtShader) {};

	void Draw(const Rectangle& item);
	void Draw(const Circle& item);
	void Draw(const Triangle& item);
	void Draw(const Line& item);
	void Draw(const Line& item, float trimmed);
	void Draw(const Arrow& item);
	void Draw(const Arc& item);
	void Draw(const Text& txt);
	void Draw(const UiButton& item);
	void Draw(const UiFrame& item);
	void Draw(const UiSlider& item);
	void Draw(const UiText& item);

	void DrawArrow(ArrowDesc& desc);
	void DrawLine(LineDesc& desc);

	void Render(const glm::mat4& proj); // Drawing the stuff on the screen
	void Clear();
	void Destroy(); // Destroys the VBO VAO AND EBO at the end of the program

private:
	void ClearScreen(); // Clearing screen
	void ClearBuffers(); // Clearing vertices and indices
	void DrawArrowHead(const Arrow& item);
};