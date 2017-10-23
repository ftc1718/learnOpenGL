#version 330 core
out vec4 fragColor;

in vec3 vertexColor;

uniform vec3 objectColor;

void main()
{
	fragColor = vec4(vertexColor * objectColor, 1.0f);
}