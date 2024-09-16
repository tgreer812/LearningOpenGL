#pragma once

#include "Drawable.h"

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
	void Draw(std::shared_ptr<Drawable> entity);

private:

};

