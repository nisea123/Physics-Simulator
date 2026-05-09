#include "Object.h"
#include "Renderer.h"
#include <iostream>

void Renderer::Draw(const Triangle& item) {

	float w = item.Size.x;
	float h = item.Size.y;

	float r = item.Color.r;
	float g = item.Color.g;
	float b = item.Color.b;

	Transform Transform = item.Transform;

	Vec2 p1 = Transform.Apply({ 0,0 });
	Vec2 p2 = Transform.Apply({ w,0 });
	Vec2 p3 = Transform.Apply({ 0,h });

	unsigned int ind = vertices.size() / 8;

	DrawBorder(item);

	vertices.insert(vertices.end(), {
		p1.x, p1.y ,0.0f, r, g, b, 0,0,
		p2.x, p2.y ,0.0f, r ,g ,b, 1,0,
		p3.x, p3.y, 0.0f, r, g, b, 0,1
		});
	indices.insert(indices.end(), {
		ind,ind + 1, ind + 2
		});
}

void Renderer::Draw(const Rectangle& item) {


	float w = item.Size.x;
	float h = item.Size.y;

	float r = item.Color.r;
	float g = item.Color.g;
	float b = item.Color.b;

	Transform Transform = item.Transform;

	unsigned int ind = vertices.size() / 8;

	Vec2 p1 = Transform.Apply({ -w / 2,  h / 2 });
	Vec2 p2 = Transform.Apply({ w / 2,  h / 2 });
	Vec2 p3 = Transform.Apply({ w / 2, -h / 2 });
	Vec2 p4 = Transform.Apply({ -w / 2, -h / 2 });

	DrawBorder(item);

	vertices.insert(vertices.end(), {
		// p1 (left top)
		p1.x, p1.y, 0.0f,  r,g,b,  0,0,

		// p2 (right top)
		p2.x, p2.y, 0.0f,  r,g,b,  1,0,

		// p3 (right bottom)
		p3.x, p3.y, 0.0f,  r,g,b,  1,1,

		// p4 (left bottom)
		p4.x, p4.y, 0.0f,  r,g,b,  0,1
		});

	indices.insert(indices.end(), {
		ind, ind + 1, ind + 2,
		ind, ind + 2, ind + 3
		});
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

	unsigned int ind = vertices.size() / 8;

	Vec2 p1 = Transform.Apply({ 0,0 });

	DrawBorder(item);

	vertices.insert(vertices.end(), {
		p1.x, p1.y, 0.0f, r, g, b, 0,0
		});

	int count = 0;

	for (float i = 0; i < 6.28; i += num) {
		Vec2 p = Transform.Apply({cos(i) * ra,sin(i) * ra});
		count++;
		vertices.insert(vertices.end(), {
			p.x, p.y , 0.0f, r, g, b, cos(i), sin(i)
			});
	}
	for (int i = 1; i <= count; i++) {
		unsigned int current = ind + i;
		unsigned int next = ind + (i % count) + 1;
		indices.insert(indices.end(), {
			ind, current, next
			});
	}
}

void Renderer::Clear() {
	vertices.clear();
	indices.clear();
}

void Renderer::DrawBorder(const Object& item) {
	GLuint shapeTypeLoc = glGetUniformLocation(shader.ID,"shapeType");
	GLuint borderSize = glGetUniformLocation(shader.ID, "borderSize");;
	GLuint borderColorLoc = glGetUniformLocation(shader.ID, "borderColor");

	auto [r, g, b, a] = item.Border.Color;

	glUniform1i(shapeTypeLoc, item.ShapeType);
	glUniform1f(borderSize, item.Border.Thickness);
	glUniform3f(borderColorLoc,r,g,b);
}