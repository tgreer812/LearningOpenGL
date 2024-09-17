#include <iostream>

#include "glm/glm.hpp"
#include "World.h"
#include "GrassBlock.h"

// Instantiate the singleton instance
World& World::GetInstance() {
    static World instance;
    return instance;
}

// Private constructor
World::World() : deltaTime(0.0f) {
}

// Destructor
World::~World() {
}

void World::init() {
    // Register event handlers
    GlobalEventDispatcher.AddListener("KeyEvent", [this](std::shared_ptr<Event> e) {
        auto keyEvent = std::dynamic_pointer_cast<KeyEvent>(e);
        if (keyEvent) {
            onKeyEvent(keyEvent);
        }
        });

    GlobalEventDispatcher.AddListener("MouseMovedEvent", [this](std::shared_ptr<Event> e) {
        auto mouseMovedEvent = std::dynamic_pointer_cast<MouseMovedEvent>(e);
        if (mouseMovedEvent) {
            onMouseMovedEvent(mouseMovedEvent);
        }
        });

    this->m_entities = {};

    this->initTerrain();

}

void World::initTerrain() {
    //this->m_entities.push_back(std::make_shared<GrassBlock>(glm::vec3(0.0f, 0.0f, 0.0f)));
    // for now hardcode terrain as default blocks
    for (int x = -20; x <= 20; x++) {
        for (int z = -20; z <= 20; z++) {
            this->m_entities.push_back(
                std::make_shared<GrassBlock>(glm::vec3((float)x*2, 0.0f, (float)z*2))
            );
            //std::cout << x << " " << z << std::endl;
        }
    }
}

void World::Update(float deltaTime) {
    this->deltaTime = deltaTime;
    // Update world state if necessary
}

void World::Draw() {
    // Render the world
    // Use camera's view and projection matrices as needed
    for (auto& entity : this->m_entities) {
        this->m_renderer.Draw(entity);
    }
}

Camera& World::GetCamera() {
    return camera;
}

void World::onKeyEvent(std::shared_ptr<KeyEvent> e) {
    if (e->action == KeyAction::Press || e->action == KeyAction::Repeat) {
        glm::vec3 direction(0.0f);

        switch (e->key) {
        case GLFW_KEY_W:
            direction.z = 1.0f;
            break;
        case GLFW_KEY_A:
            direction.x = 1.0f;
            break;
        case GLFW_KEY_S:
            direction.z = -1.0f;
            break;
        case GLFW_KEY_D:
            direction.x = -1.0f;
            break;
        default:
            break;
        }

        camera.Move(direction, deltaTime);
    }
}

void World::onMouseMovedEvent(std::shared_ptr<MouseMovedEvent> e) {
    camera.Rotate(e->GetDeltaX(), e->GetDeltaY());
}