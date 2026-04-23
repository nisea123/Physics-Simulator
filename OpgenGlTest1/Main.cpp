#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "Object.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

using namespace std;

GLfloat vertices[] =
{
	// position				// color

	-0.5f, -0.5f, 0.0f,	 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f,	 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, 0.0f,	 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, 0.0f,  1.0f, 1.0f ,1.0f
};

GLuint indices[] = {
	0, 2, 1,
	0, 3 ,2
};

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
	GLFWwindow* window = glfwCreateWindow(800,800,"First OpenGl", NULL, NULL);


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

	// Creates the VBO and EBO	
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Links them
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Square square({ 1.f,1.f }, { 0.f,0.f });

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//Main while loop
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.08f, 0.13f, 0.17f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		shaderProgram.Activate();
		glUniform1f(uniID, -.5f);

		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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