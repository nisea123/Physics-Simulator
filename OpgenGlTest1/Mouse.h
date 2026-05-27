#pragma once

#include "Structs.h"
#include<GLFW/glfw3.h>

class Mouse
{
public:
	Vec2f position;
	Vec2f dragOffset;
	bool m1 = false;
	bool m1Prev = false;
	bool m1Pressed = false;

	void Update(GLFWwindow* window, unsigned int height) {
		m1Prev = m1;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		y = height - y;

		position = { (float)x,(float)y };
		m1 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
		m1Pressed = m1 && !m1Prev;
	}
};