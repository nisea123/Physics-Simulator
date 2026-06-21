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

	scene.objects.SpawnWorld<Circle>(400.f,Vec2f{ width / 2.f, height / 2.f });
	Arrow* arrow = scene.objects.SpawnWorld<Arrow>(Vec2f(0, 0), Vec2f(width / 2.f, height / 2.f), 20);
	//Arrow* arrow1 = scene.objects.SpawnWorld<Arrow>(Vec2f(width, height), Vec2f(width / 2.f, height / 2.f), 200);
		
	float i = 0;

	static auto last = chrono::high_resolution_clock::now();
	auto now = chrono::high_resolution_clock::now();
	float deltaTime = chrono::duration<float>(now - last).count();

	Object* selectedObject = nullptr;
	Object* holdingObject = nullptr;
	Object* hoveredObject = nullptr;

	UiElement* hoveredUi = nullptr;

	Object* holdingGizmo = nullptr;
	Object* hoveredGizmo = nullptr;

	bool checked = false;

	//Main while loop
	while (!glfwWindowShouldClose(window)) {
		i += .1f;

		now = chrono::high_resolution_clock::now();
		deltaTime = chrono::duration<float>(now - last).count();

		renderer.Clear();
		int w, h;
		glfwGetFramebufferSize(window, &w, &h);
		//glBindTexture(GL_TEXTURE_2D, atlas);

		mouse.Update(window, h);
		//arrow->Visible = !arrow->Visible;
		//arrow->End = mouse.position;
		hoveredObject = nullptr;
		hoveredUi = nullptr;
		hoveredGizmo = nullptr;

		for (auto& ui : scene.ui.ui)
		{
			if (ui->Contains(mouse.position))
			{
				hoveredUi = ui.get();
			}
		}

		if (!hoveredUi) {
			for (auto& object : scene.objects.objects)
			{
				if (object->Contains(mouse.position))
				{
					hoveredObject = object.get();
					break;
				}
			}
			for (GizmoHandle& handle : scene.gizmo.handles) {
				Object* o = handle.Visual.get();
				if (o->Contains(mouse.position)) {
					hoveredGizmo = o;
					
				}
			}
		}

		if (mouse.m1Pressed)
		{
			if (hoveredUi) {
				if (hoveredUi->OnClick) {
					hoveredUi->OnClick();
				}
			}
			else if (hoveredObject) {
				selectedObject = hoveredObject;
				holdingObject = hoveredObject;
				mouse.dragOffset = mouse.position - holdingObject->Transform.Position;
			}
			else if (!hoveredObject && !hoveredGizmo) {
				selectedObject = nullptr;
			}
		}
		
		if(mouse.m1 && holdingObject){
			holdingObject->Transform.Position = mouse.position - mouse.dragOffset;
		}

		if (selectedObject) {
			scene.gizmo.target = selectedObject;
			scene.gizmo.Show();
		}
		else {
			scene.gizmo.Hide();
		}

		if (!mouse.m1) {
			holdingObject = nullptr;
		}

		if (hoveredGizmo) {
			if (Arrow* arr = dynamic_cast<Arrow*>(hoveredGizmo)) {
				ArrowDesc desc = toArrowDesc(arr, arr->Thickness * 1.5f);
				renderer.DrawArrow(desc);
			}
		}

		for (auto& object : scene.objects.objects) {
			Object* o = object.get();

			if (!o->Visible) continue;

			if (auto* r = dynamic_cast<Rectangle*>(o))
				renderer.Draw(*r);

			else if (auto* c = dynamic_cast<Circle*>(o))
				renderer.Draw(*c);
			else if (auto* t = dynamic_cast<Triangle*>(o))
				renderer.Draw(*t);
			else if (auto* n = dynamic_cast<Arrow*>(o))
				renderer.Draw(*n);
			else if (auto* p = dynamic_cast<Line*>(o))
				renderer.Draw(*p);
		}
		for (auto& object : scene.ui.ui) {
			UiElement* o = object.get();

			if (!o->Visible) continue;

			if (auto* r = dynamic_cast<UiFrame*>(o))
				renderer.Draw(*r);
			else if (auto* c = dynamic_cast<UiButton*>(o))
				renderer.Draw(*c);
			else if (auto* t = dynamic_cast<UiSlider*>(o))
				renderer.Draw(*t);
			else if (auto* y = dynamic_cast<UiText*>(o))
				renderer.Draw(*y);
		}

		for (GizmoHandle& handle : scene.gizmo.handles) {
			Object* o = handle.Visual.get();

			if (!o->Visible) continue;

			if (auto* arrow = dynamic_cast<Arrow*>(o)) {
				renderer.Draw(*arrow);
			}

		}

		//txt.Content = "In the beginning, the two nations lived at peace,until the evil forces emerged from the depths of hell";
		//counter.Content = to_string(deltaTime);

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