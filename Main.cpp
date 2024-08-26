#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Utils.h"
#include "Shader.h"

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

int main()
{
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window to draw on
	GLFWwindow *mywindow = glfwCreateWindow(800, 800, "mytriangle", NULL, NULL);
	if (mywindow == NULL) {
		std::cout << "Failed to create window!\n";
		glfwTerminate();
		return -1;
	}

	// Makes this window the current context for graphical operations.
	// Without doing this, openGL calculates what to do graphically, but
	// doesn't know where to apply it. This makes sense when you think of the
	// 'pipeline' like nature of graphics rendering, and the fact that
	// you could write a program that creates multiple windows.
	glfwMakeContextCurrent(mywindow);

	// Initialize open GL using glad
	gladLoadGL();

	// create a viewport
	glad_glViewport(0, 0, 800, 800);

	glfwSetKeyCallback(mywindow, toggleWireframe);

	std::string vertexShaderSource = std::string("C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\VertexShader.glsl");
	std::string fragmentShaderSource = std::string("C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\FragmentShader.glsl");
	std::string fragmentShaderSource2 = std::string("C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\FragmentShader2.glsl");

	Shader OrangeShader = Shader(vertexShaderSource, fragmentShaderSource);
	Shader YellowShader = Shader(vertexShaderSource, fragmentShaderSource2);
	
	GLuint ShaderProgram1 = OrangeShader.GetShaderProgram();
	GLuint ShaderProgram2 = YellowShader.GetShaderProgram();

	GLfloat vertices[] = {
		// Position
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	GLfloat vertices2[] = {
		-0.5f, -0.5f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f
	};

	GLuint VAO1, VBO1, VAO2, VBO2;
	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);

	// what is the point of this??
	glBindVertexArray(VAO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);

	// what is the point of this??
	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Graphics loop
	while (!glfwWindowShouldClose(mywindow)) {
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(ShaderProgram1);
		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(ShaderProgram2);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(mywindow);
		glfwPollEvents();
	}

	// Cleanup/exit
	glfwTerminate();
	std::cout << "Exiting cleanly\n";
	return 0;
}