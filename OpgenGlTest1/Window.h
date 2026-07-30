#pragma once

#include<GLFW/glfw3.h>
#include "Camera.h"

class Window {
public:
	GLFWwindow* window = NULL;
	Camera camera;
	std::unique_ptr<Renderer> renderer;

	Window(unsigned int width, unsigned int height, const char* name) {
		
		window = glfwCreateWindow(width, height, name, NULL, NULL);

		glfwMakeContextCurrent(window);
			
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cerr << "Failed to initialize GLAD" << std::endl;
			glfwTerminate();
		}

		renderer = std::unique_ptr<Renderer>(new Renderer(camera));
	}
};