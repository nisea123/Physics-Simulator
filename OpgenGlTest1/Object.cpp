#include "Object.h"
#include "Renderer.h"

void Triangle::Draw(Renderer& renderer) {
	renderer.Draw(*this);
}

void Rectangle::Draw(Renderer& renderer) {
	renderer.Draw(*this);
}

void Circle::Draw(Renderer& renderer) {
	renderer.Draw(*this);
}

void Line::Draw(Renderer& renderer) {
	renderer.Draw(*this);
}

void Arrow::Draw(Renderer& renderer) {
	renderer.Draw(*this);
}
