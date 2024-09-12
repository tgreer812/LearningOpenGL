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
	void Draw(Mesh &mesh) {
		// Set camera uniforms

		unsigned int vaSize = mesh.Bind();

		// Bind the vertex array
		glDrawElements(
			GL_TRIANGLES,			// Use triangle as primitive
			vaSize,					// This gets the number of unique vertices
			GL_UNSIGNED_INT,		// The 'type' of data
			nullptr					// ptr to the indices - however we bind our index data to an index buffer, so we just specify nullptr
		);

		mesh.Unbind();
	}

private:

};

