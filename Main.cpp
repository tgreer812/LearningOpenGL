#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "Utils.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture2D.h"
#include "Camera.h"

bool wireframe = false;

void toggleWireframeHandler(GLFWwindow* window, int key, int scancode, int action, int mods) {
	
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

// To do this properly we need to implement an event system (i.e pub/sub pattern)
// but for now we are going to do it the gross way of just using a global
Camera* activeCamera = nullptr;

void handleMovementInput(int key, int scancode, int action, int mods) {
	
	//temporary
	if (activeCamera == nullptr) { std::cout << "No camera set!\n";  return; }

	// Only process key down events
	if (!(action == GLFW_PRESS || action == GLFW_REPEAT)) { return; }

	//glm::mat3 movement
	switch (key) {
		case GLFW_KEY_W:
			activeCamera->Move(glm::vec3(0.0f, 0.0f, 1.0f));
			break;
		case GLFW_KEY_A:
			activeCamera->Move(glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case GLFW_KEY_S:
			activeCamera->Move(glm::vec3(0.0f, 0.0f, -1.0f));
			break;
		case GLFW_KEY_D:
			activeCamera->Move(glm::vec3(-1.0f, 0.0f, 0.0f));
			break;
	}
}

// temporary way of handling events
void handleKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (key) {
		case GLFW_KEY_X:
			toggleWireframeHandler(window, key, scancode, action, mods);
			break;
		case GLFW_KEY_W:
		case GLFW_KEY_A:
		case GLFW_KEY_S:
		case GLFW_KEY_D:
			handleMovementInput(key, scancode, action, mods);
			break;
		default:
			break;
	}
}

GLFWwindow* Window;
int windowHeight = 800;
int windowWidth = 800;

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
	Window = glfwCreateWindow(windowHeight, windowWidth, "mytriangle", NULL, NULL);
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

	glfwSetKeyCallback(Window, handleKeyEvent);
}

int main()
{
	init();

	// Load shaders
	std::string vertexShaderSource = "C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\Resources\\VertexShader.glsl";
	std::string inputColorFragmentShaderSource = "C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\Resources\\FragmentShaderInputColor.glsl";
	std::string textureShaderSource = "C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\Resources\\FragmentTextureShader.glsl";

	Shader TextureShader = Shader(vertexShaderSource, textureShaderSource);

	Texture2D testTexture = Texture2D("C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\Resources\\FlatMarbleTexture.png");

	// Define vertices and indices
	float plane_vertices[] = {
		// positions		// colors			// texture coords
		0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,		// top right
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,		// bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	0.0f, 0.0f,		// bottom left
		-0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f		// top left
	};

	unsigned int indices[] = {
		0, 1, 2,	// Triangle 1
		0, 2, 3		// Triangle 2
	};

	Camera camera = Camera();
	activeCamera = &camera;

	// Create the vertex array object with the correct number of elements (not bytes)
	VertexArray va = VertexArray(plane_vertices, sizeof(plane_vertices), indices, sizeof(indices));

	// Graphics loop
	while (!glfwWindowShouldClose(Window)) {
		// Clear the screen with the background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		constexpr float model_rotation = glm::radians(-1.0f);
		//model_matrix = glm::rotate(model_matrix, model_rotation, glm::vec3(1.0f, 1.0f, 1.0f));

		TextureShader.setMatrix4("modelMatrix", camera.GetModelMatrix());
		TextureShader.setMatrix4("viewMatrix", camera.GetViewMatrix());
		TextureShader.setMatrix4("projectionMatrix", camera.GetProjectionMatrix());

		// Use the shader program
		TextureShader.Use();

		// Bind the texture and set the texture uniform
		testTexture.Bind();
		TextureShader.setInt("ourTexture", 0); // 0 corresponds to GL_TEXTURE0

		// Bind the vertex array object
		va.Use();

		// Draw the rectangle
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap buffers and poll events
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}

	// Cleanup/exit
	glfwTerminate();
	std::cout << "Exiting cleanly\n";
	return 0;
}