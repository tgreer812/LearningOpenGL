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
#include "Mesh.h"
#include "Material.h"

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
float lastXPos = 0.0f;
float lastYPos = 0.0f;
bool first = true;

void handleMouseEvent(GLFWwindow* window, double xpos, double ypos) {
    if (first) {
        lastXPos = xpos; 
        lastYPos = ypos; 
        first = false;
        return;
    }

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

std::vector<float> Vertices = {
    // Front face (each vertex has a unique texture coordinate)
    -1.0f, -1.0f,  1.0f,  // Vertex 0
     1.0f, -1.0f,  1.0f,  // Vertex 1
    -1.0f,  1.0f,  1.0f,  // Vertex 2
     1.0f,  1.0f,  1.0f,  // Vertex 3

     // Back face
     -1.0f, -1.0f, -1.0f,  // Vertex 4
      1.0f, -1.0f, -1.0f,  // Vertex 5
     -1.0f,  1.0f, -1.0f,  // Vertex 6
      1.0f,  1.0f, -1.0f,  // Vertex 7

      // Left face
      -1.0f, -1.0f, -1.0f,  // Vertex 8
      -1.0f,  1.0f, -1.0f,  // Vertex 9
      -1.0f, -1.0f,  1.0f,  // Vertex 10
      -1.0f,  1.0f,  1.0f,  // Vertex 11

      // Right face
       1.0f, -1.0f, -1.0f,  // Vertex 12
       1.0f,  1.0f, -1.0f,  // Vertex 13
       1.0f, -1.0f,  1.0f,  // Vertex 14
       1.0f,  1.0f,  1.0f,  // Vertex 15

       // Top face
       -1.0f,  1.0f, -1.0f,  // Vertex 16
        1.0f,  1.0f, -1.0f,  // Vertex 17
       -1.0f,  1.0f,  1.0f,  // Vertex 18
        1.0f,  1.0f,  1.0f,  // Vertex 19

        // Bottom face
        -1.0f, -1.0f, -1.0f,  // Vertex 20
         1.0f, -1.0f, -1.0f,  // Vertex 21
        -1.0f, -1.0f,  1.0f,  // Vertex 22
         1.0f, -1.0f,  1.0f   // Vertex 23
};


std::vector<unsigned int> Indices = {
    // Front face
    0, 1, 2, 1, 3, 2,
    // Back face
    4, 6, 5, 5, 6, 7,
    // Left face
    0, 2, 4, 4, 2, 6,
    // Right face
    1, 5, 3, 5, 7, 3,
    // Top face
    2, 3, 6, 3, 7, 6,
    // Bottom face
    0, 4, 1, 1, 4, 5
};

std::vector<float> Colors = {
    // Front face (Red)
    1.0f, 0.0f, 0.0f,   // Vertex 0
    1.0f, 0.0f, 0.0f,   // Vertex 1
    1.0f, 0.0f, 0.0f,   // Vertex 2
    1.0f, 0.0f, 0.0f,   // Vertex 3

    // Back face (Green)
    0.0f, 1.0f, 0.0f,   // Vertex 4
    0.0f, 1.0f, 0.0f,   // Vertex 5
    0.0f, 1.0f, 0.0f,   // Vertex 6
    0.0f, 1.0f, 0.0f,   // Vertex 7

    // Left face (Blue)
    0.0f, 0.0f, 1.0f,   // Vertex 8
    0.0f, 0.0f, 1.0f,   // Vertex 9
    0.0f, 0.0f, 1.0f,   // Vertex 10
    0.0f, 0.0f, 1.0f,   // Vertex 11

    // Right face (Yellow)
    1.0f, 1.0f, 0.0f,   // Vertex 12
    1.0f, 1.0f, 0.0f,   // Vertex 13
    1.0f, 1.0f, 0.0f,   // Vertex 14
    1.0f, 1.0f, 0.0f,   // Vertex 15

    // Top face (White)
    1.0f, 1.0f, 1.0f,   // Vertex 16
    1.0f, 1.0f, 1.0f,   // Vertex 17
    1.0f, 1.0f, 1.0f,   // Vertex 18
    1.0f, 1.0f, 1.0f,   // Vertex 19

    // Bottom face (Cyan)
    0.0f, 1.0f, 1.0f,   // Vertex 20
    0.0f, 1.0f, 1.0f,   // Vertex 21
    0.0f, 1.0f, 1.0f,   // Vertex 22
    0.0f, 1.0f, 1.0f    // Vertex 23
};

std::vector<float> TextureCoords = {
    // Front face
    0.0f, 0.0f,  // Vertex 0
    1.0f, 0.0f,  // Vertex 1
    0.0f, 1.0f,  // Vertex 2
    1.0f, 1.0f,  // Vertex 3

    // Back face
    0.0f, 0.0f,  // Vertex 4
    1.0f, 0.0f,  // Vertex 5
    0.0f, 1.0f,  // Vertex 6
    1.0f, 1.0f,  // Vertex 7

    // Left face
    0.0f, 0.0f,  // Vertex 8
    1.0f, 0.0f,  // Vertex 9
    0.0f, 1.0f,  // Vertex 10
    1.0f, 1.0f,  // Vertex 11

    // Right face
    0.0f, 0.0f,  // Vertex 12
    1.0f, 0.0f,  // Vertex 13
    0.0f, 1.0f,  // Vertex 14
    1.0f, 1.0f,  // Vertex 15

    // Top face
    0.0f, 0.0f,  // Vertex 16
    1.0f, 0.0f,  // Vertex 17
    0.0f, 1.0f,  // Vertex 18
    1.0f, 1.0f,  // Vertex 19

    // Bottom face
    0.0f, 0.0f,  // Vertex 20
    1.0f, 0.0f,  // Vertex 21
    0.0f, 1.0f,  // Vertex 22
    1.0f, 1.0f   // Vertex 23
};




int main() {
    init();

    // Load shaders
    std::string vertexShaderSource = "C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\Resources\\VertexShader.glsl";
    std::string textureShaderSource = "C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\Resources\\FragmentShader.glsl";

    Shader shader = Shader(vertexShaderSource, textureShaderSource);
    //Shader shader2 = Shader(vertexShaderSource, textureShaderSource);

    //Texture2D marbleSideTex = Texture2D("C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\Resources\\FlatMarbleTexture.png");
    //Texture2D grassSideTex = Texture2D("C:\\Users\\tgree\\source\\repos\\LearningOpenGL\\Resources\\GrassBlockSide.png");

    Camera camera = Camera();
    activeCamera = &camera;

    // Enable depth testing
    //glEnable(GL_DEPTH_TEST);

    // print out camera details
    std::cout << "Projection Matrix:" << std::endl;
    Utils::printMat4(camera.GetProjectionMatrix());

    std::cout << "View Matrix:" << std::endl;
    Utils::printMat4(camera.GetViewMatrix());

    Material grassSideMat = Material(shader);
    //grassSideMat.SetVertexColor(glm::vec3(1.0f, 1.0f, 1.0f));
    //grassSideMat.SetTexture(grassSideTex);
    grassSideMat.SetBlend(0.0f);
    // 
    // Create a model matrix for the cube
    glm::mat4 modelMatrix = glm::mat4(1.0f);  // Initialize as identity matrix

    // Apply scaling transformation to make the cube 5x5x5
    modelMatrix = glm::scale(modelMatrix, glm::vec3(5.0f, 5.0f, 5.0f));

    // Apply translation to move the cube further back into the camera's view
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, -10.0f));

    Mesh testBlock(
        Vertices,
        Indices,
        Colors,
        TextureCoords,
        modelMatrix,
        grassSideMat,
        *activeCamera
    );

    Renderer renderer = Renderer();

    // Graphics loop
    while (!glfwWindowShouldClose(Window)) {
        

        // Clear the screen with the background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);

        
        glm::mat4 viewMatrix = camera.GetViewMatrix();
        glm::mat4 projectionMatrix = camera.GetProjectionMatrix();

        renderer.Draw(testBlock);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL Error: " << error << std::endl;
        }   

        //glm::mat4 modelMatrix1 = planeMesh1.GetGeometry().GetModelMatrix();
        
        // this will eventually get replaced with looping through
        // all models in the scene
        //bool first = true;
        //for (auto& curPlane : planeMeshes) {
        //    //if (!first) { first = false; break; }
        //    glm::mat4 modelMatrix = curPlane.GetGeometry().GetModelMatrix();
        //    renderer.Draw<Plane>(curPlane, modelMatrix, viewMatrix, projectionMatrix);

        //    GLenum error = glGetError();
        //    if (error != GL_NO_ERROR) {
        //        std::cout << "OpenGL Error: " << error << std::endl;
        //    }
        //}

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
