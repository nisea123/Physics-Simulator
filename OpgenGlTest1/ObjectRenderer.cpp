#include "ObjectRenderer.h"
#include <iostream>

ObjectRenderer::ObjectRenderer(Shader& s)
	: shader(s), quadVBO(&vertices), instanceVBO(&shapeInstances), objEBO(&indices)
{
	objVAO.Bind();

	PushQuad();

	quadVBO.Bind();
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_DYNAMIC_DRAW);

	objEBO.Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_DYNAMIC_DRAW);

	instanceVBO.Bind();

	//Quad
	objVAO.LinkAttrib(quadVBO, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);

	//Instances
	objVAO.LinkInstanceAttrib(instanceVBO, 1, 2, GL_FLOAT, sizeof(ShapeInstance),
		(void*)offsetof(ShapeInstance, position));

	objVAO.LinkInstanceAttrib(instanceVBO, 2, 2, GL_FLOAT, sizeof(ShapeInstance),
		(void*)offsetof(ShapeInstance, size));

	objVAO.LinkInstanceAttrib(instanceVBO, 3, 4, GL_FLOAT, sizeof(ShapeInstance),
		(void*)offsetof(ShapeInstance, color));

	objVAO.LinkInstanceAttrib(instanceVBO, 4, 1, GL_FLOAT, sizeof(ShapeInstance),
		(void*)offsetof(ShapeInstance, radius));

	objVAO.LinkInstanceAttrib(instanceVBO, 5, 1, GL_FLOAT, sizeof(ShapeInstance),
		(void*)offsetof(ShapeInstance, rotation));

	objVAO.LinkInstanceAttrib(instanceVBO, 6, 1, GL_FLOAT, sizeof(ShapeInstance),
		(void*)offsetof(ShapeInstance, type));


	objVAO.Unbind();

}

void ObjectRenderer::Render(const glm::mat4& proj) {

	if (shapeInstances.empty()) return;

	shader.Activate();

	glUniformMatrix4fv(
		glGetUniformLocation(shader.ID, "projection"),
		1,
		GL_FALSE,
		&proj[0][0]
	);

	objVAO.Bind();

	instanceVBO.Bind();
	glBufferData(GL_ARRAY_BUFFER, shapeInstances.size() * sizeof(ShapeInstance), shapeInstances.data(), GL_DYNAMIC_DRAW);

	glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr, shapeInstances.size());
}

void ObjectRenderer::PushQuad() {
	vertices.insert(vertices.end(), {
		0,0,
		0,1,
		1,0,
		1,1
		});
	indices.insert(indices.end(), {
		0,1,2,
		1,2,3
		});
}

void ObjectRenderer::Destroy() {

	objVAO.Delete();
	quadVBO.Delete();
	instanceVBO.Delete();
	objEBO.Delete();
	shader.Delete();

}

void ObjectRenderer::ClearBuffers() {
	shapeInstances.clear();
}