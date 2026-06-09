#include "TextRenderer.h"

TextRenderer::TextRenderer(Shader& s) 
	: shader(s), textVBO(&textVertices), textEBO(&textIndices) {

	textVAO.Bind();

	textVBO.Bind();
	textEBO.Bind();

	textVAO.LinkAttrib(textVBO, 0, 2, GL_FLOAT, 7 * sizeof(float), (void*)0);
	textVAO.LinkAttrib(textVBO, 1, 3, GL_FLOAT, 7 * sizeof(float), (void*)(2 * sizeof(float)));
	textVAO.LinkAttrib(textVBO, 2, 2, GL_FLOAT, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	
	textVAO.Unbind();
}

void TextRenderer::Render(const glm::mat4& proj) {

	if (textVertices.empty() || textIndices.empty()) return;

	shader.Activate();

	textVAO.Bind();
	textVBO.Bind();
	textEBO.Bind();

	glUniformMatrix4fv(
		glGetUniformLocation(shader.ID, "projection"),
		1,
		GL_FALSE,
		&proj[0][0]
	);

	glBufferData(GL_ARRAY_BUFFER, textVertices.size() * sizeof(GLfloat), textVertices.data(), GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, textIndices.size() * sizeof(GLuint), textIndices.data(), GL_DYNAMIC_DRAW);

	glUniform1i(glGetUniformLocation(shader.ID, "textTexture"), 0);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glDrawElements(GL_TRIANGLES, textIndices.size(), GL_UNSIGNED_INT, 0);
}

void TextRenderer::Destroy() {
	
	textVBO.Delete();
	textVAO.Delete();
	textEBO.Delete();
	shader.Delete();

}

void TextRenderer::ClearBuffers() {
	textVertices.clear();
	textIndices.clear();
}