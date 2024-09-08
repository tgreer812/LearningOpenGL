#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "Utils.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Plane.h"
#include "Renderer.h"

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

float deltaTime = 0.0f;
float lastFrameTime = 0.0f;

void handleMovementInput(int key, int scancode, int action, int mods) {
    // Temporary
    if (activeCamera == nullptr) { std::cout << "No camera set!\n";  return; }

    //if (!activeCamera.Enabled()) { return; }

    // Only process key down events
    if (!(action == GLFW_PRESS || action == GLFW_REPEAT)) { return; }

    // glm::mat3 movement
    switch (key) {
    case GLFW_KEY_W:
        activeCamera->Move(glm::vec3(0.0f, 0.0f, 1.0f), deltaTime);
        break;
    case GLFW_KEY_A:
        activeCamera->Move(glm::vec3(1.0f, 0.0f, 0.0f), deltaTime);
        break;
    case GLFW_KEY_S:
        activeCamera->Move(glm::vec3(0.0f, 0.0f, -1.0f), deltaTime);
        break;
    case GLFW_KEY_D:
        activeCamera->Move(glm::vec3(-1.0f, 0.0f, 0.0f), deltaTime);
        break;
    }
}

float lastXPos = 0.0f;
float lastYPos = 0.0f;
bool first = true;

void handleMouseEvent(GLFWwindow* window, double xpos, double ypos) {
    if (first) { lastXPos = xpos; lastYPos = ypos; first = false; return; }

    std::cout << "Rotating camera - x:" << xpos << " y:" << ypos << std::endl;
    activeCamera->Rotate(xpos - lastXPos, ypos - lastYPos);
    lastXPos = xpos;
    lastYPos = ypos;

    // print out camera details
    std::cout << "Projection Matrix:" << std::endl;
    Utils::printMat4(activeCamera->GetProjectionMatrix());

    std::cout << "View Matrix:" << std::endl;
    Utils::printMat4(activeCamera->GetViewMatrix());
}

// Temporary way of handling events
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
    Window = glfwCreateWindow(windowHeight, windowWidth, "my graphics engine", NULL, NULL);
    if (Window == NULL) {
        std::cout << "Failed to create window!\n";
        glfwTerminate();
        exit(-1);
    }

    // Makes this window the current context for graphical operations.
    glfwMakeContextCurrent(Window);

    // Initialize open GL using glad
    gladLoadGL();

    // Create a viewport
    glad_glViewport(0, 0, 800, 800);

    // Handle key presses
    glfwSetKeyCallback(Window, handleKeyEvent);

    // Handle mouse movement
    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(Window, handleMouseEvent);
}

std::vector<float> CreateInterleavedVertexBuffer(
    const std::vector<float>& vertexPositions,
    const std::vector<float>& vertexColors,
    const std::vector<float>& textureCoords)
{
    std::vector<float> interleavedBuffer;

    // Ensure all vectors are the same length (in terms of number of vertices)
    size_t numVertices = vertexPositions.size() / 3; // 3 floats per position
    if (vertexColors.size() / 3 != numVertices || textureCoords.size() / 2 != numVertices) {
        throw std::runtime_error("Mismatch in vertex data sizes.");
    }

    // Interleave the data: position (3 floats), color (3 floats), texture coord (2 floats)
    for (size_t i = 0; i < numVertices; i++) {
        // Add position (3 floats)
        interleavedBuffer.push_back(vertexPositions[i * 3 + 0]);
        interleavedBuffer.push_back(vertexPositions[i * 3 + 1]);
        interleavedBuffer.push_back(vertexPositions[i * 3 + 2]);

        // Add color (3 floats)
        interleavedBuffer.push_back(vertexColors[i * 3 + 0]);
        interleavedBuffer.push_back(vertexColors[i * 3 + 1]);
        interleavedBuffer.push_back(vertexColors[i * 3 + 2]);

        // Add texture coordinates (2 floats)
        interleavedBuffer.push_back(textureCoords[i * 2 + 0]);
        interleavedBuffer.push_back(textureCoords[i * 2 + 1]);
    }

    return interleavedBuffer;
}

int main() {
    init();

    // Load shaders
    std::string vertexShaderSource = "C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\Resources\\VertexShader.glsl";
    std::string textureShaderSource = "C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\Resources\\FragmentShader.glsl";

    Shader shader = Shader(vertexShaderSource, textureShaderSource);

    Texture2D testTexture = Texture2D("C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\Resources\\FlatMarbleTexture.png");

    Camera camera = Camera();
    activeCamera = &camera;

    // print out camera details
    std::cout << "Projection Matrix:" << std::endl;
    Utils::printMat4(camera.GetProjectionMatrix());

    std::cout << "View Matrix:" << std::endl;
    Utils::printMat4(camera.GetViewMatrix());


    // Initialize Plane2D with the shader and texture
    Plane plane = Plane(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0, 1.0);

    std::vector<float> vertexPositions = plane.GetVertexPositions();
    
    // For now just make the colors white
    // should probably get this from a 'material' going forward
    std::vector<float> vertexColors = {
        0.0f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };

    // would probably also get this from a material?
    std::vector<float> textureCoords = {
        0.0f, 1.0f,         // top left
        1.0f, 1.0f,         // top right
        0.0f, 0.0f,         // bottom left
        1.0f, 0.0f,         // bottom right
    };

    std::vector<float> vertexBuffer = CreateInterleavedVertexBuffer(vertexPositions, vertexColors, textureCoords);
    
    // debug
    /*for (auto v : vertexBuffer) {
        std::cout << v;
    }
    std::cout << std::endl;*/

    // Create a vertex array
    VertexArray va = VertexArray(vertexBuffer, plane.GetIndices());

    Renderer renderer = Renderer();

    // TODO: remove this
    //activeCamera->Disable();
    std::cout << "Model Matrix:" << std::endl;
    Utils::printMat4(plane.GetModelMatrix());

    // Graphics loop
    while (!glfwWindowShouldClose(Window)) {
        // Clear the screen with the background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 modelMatrix = plane.GetModelMatrix();
        glm::mat4 viewMatrix = camera.GetViewMatrix();
        glm::mat4 projectionMatrix = camera.GetProjectionMatrix();
        renderer.Draw(shader, va, modelMatrix, viewMatrix, projectionMatrix);

        // Swap buffers and poll events
        glfwSwapBuffers(Window);
        glfwPollEvents();

        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
    }

    // Cleanup/exit
    glfwTerminate();
    std::cout << "Exiting cleanly\n";
    return 0;
}
