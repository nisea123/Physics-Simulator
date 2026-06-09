#include "Renderer.h"

void Renderer::Render(const glm::mat4& proj) {
	objRenderer.Render(proj);
	txtRenderer.Render(proj);

}

void Renderer::Destroy() {

	objRenderer.Destroy();
	txtRenderer.Destroy();

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
	objRenderer.ClearBuffers();
	txtRenderer.ClearBuffers();
}