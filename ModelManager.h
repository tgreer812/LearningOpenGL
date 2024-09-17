// ModelManager.h
#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <mutex>
#include "ModelData.h"

class ModelManager {
public:
    // Singleton access method
    static ModelManager& Instance();

    // Deleted methods to prevent copying
    ModelManager(const ModelManager&) = delete;
    ModelManager& operator=(const ModelManager&) = delete;

    // Method to get or load a model
    std::shared_ptr<ModelData> GetModelData(const std::string& filepath);

    // Optional method to clear all cached models
    void Clear();

private:
    // Private constructor and destructor
    ModelManager() = default;
    ~ModelManager() = default;

    // Cache for model data
    std::unordered_map<std::string, std::shared_ptr<ModelData>> modelCache;

    // Mutex for thread safety
    std::mutex cacheMutex;
};
