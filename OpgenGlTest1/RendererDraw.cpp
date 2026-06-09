#include "Renderer.h"

using namespace std;

void Renderer::Draw(const Triangle& item) {

	float w = item.Size.x;
	float h = item.Size.y;

	float r = item.Color.r;
	float g = item.Color.g;
	float b = item.Color.b;

	Transform Transform = item.Transform;

	Vec2f p1 = Transform.Apply({ 0,0 });
	Vec2f p2 = Transform.Apply({ w,0 });
	Vec2f p3 = Transform.Apply({ 0,h }); // Getting new values of the points after scaling,rotation and offset

	float radius = 0;

	float type = item.ShapeType;
}

void Renderer::Draw(const Rectangle& item) {

	ShapeInstance shapeInstance;

	shapeInstance.color = item.Color;
	shapeInstance.position = item.Transform.Position;
	shapeInstance.size = item.Size;
	shapeInstance.radius = item.CornerRadius;
	shapeInstance.type = item.ShapeType;

	objRenderer.shapeInstances.push_back(shapeInstance);
}

void Renderer::Draw(const Circle& item) {
	int n = 30;

	float ra = item.Radius;

	float r = item.Color.r;
	float g = item.Color.g;
	float b = item.Color.b;

	float num = 6.28 / n;

	float rot = item.Transform.Rotation;

	Transform Transform = item.Transform;


	float type = item.ShapeType;

	Vec2f p1 = Transform.Apply({ 0,0 });

	int count = 0;

}

void Renderer::Draw(const Text& txt)
{
	float orgX = txt.Transform.Position.x;
	float limitX = 1920;

	float lineHeight = txt.font.lineHeight;

	float x = orgX;
	float y = txt.Transform.Position.y - lineHeight;

	float r = 0.0f, g = 0.0f, b = 0.0f;

	for (unsigned char c : txt.Content)
	{
		const Character& ch = txt.font.Characters.at(c);

		float xpos = x + ch.Bearing.x;

		if (xpos + ch.Size.x > limitX) {
			x = orgX;
			y -= lineHeight;
			xpos = x + ch.Bearing.x;
		}

		float ypos = y - (ch.Size.y - ch.Bearing.y);

		float w = ch.Size.x;
		float h = ch.Size.y;

		float type = txt.ShapeType;

		float u0 = ch.UV1.x;
		float v0 = ch.UV1.y;
		float u1 = ch.UV2.x;
		float v1 = ch.UV2.y;

		x += (ch.Advance >> 6);

		unsigned int ind = txtRenderer.textVertices.size() / 7;

		txtRenderer.textVertices.insert(txtRenderer.textVertices.end(), {
			xpos,     ypos + h, r,g,b, u0, v1,
			xpos,     ypos,     r,g,b, u0, v0,
			xpos + w, ypos,     r,g,b, u1, v0,
			xpos + w, ypos + h, r,g,b, u1, v1
			});

		txtRenderer.textIndices.insert(txtRenderer.textIndices.end(), {
			ind, ind + 1, ind + 2,
			ind, ind + 2, ind + 3
			});
	}

	glActiveTexture(GL_TEXTURE0); // Activate slot 0
	glBindTexture(GL_TEXTURE_2D, txt.font.id); // Bind your loaded texture to slot 0

}

void Renderer::Draw(const UiButton& item) {
	Draw(item.rect);
	Draw(item.text);
}

void Renderer::Draw(const UiFrame& item) {
	Draw(item.rect);
}

void Renderer::Draw(const UiSlider& item) {
	Draw(item.rect);
}

void Renderer::Draw(const UiText& item) {
	Draw(item.rect);
	Draw(item.text);
}