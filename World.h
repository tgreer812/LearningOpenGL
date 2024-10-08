#pragma once

#include "glad/glad.h"
#include "Camera.h"
#include "Event.h"
#include "MouseEvent.h"
#include "KeyEvent.h"
#include "Renderer.h"
#include <memory>


class World {
public:
    // Get the singleton instance of the World
    static World& GetInstance();

    // Initialize the world and register event handlers
    void init();

    void initTerrain();

    // Update the world (if needed)
    void Update(float deltaTime);

    // Render the world
    void Draw();

    // Method to get a reference to the camera
    Camera& GetCamera();

private:
    // Private constructor to prevent multiple instances
    World();
    ~World();

    // Delete copy constructor and assignment operator
    World(const World&) = delete;
    World& operator=(const World&) = delete;

    // Camera
    Camera camera;

    // Renderer
    Renderer m_renderer;

    // drawable entities
    std::vector<std::shared_ptr<Drawable>> m_entities;

    // Event handling methods
    void onKeyEvent(std::shared_ptr<KeyEvent> e);
    void onMouseMovedEvent(std::shared_ptr<MouseMovedEvent> e);

    // Timing variable
    float deltaTime;
};
