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
#include "TextRenderer.h"
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

	//Makes a window 800x800
	unsigned int width = 1920;
	unsigned int height = 1080;

	GLFWwindow* window = glfwCreateWindow(width, height, "First OpenGl", NULL, NULL);

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
	Shader shaderProgram("default.vert", "default.frag");

	Renderer renderer(shaderProgram);

	Rectangle block({ 1.0f, 1.0f }, { 0.0f, 0.0f });

	Circle circ(1, { 0.0f,0.0f });
	
	Triangle trig({ 1.f,1.f }, { 0.0f,0.0f });

	Font font("OpenSans.ttf");
	Text txt(font);

	Text counter(font);
	counter.Transform.Position = { width / 2.f, 1000};

	UiBlock click(font,{200.f,200.f},{width/ 2.f,1000});
	click.text.Content = "Spawn Square";
	click.rect.Color = { 0.f,0.f,0.f,1.f };
		
	float i = 0;

	static auto last = chrono::high_resolution_clock::now();
	auto now = chrono::high_resolution_clock::now();
	float deltaTime = chrono::duration<float>(now - last).count();

	txt.Transform.Position = { width / 2.f, height / 2.f };

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Main while loop
	while (!glfwWindowShouldClose(window)) {

		i += .1;


		now = chrono::high_resolution_clock::now();
		deltaTime = chrono::duration<float>(now - last).count();

		renderer.Clear();
		//glBindTexture(GL_TEXTURE_2D, atlas);

		glUniformMatrix4fv(
			glGetUniformLocation(shaderProgram.ID, "projection"),
			1,
			GL_FALSE,
			&proj[0][0]
		);
		
		txt.Content = "In the beginning, the two nations lived at peace,until the evil forces emerged from the depths of hell";
		counter.Content = to_string(deltaTime);
		renderer.Draw(click.rect);
		renderer.Draw(txt);
		renderer.Draw(counter);
		

		//cout << click.rect.Transform.Position.y << endl;

		renderer.Render();

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