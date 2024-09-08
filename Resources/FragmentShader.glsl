#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform bool useTexture;   // Flag to determine whether to use texture or color
uniform float blendFactor; // Blend factor (0.0 = only color, 1.0 = only texture)

void main()
{
    // Fetch the texture color
    vec4 texColor = texture(ourTexture, TexCoord);
    
    // Convert ourColor to a vec4 with an alpha of 1.0
    vec4 color = vec4(ourColor, 1.0);
    
    // If the texture should be used, blend it with the color based on the blendFactor
    if (useTexture) {
        FragColor = mix(color, texColor, blendFactor);
    }
    // If the texture is not used, output only the color
    else {
        FragColor = color;
    }
}
