// ModelManager.cpp
#include "ModelManager.h"
#include <iostream>

ModelManager& ModelManager::Instance() {
    static ModelManager instance;
    return instance;
}

std::shared_ptr<ModelData> ModelManager::GetModelData(const std::string& filepath) {
    {
        // Lock the mutex for thread safety
        std::lock_guard<std::mutex> lock(cacheMutex);

        // Check if the model is already loaded
        auto it = modelCache.find(filepath);
        if (it != modelCache.end()) {
            // Return the existing model data
            return it->second;
        }
    }

    // Model not found, load it
    std::shared_ptr<ModelData> modelData = std::make_shared<ModelData>();

    // Load model data from file
    if (!modelData->LoadModel(filepath)) {
        std::cerr << "Error: Failed to load model: " << filepath << std::endl;
        return nullptr;
    }

    {
        // Lock the mutex before modifying the cache
        std::lock_guard<std::mutex> lock(cacheMutex);
        // Store the model data in the cache
        modelCache[filepath] = modelData;
    }

    return modelData;
}

void ModelManager::Clear() {
    std::lock_guard<std::mutex> lock(cacheMutex);
    modelCache.clear();
}
