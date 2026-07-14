#include<iostream>
#include <vector>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <chrono>
#include <math.h>
#include <map>

#include "shaderClass.h"
#include "Object.h"
#include "Renderer.h"
#include "Mouse.h"
#include "Scene.h"
#include "ObjectCast.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

int main() {

	//Initialize GLFW
	glfwInit();

	//Specifies the version of the glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Tells glfw the core version we are using
	//Means we only use modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Makes a window
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	unsigned int width = mode->width;
	unsigned int height = mode->height;

	GLFWwindow* window = glfwCreateWindow(width, height, "Physics Engine", NULL, NULL);

	glm::mat4 proj = glm::ortho(
		0.0f, (float)width,
		0.0f, (float)height,   // flipped Y
		-1.0f, 1.0f
	);

	//Error if the window cant be created
	if (window == NULL) {
		cerr << "Failed to create a window" << endl;
		glfwTerminate();
		return -1;
	}

	//Introduces the window into the current context
	glfwMakeContextCurrent(window);

	//Loads glad so it configures opengl
	gladLoadGL();

	//Specifies the position and size of the viewport
	glViewport(0, 0, width, height);

	// Creating the vertex shader
	Shader ObjectShaderProgram("default.vert", "default.frag");
	Shader TextShaderProgram("text.vert", "text.frag");

	Renderer renderer(ObjectShaderProgram,TextShaderProgram);

	Mouse mouse;

	Scene scene;

//	scene.objects.SpawnWorld<Circle>(400.f,Vec2f{ width / 2.f, height / 2.f });
	//Arrow* arrow = scene.objects.SpawnWorld<Arrow>(Vec2f(0, 0), Vec2f(width / 2.f, height / 2.f), 20);
	//Arrow* arrow1 = scene.objects.SpawnWorld<Arrow>(Vec2f(width, height), Vec2f(width / 2.f, height / 2.f), 200);
	Arc* arc = scene.objects.SpawnWorld<Arc>(Vec2f{ width / 2.f, height / 2.f });
	arc->Visible = false;
		
	float i = 0;

	static auto last = chrono::high_resolution_clock::now();
	auto now = chrono::high_resolution_clock::now();
	float deltaTime = chrono::duration<float>(now - last).count();

	bool checked = false;

	//Main while loop
	while (!glfwWindowShouldClose(window)) {
	//	i += .001f;

		now = chrono::high_resolution_clock::now();
		deltaTime = chrono::duration<float>(now - last).count();

		renderer.Clear();
		int w, h;
		glfwGetFramebufferSize(window, &w, &h);
		//glBindTexture(GL_TEXTURE_2D, atlas);

		mouse.Update(window, h);
		//arc->Transform.Rotation.radians -= Angle::Radians(.0001f).AsRadians();
		scene.Update(mouse);
		scene.Draw(renderer);

		renderer.Render(proj);

		glfwSwapBuffers(window);

		//Gets events like mouse,keyboard etc
		glfwPollEvents();
	}
	
	// Deletes them
	renderer.Destroy();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}