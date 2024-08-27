#pragma once

#include "glad/glad.h"
#include "vector"

class VertexArray
{
public:
	VertexArray(const float vertices[], size_t vertexCount, const unsigned int indices[], size_t indexCount);
	~VertexArray();
	
	void Use();

private:
	std::vector<float> _vertices;
	std::vector<unsigned int> _indices;
};

