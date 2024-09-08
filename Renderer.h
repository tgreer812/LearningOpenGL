#pragma once
#include "Shader.h"
#include "VertexArray.h"
#include "glm/glm.hpp"

class Renderer
{
public:
	Renderer();

	void Draw(Shader& shader, VertexArray& va, glm::mat4& modelMatrix, glm::mat4& viewMatrix, glm::mat4& projectionMatrix);

private:

};

