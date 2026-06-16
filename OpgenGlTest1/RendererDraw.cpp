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
	shapeInstance.rotation = item.Transform.Rotation;

	objRenderer.shapeInstances.push_back(shapeInstance);
}

void Renderer::Draw(const Circle& item) {
	 
	ShapeInstance shapeInstance;

	shapeInstance.color = item.Color;
	shapeInstance.position = item.Transform.Position;
	shapeInstance.size = Vec2f(item.Radius,item.Radius);
	shapeInstance.radius = item.Radius;
	shapeInstance.type = item.ShapeType;

	objRenderer.shapeInstances.push_back(shapeInstance);
}

void Renderer::Draw(const Line& item) {

	ShapeInstance shapeInstance;

	Vec2f dir = Normalize(item.End - item.Start);
	float len = Length(item.End - item.Start);

	Vec2f midPoint = (item.Start + item.End) * .5;
	Vec2f size = { len,item.Thickness };
	float angle = atan2(dir.y, dir.x);

	shapeInstance.position = midPoint;
	shapeInstance.size = size;
	shapeInstance.rotation = angle;
	shapeInstance.color = item.Color;
	shapeInstance.type = 4;
	shapeInstance.radius = 0;

	objRenderer.shapeInstances.push_back(shapeInstance);
}

void Renderer::Draw(const Line& item, float trimmed) {
	ShapeInstance shapeInstance;

	Vec2f dir = Normalize(item.End - item.Start);

	float len = Length(item.End - item.Start) - trimmed;

	Vec2f midPoint = item.Start + dir * (len * 0.5f + trimmed * 0.5f);
	Vec2f size = { len,item.Thickness };
	float angle = atan2(dir.y, dir.x);

	shapeInstance.position = midPoint;
	shapeInstance.size = size;
	shapeInstance.rotation = angle;
	shapeInstance.color = item.Color;
	shapeInstance.type = 4;
	shapeInstance.radius = 0;

	objRenderer.shapeInstances.push_back(shapeInstance);
}

void Renderer::Draw(const Arrow& item) {
	float trimmed = item.Thickness * item.ArrowHeight;

	DrawArrowHead(item);
	Draw(static_cast<const Line&>(item),trimmed);
	
}

void Renderer::DrawArrowHead(const Arrow& item) {
	float arrowHeight = item.Thickness * item.ArrowHeight;
	float arrowWidth = item.Thickness * item.ArrowWidth;
	Vec2f tipPos = item.End;
	Vec2f dir = Normalize(item.End - item.Start);
	
	ShapeInstance shapeInstance;

	shapeInstance.position = tipPos;
	shapeInstance.size = { arrowHeight,arrowWidth };
	shapeInstance.rotation = atan2(dir.y, dir.x);
	shapeInstance.color = item.Color;
	shapeInstance.type = item.ShapeType;

	objRenderer.shapeInstances.push_back(shapeInstance);

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