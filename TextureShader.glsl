#shader vertex
#version 330 core

out vec4 ourColor;

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;

void main() {
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPosition, 1.0);
	ourColor = aColor;
}



#shader fragment
#version 330 core

in vec4 ourColor
out vec4 FragColor;

void main() {
	FragColor = ourColor;
}