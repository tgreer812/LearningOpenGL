#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>

class SimpleModel
{
public:
    std::vector<float> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<float> Colors;
    std::vector<float> TextureCoords;
    bool modelLoaded = false;

    SimpleModel(const std::string& filepath) {
        if (LoadModel(filepath))
            modelLoaded = true;
    }

    bool LoadModel(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') {
                continue; // Skip comments and empty lines
            }

            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "v") {
                // Vertices (x, y, z)
                float x, y, z;
                iss >> x >> y >> z;
                Vertices.push_back(x);
                Vertices.push_back(y);
                Vertices.push_back(z);
            }
            else if (prefix == "i") {
                // Indices (triangle indices)
                unsigned int a, b, c;
                iss >> a >> b >> c;
                Indices.push_back(a);
                Indices.push_back(b);
                Indices.push_back(c);
            }
            else if (prefix == "c") {
                // Colors (r, g, b)
                float r, g, b;
                iss >> r >> g >> b;
                Colors.push_back(r);
                Colors.push_back(g);
                Colors.push_back(b);
            }
            else if (prefix == "t") {
                // Texture Coordinates (u, v)
                float u, v;
                iss >> u >> v;
                TextureCoords.push_back(u);
                TextureCoords.push_back(v);
            }
        }

        file.close();
        return true;
    }
};