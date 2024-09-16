// Game.h

#pragma once

#include "glad/glad.h"
#include "Event.h"
#include <GLFW/glfw3.h>

class Game {
public:
    Game(int windowWidth = 800, int windowHeight = 600, const char* title = "My Graphics Engine");
    ~Game();

    // Initialize the game (window, event handlers, etc.)
    void init();

    // Start the game loop
    void start();

    

private:
    // Window dimensions and title
    int windowWidth;
    int windowHeight;
    const char* windowTitle;

    // GLFW window
    GLFWwindow* window;

    // Timing variables
    float deltaTime;
    float lastFrameTime;    

    // Wireframe mode flag
    bool wireframe;

    // Static methods for GLFW callbacks
    static void handleKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void handleMouseEvent(GLFWwindow* window, double xpos, double ypos);

    // Helper method
    void toggleWireframe();
};
