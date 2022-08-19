#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // top
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

	// Create Vertex Shader object & get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach vertex shader source to vetex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Complie vetex shader into machine code
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Create Shader Program object & get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach vertex and fragment shaders to shader programs
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Link all shaders together to shader program
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Create reference containers for Vertex Array Object, Vertex Buffer Object
	GLuint VAO, VBO;

	// Generate VAO, VBO with 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make VAO current VAO by binding it
	glBindVertexArray(VAO);

	// Bind VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce vertices into VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure vertex attribute so that OpenGL knows how to read VBO
	// Vertex Attribute is a way of communicating with vertex shader from outside.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable vertex attribute so that OpenGL knows how to use it
	glad_glEnableVertexAttribArray(0);

	// Bind VBO & VAO to 0 so that we don't accidentally modify them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Specify color of background in decimal rgba form
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean back buffer & assign new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap back buffer with the front buffer
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell openGL which shader program to use
		glUseProgram(shaderProgram);
		// Bind VAO so OpenGL knows how to use it
		glBindVertexArray(VAO);
		// Draw triangle using GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		// Handle all GLFW events
		// To make the window responsive (eg. resizing)
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Delete window before ending program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending program
	glfwTerminate();
	return 0;
}