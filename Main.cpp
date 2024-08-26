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
	std::string uniformFragmentShaderSource = std::string("C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\FragmentShaderUniform.glsl");
	std::string inputColorFragmentShaderSource = std::string("C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\FragmentShaderInputColor.glsl");

	// Shader OrangeShader = Shader(vertexShaderSource, fragmentShaderSource);
	// Shader YellowShader = Shader(vertexShaderSource, fragmentShaderSource2);
	// Shader UniformShader = Shader(vertexShaderSource, uniformFragmentShaderSource);
	Shader InputColorShader = Shader(vertexShaderSource, inputColorFragmentShaderSource);

	// box
	//GLfloat vertices[] = {
	//	// Position				// Color RGB
	//	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
	//	-0.5f,  0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	//	 0.0f,  0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	//	 0.0f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f
	//};

	GLfloat vertices[] = {
		// Position				// Color RGB
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,
	};

	//unsigned int indices[] = {
	//	0, 1, 2,	// first triangle
	//	0, 2, 3		// second triangle
	//};

	//unsigned int indices[] = {
	//	0, 1, 2
	//};

	GLuint VAO, VBO;
	//GLuint VAO, VBO, EBO;

	// Generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Bind vertex array object first so that it can store the EBO
	// binding just tells it to use this as the primary VAO
	glBindVertexArray(VAO);

	// Bind and copy the vertices into the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the EBO and copy the indices into it
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// Now set all the vertex attribute pointers
	// Essentially this just goes through the different attributes, telling opengl where they are in the VAO
	// and then turns them on with the enable call
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Graphics loop
	while (!glfwWindowShouldClose(mywindow)) {
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		//YellowShader.Use();
		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(UniformShader.GetShaderProgram(), "customColor");
		InputColorShader.Use();
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(mywindow);
		glfwPollEvents();
	}

	// Cleanup/exit
	glfwTerminate();
	std::cout << "Exiting cleanly\n";
	return 0;
}