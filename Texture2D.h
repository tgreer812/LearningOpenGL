#pragma once
#include <string>
#include <vector>

#define BYTE uint8_t

class Texture2D {
public:
    Texture2D(const std::string path);
    Texture2D(const std::string path, int channels);

    void Bind(); // Bind the texture for use

    int GetWidth();
    int GetHeight();
    BYTE* GetBuffer();
    int GetSize();

private:
    unsigned int m_textureID;   // Store texture ID here
    std::vector<BYTE> m_buffer;
    int m_width, m_height;
    bool m_initialized = false;
};


