#include<iostream>
#include <vector>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <chrono>
#include <math.h>

#include "Object.h"
#include "Scene.h"
#include "ObjectCast.h"
#include "Window.h"
#include "UiElements.h"
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

	window.camera.position = Vec2f(width / 2.f, height / 2.f);

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
	
	Rectangle* obstacle2 = scene.objects.SpawnPhysicsObject<Rectangle>(Vec2f(100.f, 100.f), Vec2f(width / 2.f, height / 2.f));

	float textOffset = width / 10.f;
	float textOffsetY = 100.f;

	//Text txt(renderer.fontManager.GetDefaultFont());
	//txt.Transform.Position = Vec2f(width / 2.f, textOffsetY);
	Camera& cam = window.camera;
	Mouse& mouse = scene.mouse;

	Tracker xPos(renderer.fontManager.GetDefaultFont(), cam.position.x, "Camera X : ", "");
	xPos.Transform.Position = UDim2(0,0,textOffset, height - textOffsetY);

	Tracker yPos(renderer.fontManager.GetDefaultFont(), cam.position.y, "Camera Y : ", "");
	yPos.Transform.Position = UDim2(0,0,textOffset, height - textOffsetY * 2);
	
	Tracker mousePosX(renderer.fontManager.GetDefaultFont(), mouse.worldPosition.x, "Mouse X : ", "");
	mousePosX.Transform.Position = UDim2(0,0,textOffset, height - textOffsetY * 3);

	Tracker mousePosY(renderer.fontManager.GetDefaultFont(), mouse.worldPosition.y, "Mouse Y : ", "");
	mousePosY.Transform.Position = UDim2(0,0,textOffset, height - textOffsetY * 4);

	Tracker obstaclePosX(renderer.fontManager.GetDefaultFont(),obstacle2->Transform.Position.x,"Obstacle X : ","");
	obstaclePosX.Transform.Position = UDim2(0,0,textOffset, height - textOffsetY * 5);

	Tracker obstaclePosY(renderer.fontManager.GetDefaultFont(), obstacle2->Transform.Position.y, "Obstacle Y : ", "");
	obstaclePosY.Transform.Position = UDim2(0,0,textOffset, height - textOffsetY * 6);

	Tracker cameraZoom(renderer.fontManager.GetDefaultFont(), cam.zoom.x, "Camera Zoom", "");
	cameraZoom.Transform.Position = UDim2(0,0,textOffset, height - textOffsetY * 7);

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
		float zoom = window.camera.zoom.x;
		glfwGetFramebufferSize(window.window, &w, &h);
		Vec2f screenSize = Vec2f(w, h);
		//glBindTexture(GL_TEXTURE_2D, atlas);
		
		//arc->Transform.Rotation.radians -= Angle::Radians(.0001f).AsRadians();
		//cout << deltaTime << endl;
	/*	while (num < 100) {
			scene.objects.SpawnPhysicsObject<Rectangle>(Vec2f(100.f, 100.f), Vec2f(width / 2.f, height / 2.f));
			num += 1;
		}
		txt.Content = "Number of objects : " + to_string(num);
		*/
		proj = glm::ortho(
			cam.position.x - (float)w / (2 * zoom), cam.position.x + (float)w / (2 * zoom),
			cam.position.y - (float)h / (2 * zoom), cam.position.y + (float)h / (2 * zoom),   // flipped Y
			-1.0f, 1.0f
		);

		scene.mouse.Update(window.window, screenSize, deltaTime,window.camera);
		scene.Update(deltaTime);
		scene.Draw(renderer);
		//renderer.Draw(txt);
		renderer.Draw(xPos);
		renderer.Draw(yPos);
		renderer.Draw(mousePosX);
		renderer.Draw(mousePosY);
		renderer.Draw(obstaclePosX);
		renderer.Draw(obstaclePosY);
		renderer.Draw(cameraZoom);

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