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

	int x1 = cX - w / 2; // left
	int x2 = cX + w / 2; // right
	int y1 = cY - h / 2; // bottom
	int y2 = cY + h / 2; // top

	vertices.insert(vertices.end(), {
		x1 * cos(rot) - y1 * sin(rot), y1 * cos(rot) + x1 * sin(rot), 0.0f ,r ,g ,b, // left top
		x2 * cos(rot) - y1 * sin(rot), y1 * cos(rot) + x2 * sin(rot), 0.0f ,r ,g ,b, // right top
		x2 * cos(rot) - y2 * sin(rot), y2 * cos(rot) + x2 * sin(rot), 0.0f ,r ,g ,b, // right bottom
		x1 * cos(rot) - y2 * sin(rot), y2 * cos(rot) + x1 * sin(rot), 0.0f ,r ,g ,b, // left bottom
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

	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;

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
			ra * float(cos(i+rot)) + x,ra * float(sin(i+rot)) + y , 0.0f, r * sin(i + rot), g * sin(i + rot), b * sin(i + rot),
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