#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Utils.h"
#include "Shader.h"
#include "VertexArray.h"

bool wireframe = false;

void toggleWireframe(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key != GLFW_KEY_X) { return; }
	if (action != GLFW_RELEASE) { return; }

	if (wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	wireframe = !wireframe;
}

GLFWwindow* Window;

void init() {
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window to draw on
	Window = glfwCreateWindow(800, 800, "mytriangle", NULL, NULL);
	if (Window == NULL) {
		std::cout << "Failed to create window!\n";
		glfwTerminate();
		exit(-1);
	}

	// Makes this window the current context for graphical operations.
	// Without doing this, openGL calculates what to do graphically, but
	// doesn't know where to apply it. This makes sense when you think of the
	// 'pipeline' like nature of graphics rendering, and the fact that
	// you could write a program that creates multiple windows.
	glfwMakeContextCurrent(Window);

	// Initialize open GL using glad
	gladLoadGL();

	// create a viewport
	glad_glViewport(0, 0, 800, 800);

	glfwSetKeyCallback(Window, toggleWireframe);
}

int main()
{
	init();

	// Load shaders
	std::string vertexShaderSource = "C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\VertexShader.glsl";
	std::string inputColorFragmentShaderSource = "C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\FragmentShaderInputColor.glsl";
	Shader InputColorShader = Shader(vertexShaderSource, inputColorFragmentShaderSource);

	// Define vertices and indices
	float vertices[] = {
		// Positions         // Colors (RGB)
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Vertex 1: Red
		 0.0f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Vertex 2: Green
		 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Vertex 3: Blue
	};

	unsigned int indices[] = {
		0, 1, 2  // Triangle
	};

	// Create the vertex array object with the correct number of elements (not bytes)
	VertexArray va = VertexArray(vertices, sizeof(vertices), indices, sizeof(indices));

	// Graphics loop
	while (!glfwWindowShouldClose(Window)) {
		// Clear the screen with the background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use the shader program
		InputColorShader.Use();

		// Bind the vertex array object
		va.Use();

		// Draw the triangle
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		// Swap buffers and poll events
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}

	// Cleanup/exit
	glfwTerminate();
	std::cout << "Exiting cleanly\n";
	return 0;
}