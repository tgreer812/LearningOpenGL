#pragma once
#include "Utils.h"

namespace Utils {
    std::string readFile(const std::string& filePath) {
	    std::ifstream file(filePath, std::ios::binary | std::ios::ate);

	    if (!file.is_open()) {
		    std::cerr << "Error: Could not open file." << std::endl;
		    return "";
	    }

	    std::streamsize fileSize = file.tellg();
	    file.seekg(0, std::ios::beg);

	    std::string buffer(fileSize, '\0');
	    if (!file.read(&buffer[0], fileSize)) {
		    std::cerr << "Error: Could not read file." << std::endl;
		    return "";
	    }

	    return buffer;
    }

    // Utility to print glm::vec3
    void printVec3(const glm::vec3& v) {
        std::cout << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
    }

    // Utility to print glm::vec4
    void printVec4(const glm::vec4& v) {
        std::cout << "vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")" << std::endl;
    }

    // Utility to print glm::mat3
    void printMat3(const glm::mat3& m) {
        std::cout << "mat3(" << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << "  ";
            for (int j = 0; j < 3; ++j) {
                std::cout << m[i][j];
                if (j < 2) std::cout << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << ")" << std::endl;
    }

    // Utility to print glm::mat4
    void printMat4(const glm::mat4& m) {
        std::cout << "mat4(" << std::endl;
        for (int i = 0; i < 4; ++i) {
            std::cout << "  ";
            for (int j = 0; j < 4; ++j) {
                std::cout << m[i][j];
                if (j < 3) std::cout << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << ")" << std::endl;
    }

}