#version 330 core

out vec4 fragColor;
in vec3 vertexPosition;

void main()
{
	fragColor = vec4(vertexPosition, 1.0f);
}