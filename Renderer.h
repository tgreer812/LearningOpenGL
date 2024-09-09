#pragma once
#include "Mesh.h"
#include "Material.h"
#include "VertexArray.h"
#include "glm/glm.hpp"

class Renderer
{
public:
	Renderer() {}

	// TODO: make this use materials instead of shaders
	// Have a material class responsible for knowing the uniforms of a specific shader
	// have it have a public method like "SetUniforms" that is responsible for binding the shader
	// and setting the uniforms to the user provided values
	// and then this method can just call that
	// for now though just going to do this since we only have one shader
	template <typename T>
	void Draw(Mesh<T>& mesh, glm::mat4& modelMatrix, glm::mat4& viewMatrix, glm::mat4& projectionMatrix) {
		// Bind the shader
		//shader.Bind();
		//material.Use();
		//Material material = mesh.GetMaterial();

		// Set camera uniforms
		Shader shader = mesh.GetMaterial().GetShader();
		shader.Bind();
		shader.SetMat4("modelMatrix", modelMatrix);
		shader.SetMat4("viewMatrix", viewMatrix);
		shader.SetMat4("projectionMatrix", projectionMatrix);

		unsigned int vaSize = mesh.Bind();

		// Bind the vertex array
		glDrawElements(
			GL_TRIANGLES,			// Use triangle as primitive
			vaSize,					// This gets the number of non-repeated vertices (i.e the indices)
			GL_UNSIGNED_INT,		// The 'type' of data
			nullptr					// ptr to the indices - however we bind our index data to an index buffer, so we just specify nullptr
		);
	}

private:

};

