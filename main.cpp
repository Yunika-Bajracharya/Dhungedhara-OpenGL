#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


int main() {

	// Initialize GLFW
	glfwInit();

	// Tell GLFW the version of OpenGL we are using (here 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW: we are using CORE profile that contains only modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Coordinates of vertices
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower left
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // top
		-0.5 / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // inner down
	};

	GLuint indices[] = {
		0, 3, 5, // lower left triangle
		3, 2, 4,  // top
		5, 4, 1 // lower right
	};

	// Create GLFW window object of 800*800 pixels
	GLFWwindow* window = glfwCreateWindow(800, 800, "Dhungedhara", NULL, NULL);

	// If window failed to create
	if (window == NULL) {
		std::cout << "Unable to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce window into current context
	glfwMakeContextCurrent(window);

	// Load glad to configure OpenGL
	gladLoadGL();

	// Specify viewport of OpenGL in the window
	// Here viewport goes from (bottom left) x = 0, y = 0 to (top right) x = 800, y = 800
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Main while loop
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell openGL which shader program to use
		shaderProgram.Activate();
		// Bind VAO so OpenGL knows how to use it
		VAO1.Bind();
		// Draw triangle using GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Handle all GLFW events
		// To make the window responsive (eg. resizing)
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Delete window before ending program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending program
	glfwTerminate();
	return 0;
}