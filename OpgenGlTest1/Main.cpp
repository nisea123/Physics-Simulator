#include<iostream>
#include <vector>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "Object.h"
#include "Renderer.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

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
	GLFWwindow* window = glfwCreateWindow(800, 800, "First OpenGl", NULL, NULL);


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
	glViewport(0, 0, 800, 800);

	// Creating the vertex shader
	Shader shaderProgram("default.vert", "default.frag");

	// Creates the VAO
	VAO VAO1;
	VAO1.Bind();

	Renderer renderer;

	constexpr float TAU = 6.28318530718f;
	int count = 64;
	float step = TAU / count;


	Circle circle(step / 10, { 0.0f, 0.0f });

	Square floor({ 4.0f,1.0f }, { 0.0f,-1.5f });

	Square block({ 2.0f, 1.0f }, { 0.0f, 1.f });

	vector<Circle> circArr;

	for (int a = 0; a < count; a += 1) {
		Circle x(step / 5, { 0.0f, 0.0f });
		circArr.push_back(x);
	}
	
	// Creates the VBO and EBO	
	VBO VBO1(&renderer.vertices);
	EBO EBO1(&renderer.indices);

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	float i = 0;

	//Main while loop
	while (!glfwWindowShouldClose(window)) {

		i += .01;

		glClearColor(0.08f, 0.13f, 0.17f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		shaderProgram.Activate();
		glUniform1f(uniID, -.5f);

		renderer.Clear();

		//circle.Position = { cos(angle),sin(angle) };
		//circle.Rotation += i;
		
		//floor.Rotation += i;

		for (int a = 0; a < count; a++) {
			circArr[a].Position = {cos(a - i),sin(a - i) };
			circArr[a].Rotation = tan(i);
			renderer.Draw(circArr[a]);
		}

		//block.Rotation = i;

		//renderer.Draw(block);

		//renderer.Draw(floor);
		//renderer.Draw(circle);
		
		VAO1.Bind();

		VBO1.Bind();
		glBufferData(GL_ARRAY_BUFFER, renderer.vertices.size() * sizeof(GLfloat), renderer.vertices.data(), GL_DYNAMIC_DRAW);

		EBO1.Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, renderer.indices.size() * sizeof(GLuint), renderer.indices.data(), GL_DYNAMIC_DRAW);

		glDrawElements(GL_TRIANGLES, renderer.indices.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		//Gets events like mouse,keyboard etc
		glfwPollEvents();
	}
	
	// Deletes them
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}