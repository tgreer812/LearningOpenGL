#pragma once
#include <vector>

class Geometry
{
public:
    virtual std::vector<float> GetVertexPositions() const { return std::vector<float>{}; }
    virtual std::vector<unsigned int> GetIndices() const { return std::vector<unsigned int>{}; }
};

