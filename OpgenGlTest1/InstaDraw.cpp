// This file will draw objects from their data and not their object
#include "Renderer.h"

void Renderer::DrawArrow(ArrowDesc& desc) {

	float trimmed = desc.ArrowHeight * desc.Thickness * 1.1f;

	float arrowHeight = desc.Thickness * desc.ArrowHeight;
	float arrowWidth = desc.Thickness * desc.ArrowWidth;
	Vec2f tipPos = desc.End;
	Vec2f dir = Normalize(desc.End - desc.Start);


	// Head
	ShapeInstance head;

	head.position = tipPos;
	head.size = { arrowHeight,arrowWidth };
	head.rotation = atan2(dir.y, dir.x);
	head.color = desc.Color;
	head.type = static_cast<float>(ObjectType::Arrow);

	objRenderer.shapeInstances.push_back(head);

	//Shaft

	ShapeInstance shaft;

	Vec2f start = desc.Start;
	Vec2f end = desc.End - dir * (trimmed * 0.5f);

	Vec2f delta = end - start;

	float len = Length(delta);
	Vec2f midPoint = start + dir * (len * 0.5f);

	Vec2f size = { len,desc.Thickness };
	float angle = atan2(dir.y, dir.x);

	shaft.position = midPoint;
	shaft.size = size;
	shaft.rotation = angle;
	shaft.color = desc.Color;
	shaft.type = static_cast<float>(ObjectType::Line);
	shaft.radius = 0;

	objRenderer.shapeInstances.push_back(shaft);
}

void Renderer::DrawLine(LineDesc& desc) {
	ShapeInstance line;

	Vec2f start = desc.Start;
	Vec2f end = desc.End;

	Vec2f dir = Normalize(desc.End - desc.Start);
	
	Vec2f delta = end - start;

	float len = Length(delta);
	Vec2f midPoint = start + dir * (len * 0.5f);

	Vec2f size = { len,desc.Thickness };
	float angle = atan2(dir.y, dir.x);

	line.position = midPoint;
	line.size = size;
	line.rotation = angle;
	line.color = desc.Color;
	line.type = static_cast<float>(ObjectType::Line);
	line.radius = 0;

	objRenderer.shapeInstances.push_back(line);
}

void Renderer::DrawText(TextDesc& desc) {
	float orgX = desc.Position.x;
	float limitX = 1920;

	float lineHeight = desc.TextFont.lineHeight;

	float x = orgX;
	float y = desc.Position.y - lineHeight;

	float r = 0.0f, g = 0.0f, b = 0.0f;

	for (unsigned char c : desc.Content)
	{
		const Character& ch = desc.TextFont.Characters.at(c);

		float xpos = x + ch.Bearing.x;

		if (xpos + ch.Size.x > limitX) {
			x = orgX;
			y -= lineHeight;
			xpos = x + ch.Bearing.x;
		}

		float ypos = y - (ch.Size.y - ch.Bearing.y);

		float w = ch.Size.x;
		float h = ch.Size.y;

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
	glBindTexture(GL_TEXTURE_2D, desc.TextFont.id); // Bind your loaded texture to slot 0

}