#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>

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

}