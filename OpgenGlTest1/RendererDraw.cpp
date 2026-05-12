#include "Renderer.h"
#include <map>
#include "TextRenderer.h"

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

	unsigned int ind = vertices.size() / VERTEX_SIZE;

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

	unsigned int ind = vertices.size() / VERTEX_SIZE;

	Vec2f p1 = Transform.Apply({ -w / 2,  h / 2 });
	Vec2f p2 = Transform.Apply({ w / 2,  h / 2 });
	Vec2f p3 = Transform.Apply({ w / 2, -h / 2 });
	Vec2f p4 = Transform.Apply({ -w / 2, -h / 2 });

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

	unsigned int ind = vertices.size() / VERTEX_SIZE;

	Vec2f p1 = Transform.Apply({ 0,0 });

	DrawBorder(item);

	vertices.insert(vertices.end(), {
		p1.x, p1.y, 0.0f, r, g, b, 0,0
		});

	int count = 0;

	for (float i = 0; i < 6.28; i += num) {
		Vec2f p = Transform.Apply({ cos(i) * ra,sin(i) * ra });
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

void Renderer::Draw(const Text& txt)
{
	int orgX = txt.Transform.Position.x;
	int limitX = 1920;

	int lineHeight = txt.font.lineHeight;

	float x = orgX;
	float y = txt.Transform.Position.y;

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

		unsigned int ind = vertices.size() / VERTEX_SIZE;

		float u0 = ch.UV1.x;
		float v0 = ch.UV1.y;
		float u1 = ch.UV2.x;
		float v1 = ch.UV2.y;
		
		vertices.insert(vertices.end(), {
			xpos,     ypos + h, 0, r,g,b, u0, v1,
			xpos,     ypos,     0, r,g,b, u0, v0,
			xpos + w, ypos,     0, r,g,b, u1, v0,
			xpos + w, ypos + h, 0, r,g,b, u1, v1
			});

		indices.insert(indices.end(), {
			ind, ind + 1, ind + 2,
			ind, ind + 2, ind + 3
			});

		x += (ch.Advance >> 6);
	}

	glUniform1i(glGetUniformLocation(shader.ID, "shapeType"), -1);
	glActiveTexture(GL_TEXTURE0); // Activate slot 0
	glBindTexture(GL_TEXTURE_2D, txt.font.id); // Bind your loaded texture to slot 0

}

void Renderer::Draw(const UiBlock& item) {
	Draw(item.rect);
	Draw(item.text);
}

void Renderer::DrawBorder(const Object& item) {
	GLuint shapeTypeLoc = glGetUniformLocation(shader.ID, "shapeType");
	GLuint borderSize = glGetUniformLocation(shader.ID, "borderSize");;
	GLuint borderColorLoc = glGetUniformLocation(shader.ID, "borderColor");
	glBindTexture(GL_TEXTURE_2D, 0);

	auto [r, g, b, a] = item.Border.Color;

	glUniform1i(shapeTypeLoc, item.ShapeType);
	glUniform1f(borderSize, item.Border.Thickness);
	glUniform3f(borderColorLoc, r, g, b);
}