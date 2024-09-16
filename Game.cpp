// Game.cpp

#include "Game.h"
#include "World.h"
#include "glad/glad.h"
#include <iostream>

Game::Game(int windowWidth, int windowHeight, const char* title)
    : windowWidth(windowWidth),
    windowHeight(windowHeight),
    windowTitle(title),
    window(nullptr),
    deltaTime(0.0f),
    lastFrameTime(0.0f),
    wireframe(false) {
}

Game::~Game() {
    glfwTerminate();
}

void Game::init() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!\n";
        exit(EXIT_FAILURE);
    }

    // Set GLFW window hints for OpenGL version (3.3 Core)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the GLFW window
    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load OpenGL functions using GLAD
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD!\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Set the OpenGL viewport
    glViewport(0, 0, windowWidth, windowHeight);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Set input modes and callbacks
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, handleKeyEvent);
    glfwSetCursorPosCallback(window, handleMouseEvent);

    // Initialize the world and pass the event dispatcher
    World::GetInstance().init(&eventDispatcher);
}

void Game::start() {
    // Main game loop
    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time
        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // Clear the screen
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update the world
        World::GetInstance().Update(deltaTime);

        // Render the world
        World::GetInstance().Draw();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::cout << "Exiting cleanly\n";
}

void Game::handleKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Retrieve the Game instance
    Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    if (!game) return;

    // Map GLFW action to KeyAction enum
    KeyAction keyAction = KeyAction::Press;
    if (action == GLFW_RELEASE)
        keyAction = KeyAction::Release;
    else if (action == GLFW_REPEAT)
        keyAction = KeyAction::Repeat;

    // Create a KeyEvent and dispatch it
    auto keyEvent = std::make_shared<KeyEvent>(key, scancode, keyAction, mods);
    game->eventDispatcher.Dispatch(keyEvent);

    // Handle wireframe toggle within the Game class
    if (keyEvent->action == KeyAction::Release && keyEvent->key == GLFW_KEY_X) {
        game->toggleWireframe();
    }
}

void Game::handleMouseEvent(GLFWwindow* window, double xpos, double ypos) {
    // Retrieve the Game instance
    Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    if (!game) return;

    static bool firstMouseMovement = true;
    static double lastXPos = xpos;
    static double lastYPos = ypos;

    if (firstMouseMovement) {
        lastXPos = xpos;
        lastYPos = ypos;
        firstMouseMovement = false;
    }

    float deltaX = static_cast<float>(xpos - lastXPos);
    float deltaY = static_cast<float>(ypos - lastYPos);
    lastXPos = xpos;
    lastYPos = ypos;

    // Create a MouseMovedEvent and dispatch it
    auto mouseMovedEvent = std::make_shared<MouseMovedEvent>(
        static_cast<int>(xpos), static_cast<int>(ypos), deltaX, deltaY);
    game->eventDispatcher.Dispatch(mouseMovedEvent);
}

void Game::toggleWireframe() {
    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    wireframe = !wireframe;
}
