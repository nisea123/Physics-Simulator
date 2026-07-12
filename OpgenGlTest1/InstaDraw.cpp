// This file will draw objects from their data and not their object
#include "Renderer.h"

void Renderer::DrawArrow(ArrowDesc& desc) {

	float trimmed = desc.ArrowHeight + 10.f;

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