#include "Texture2D.h"
#include "glad/glad.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture2D::Texture2D(const std::string path) : Texture2D(path, 4) {}

// For now store the image in memory
// might change this at some point (probably should)
// TODO: reevaluate this decision
// Constructor
Texture2D::Texture2D(const std::string path, int channels) {
    int x, y, comp;
    stbi_uc* buf = stbi_load(
        path.c_str(),
        &x,
        &y,
        &comp,
        channels
    );
    if (!buf) {
        std::cout << "Failed to load texture!" << std::endl;
        return;
    }
    this->m_initialized = true;

    this->m_buffer = std::vector<BYTE>(buf, buf + (x * y * channels));
    this->m_width = x;
    this->m_height = y;

    // Generate and bind texture ID here
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload texture data
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,  // Assuming 4 channels for internal format
        this->m_width,
        this->m_height,
        0,
        GL_RGBA,  // Format should match the number of channels in m_buffer
        GL_UNSIGNED_BYTE,
        this->m_buffer.data()
    );

    glGenerateMipmap(GL_TEXTURE_2D); // Optionally generate mipmaps
}

// Bind method
void Texture2D::Bind() {
    if (!this->m_initialized) {
        std::cout << "ERROR: Texture not initialized!" << std::endl;
        return;
    }

    glActiveTexture(GL_TEXTURE0); // Activate texture unit 0
    glBindTexture(GL_TEXTURE_2D, m_textureID); // Bind the texture ID generated earlier
}


int Texture2D::GetWidth() { return this->m_width; }

int Texture2D::GetHeight() { return this->m_height; }

BYTE* Texture2D::GetBuffer() { return (BYTE*)this->m_buffer.data(); }

int Texture2D::GetSize() { return this->m_buffer.size(); }