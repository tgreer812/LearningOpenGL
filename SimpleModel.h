// SimpleModel.h
#pragma once

#include <string>
#include <vector>
#include <memory>
#include "ModelData.h"

class SimpleModel
{
public:
    // Constructor
    SimpleModel(const std::string& filepath);

    // Accessor methods to retrieve model data
    const std::vector<float>& GetVertices() const;
    const std::vector<unsigned int>& GetIndices() const;
    const std::vector<float>& GetColors() const;
    const std::vector<float>& GetTextureCoords() const;

    // Flag indicating whether the model was successfully loaded
    bool IsModelLoaded() const;

private:
    // Shared pointer to the model data
    std::shared_ptr<ModelData> modelData;

    // Flag indicating whether the model was successfully loaded
    bool modelLoaded = false;
};

