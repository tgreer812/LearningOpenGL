#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>

namespace Utils {

    // Function to read a file's content into a string
    std::string readFile(const std::string& filePath);

    // Utility to print glm::vec3
    void printVec3(const glm::vec3& v);

    // Utility to print glm::vec4
    void printVec4(const glm::vec4& v);

    // Utility to print glm::mat3
    void printMat3(const glm::mat3& m);

    // Utility to print glm::mat4
    void printMat4(const glm::mat4& m);

    void printVector(const std::vector<float>& vec);

    std::vector<float> CreateInterleavedVertexBuffer(
        const std::vector<float>& vertexPositions,
        const std::vector<float>& vertexColors,
        const std::vector<float>& textureCoords
    );

    /**
    * Returns a vector of floats created by replicating the color parameter fillSize times
    **/
    std::vector<float> FillVector3(glm::vec3 color, unsigned int fillSize);

}