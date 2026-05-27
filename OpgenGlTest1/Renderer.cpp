#include "Object.h"
#include "Renderer.h"
#include <iostream>

Renderer::Renderer(Shader& s)
	: shader(s), VBO1(&vertices), EBO1(&indices)
{
	VAO1.Bind();

	VBO1.Bind();
	EBO1.Bind();

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 1, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)(8 * sizeof(float)));
	VAO1.Unbind();
}

void Renderer::Render() {

	if (indices.empty() || vertices.empty()) return;

	shader.Activate();

	glUniform1i(glGetUniformLocation(shader.ID, "textTexture"), 0);

	VAO1.Bind();
	VBO1.Bind();
	EBO1.Bind();

	UploadBuffers();

	DrawBuffers();
}

void Renderer::UploadBuffers() {
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_DYNAMIC_DRAW);

}

void Renderer::DrawBuffers() {
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Renderer::Destroy() {

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shader.Delete();

}

void Renderer::Clear() {
	ClearScreen();
	ClearBuffers();
}

void Renderer::ClearScreen() {
	glClearColor(0.07f, 0.13f, 0.17f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::ClearBuffers() {
	vertices.clear();
	indices.clear();
}