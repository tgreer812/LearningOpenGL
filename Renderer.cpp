#include "Renderer.h"
#include "Utils.h"


void Renderer::Draw(std::shared_ptr<Drawable> entity) {
	// Set camera uniforms

	entity->Bind();
	unsigned int vaSize = entity->GetSize();

	// Bind the vertex array
	GL_CALL(glDrawElements(
		GL_TRIANGLES,			// Use triangle as primitive
		vaSize,						// This gets the number of unique vertices
		GL_UNSIGNED_INT,		// The 'type' of data
		nullptr					// ptr to the indices - however we bind our index data to an index buffer, so we just specify nullptr
	));

	//mesh.Unbind();
}