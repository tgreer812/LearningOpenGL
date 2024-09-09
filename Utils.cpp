#pragma once
#include "Utils.h"
#include <vector>

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


    void printVector(const std::vector<float>& vec) {
        std::cout << "vector(";
        for (auto f : vec) {
            std::cout << f << ", ";
        }
        std::cout << ")" << std::endl;
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

    std::vector<float> CreateInterleavedVertexBuffer(
        const std::vector<float>& vertexPositions,
        const std::vector<float>& vertexColors,
        const std::vector<float>& textureCoords
    )
    {
        std::vector<float> interleavedBuffer;

        // Ensure all vectors are the same length (in terms of number of vertices)
        size_t numVertices = vertexPositions.size() / 3; // 3 floats per position
        if (vertexColors.size() / 3 != numVertices || textureCoords.size() / 2 != numVertices) {
            throw std::runtime_error("Mismatch in vertex data sizes.");
        }

        // Interleave the data: position (3 floats), color (3 floats), texture coord (2 floats)
        for (size_t i = 0; i < numVertices; i++) {
            // Add position (3 floats)
            interleavedBuffer.push_back(vertexPositions[i * 3 + 0]);
            interleavedBuffer.push_back(vertexPositions[i * 3 + 1]);
            interleavedBuffer.push_back(vertexPositions[i * 3 + 2]);

            // Add color (3 floats)
            interleavedBuffer.push_back(vertexColors[i * 3 + 0]);
            interleavedBuffer.push_back(vertexColors[i * 3 + 1]);
            interleavedBuffer.push_back(vertexColors[i * 3 + 2]);

            // Add texture coordinates (2 floats)
            interleavedBuffer.push_back(textureCoords[i * 2 + 0]);
            interleavedBuffer.push_back(textureCoords[i * 2 + 1]);
        }

        return interleavedBuffer;
    }


    std::vector<float> FillVector3(glm::vec3 color, unsigned int fillSize) {

        std::vector<float> result = {};
        for (unsigned i = 0; i < fillSize; i++) {
            result.push_back(color.r);
            result.push_back(color.g);
            result.push_back(color.b);
        }

        return result;
    }

}