#include<iostream>
#include <vector>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <chrono>
#include <math.h>

#include "shaderClass.h"
#include "Object.h"
#include "Renderer.h"
#include "Mouse.h"
#include "Scene.h"
#include "ObjectCast.h"
#include "Window.h"
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

	Window window(width, height, "Physics Engine");

	glm::mat4 proj = glm::ortho(
		0.0f, (float)width,
		0.0f, (float)height,   // flipped Y
		-1.0f, 1.0f
	);

	//Error if the window cant be created
	if (window.window == NULL) {
		cerr << "Failed to create a window" << endl;
		glfwTerminate();
		return -1;
	}

	//Introduces the window into the current context
	glfwMakeContextCurrent(window.window);

	//Loads glad so it configures opengl
	gladLoadGL();

	//Specifies the position and size of the viewport
	glViewport(0, 0, width, height);
	//glfwSwapInterval(1);

	// Creating the vertex shaders

	Renderer& renderer = *window.renderer;

	Scene scene(renderer.fontManager, window.camera);

//	scene.objects.SpawnWorld<Circle>(400.f,Vec2f{ width / 2.f, height / 2.f });
	Rectangle* base = scene.objects.SpawnPhysicsObject<Rectangle>(Vec2f(width, 200.f), Vec2f(width / 2.f, height / 10.f));
	base->Selectable = false;
	base->PhysicsBody->Anchored = true;

	Rectangle* obstacle = scene.objects.SpawnPhysicsObject<Rectangle>(Vec2f(200.f, 200.f), Vec2f(width / 5.f, height / 2.f));
	obstacle->Selectable = false;
	obstacle->PhysicsBody->Anchored = true;

	Text txt(renderer.fontManager.GetDefaultFont());
	txt.Transform.Position = Vec2f(width / 2.f, height / 1.2f);

	Text xPos(renderer.fontManager.GetDefaultFont());
	xPos.Transform.Position = Vec2f(width / 6.f, height / 1.2f);

	Text yPos(renderer.fontManager.GetDefaultFont());
	yPos.Transform.Position = Vec2f(width / 6.f, height / 1.3f);
		
	float i = 0;

	static auto last = chrono::high_resolution_clock::now();
	auto now = chrono::high_resolution_clock::now();
	float deltaTime = chrono::duration<float>(now - last).count();

	bool checked = false;
	int num = 0;

	//Main while loop
	while (!glfwWindowShouldClose(window.window)) {
	//	i += .001f;

		now = chrono::high_resolution_clock::now();
		deltaTime = chrono::duration<float>(now - last).count();
		last = now;
		renderer.Clear();
		int w, h;
		glfwGetFramebufferSize(window.window, &w, &h);
		//glBindTexture(GL_TEXTURE_2D, atlas);
		
		//arc->Transform.Rotation.radians -= Angle::Radians(.0001f).AsRadians();
		//cout << deltaTime << endl;
	/*	while (num < 100) {
			scene.objects.SpawnPhysicsObject<Rectangle>(Vec2f(100.f, 100.f), Vec2f(width / 2.f, height / 2.f));
			num += 1;
		}
		txt.Content = "Number of objects : " + to_string(num);
		*/

		xPos.Content = "Camera X : " + to_string(window.camera.position.x);
		yPos.Content = "Camera Y : " + to_string(window.camera.position.y);

		scene.mouse.Update(window.window, h, deltaTime,window.camera);
		scene.Update(deltaTime);
		scene.Draw(renderer);
		renderer.Draw(txt);
		renderer.Draw(xPos);
		renderer.Draw(yPos);

		renderer.Render(proj);

		glfwSwapBuffers(window.window);

		//Gets events like mouse,keyboard etc
		glfwPollEvents();
	}
	
	// Deletes them
	renderer.Destroy();
	glfwDestroyWindow(window.window);
	glfwTerminate();

	return 0;
}