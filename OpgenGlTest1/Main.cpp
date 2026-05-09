#include<iostream>
#include <vector>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <math.h>
#include <algorithm>

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

	Renderer renderer(shaderProgram);

	constexpr float TAU = 6.28318530718f;
	int count = 64;
	float step = TAU / count;

	Rectangle block({ 1.0f, 1.0f }, { 0.0f, 0.0f });

	Circle circ(1, { 0.0f,0.0f });

	//vector<Circle> circArr;

	//for(int i = 0;i < count;i++){
	//	Circle circ(step, { 0.0f,0.0f });
	//	circ.Transform.Scale = { .1f,.1f };
	//	circArr.push_back(circ);
	//}
	
	Triangle trig({ 1.f,1.f }, { 0.0f,0.0f });
	
	// Creates the VBO and EBO	
	VBO VBO1(&renderer.vertices);
	EBO EBO1(&renderer.indices);

	glDisable(GL_DEPTH_TEST);
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint borderLoc = glGetUniformLocation(shaderProgram.ID, "borderSize");
	GLuint borderColorLoc = glGetUniformLocation(shaderProgram.ID, "borderColor");

	float i = 0;

	//Main while loop
	while (!glfwWindowShouldClose(window)) {

		i += .01;

		//glClearColor(0.08f, 0.13f, 0.17f, 1.f);
		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		shaderProgram.Activate();

		renderer.Clear();

		//for (float a = 0; a < count; a++) {
		//	float r = (sin(i) + 1.0f) * 0.5f;
		//	float g = (sin(i + 2.094f) + 1.0f) * 0.5f;
		//	float b = (sin(i + 4.188f) + 1.0f) * 0.5f;
		//	circArr[a].Transform.Position = {1/tan(a+i),cos(sin(a+i))};
		//	//circArr[a].Transform.Rotation = i;
		//	circArr[a].Color = {r,g,b};
		//	renderer.Draw(circArr[a]);
		//}

		//renderer.Draw(circ);
		//renderer.Draw(trig);

		renderer.Draw(block);
		
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