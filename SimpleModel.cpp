// SimpleModel.cpp
#include "SimpleModel.h"
#include "ModelManager.h"
#include <iostream>

SimpleModel::SimpleModel(const std::string& filepath) {
    // Get the model data from the ModelManager
    modelData = ModelManager::Instance().GetModelData(filepath);

    if (modelData) {
        modelLoaded = true;
    }
    else {
        std::cerr << "Error: Model data could not be loaded for: " << filepath << std::endl;
    }
}

const std::vector<float>& SimpleModel::GetVertices() const {
    return modelData->Vertices;
}

const std::vector<unsigned int>& SimpleModel::GetIndices() const {
    return modelData->Indices;
}

const std::vector<float>& SimpleModel::GetColors() const {
    return modelData->Colors;
}

const std::vector<float>& SimpleModel::GetTextureCoords() const {
    return modelData->TextureCoords;
}

bool SimpleModel::IsModelLoaded() const {
    return modelLoaded;
}

