// ModelData.h
#pragma once

#include <vector>
#include <string>

class ModelData {
public:
    std::vector<float> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<float> Colors;
    std::vector<float> TextureCoords;

    bool LoadModel(const std::string& filename);

private:
    // You can add private helper methods if needed
};
