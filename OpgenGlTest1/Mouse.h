#pragma once

#include "Structs.h"
#include<GLFW/glfw3.h>
#include <deque>
#include "Camera.h"

class Mouse
{
public:
	Vec2f position;
	Vec2f lastPosition;
	std::deque<Vec2f> dragHistory;

	float a = 0.f;
 	float t = .1f;

	float throwStrength = 1.5f;

	bool m1 = false;
	bool m1Prev = false;
	bool m1Pressed = false;

	void Update(GLFWwindow* window, unsigned int height, float dt,Camera& camera) {
		m1Prev = m1;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		y = height - y;

		lastPosition = position;
		position = Vec2f((float)x,(float)y) + camera.position;

		dragHistory.push_back(position - lastPosition);
		a += dt;

		if (a > t) dragHistory.pop_front();

		m1 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
		m1Pressed = m1 && !m1Prev;
	}

	Vec2f GetDragDistance() {
		Vec2f newDrag(0);
		for (const Vec2f& drag : dragHistory) {
			newDrag += drag;
		}
		return newDrag;
	}
};