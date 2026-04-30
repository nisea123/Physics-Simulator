#include "Object.h"
#include "Renderer.h"
#include <iostream>

void Renderer::Draw(const Square& item) {

	float x = item.Position.x;
	float y = item.Position.y;
	float w = item.Size.x;
	float h = item.Size.y;

	float r = item.Color.r;
	float g = item.Color.g;
	float b = item.Color.b;

	float cX = x;
	float cY = y;

	float rot = item.Rotation;

	unsigned int ind = vertices.size() / 6;

	vertices.insert(vertices.end(), {
		(cX - w / 2) * cos(rot), cY + h / 2 * sin(rot), 0.0f ,r ,g ,b, // left top
		(cX + w / 2) * cos(rot), (cY + h / 2) * sin(rot), 0.0f ,r ,g ,b, // right top
		(cX + w / 2) * cos(rot), (cY - h / 2) * sin(rot), 0.0f ,r ,g ,b, // right bottom
		(cX - w / 2) * cos(rot), (cY - h / 2) * sin(rot), 0.0f ,r ,g ,b, // left bottom
		});

	indices.insert(indices.end(), {
		ind, ind + 1, ind + 2,
		ind, ind + 2, ind + 3
		});
}

void Renderer::Draw(const Circle& item) {
	int n = 30;

	float ra = item.Radius;
	float x = item.Position.x;
	float y = item.Position.y;

	float r = 0.498f;
	float g = 1.0f;
	float b = 0.0f;

	float num = 6.28 / n;

	float rot = item.Rotation;

	unsigned int ind = vertices.size() / 6;

	vertices.insert(vertices.end(), {
		x * float(cos(rot)), y * float(sin(rot)), 0.0f, r, g, b
		});
	int count = 0;
	for (float i = 0; i < 6.28; i += num) {
		count++;
		vertices.insert(vertices.end(), {
			ra * float(cos(i+rot)) + x,ra * float(sin(i+rot)) + y , 0.0f, r * float(sin(i)), g * float(sin(i)) , b * float(sin(i)),
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

void Renderer::Draw(const Triangle& item) {

	float w = item.Size.x;
	float h = item.Size.y;

	float x = item.Position.x;
	float y = item.Position.y;

	float r = item.Color.r;
	float g = item.Color.g;
	float b = item.Color.b;

	unsigned int ind = vertices.size() / 6;

	vertices.insert(vertices.end(), {
		x, y ,0.0f, r, g, b,
		x + w, y ,0.0f, r ,g ,b,
		x, y + h, 0.0f, r, g, b
		});
	indices.insert(indices.end(), {
		ind,ind + 1, ind + 2
		});
}

void Renderer::Clear() {
	vertices.clear();
	indices.clear();
}