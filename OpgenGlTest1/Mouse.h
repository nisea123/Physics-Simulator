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
	Vec2f worldPosition;
	std::deque<Vec2f> dragHistory;

	float a = 0.f;
	float t = .1f; // Time window for drag history in seconds

	float scrollDelta = 0.f;
	float scrollSensitivity = 1.f;
	float scrollDampen = 0.5f;

	float throwStrength = 1.5f;

	bool m1 = false;
	bool m1Prev = false;
	bool m1Pressed = false;

	Mouse() {
		glfwSetWindowUserPointer(glfwGetCurrentContext(), this);
	}

	static void ScrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {
		Mouse* mouse = static_cast<Mouse*>(glfwGetWindowUserPointer(window));
		if (!mouse) return;

		mouse->scrollDelta = (float)yoffset;
	}
	void Update(GLFWwindow* window, Vec2f screenSize, float dt,Camera& camera) {
		scrollDelta *= scrollDampen; // Dampen the scroll delta to make zooming smoother.
		m1Prev = m1;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		y = screenSize.y - y;

		lastPosition = position;
		position = Vec2f((float)x,(float)y);
		worldPosition = camera.ScreenToWorld(position, screenSize); // Transforms the mouse position from screen space to world space using the camera's transformation.

		dragHistory.push_back(position - lastPosition);
		a += dt;

		if (a > t) dragHistory.pop_front();

		m1 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
		m1Pressed = m1 && !m1Prev;

		glfwSetScrollCallback(window, ScrollCallBack);
		camera.zoom = camera.zoom * powf(1.1f,scrollDelta * scrollSensitivity);
	}

	Vec2f GetDragDistance() {
		Vec2f newDrag(0);
		for (const Vec2f& drag : dragHistory) {
			newDrag += drag;
		}
		return newDrag;
	}
};