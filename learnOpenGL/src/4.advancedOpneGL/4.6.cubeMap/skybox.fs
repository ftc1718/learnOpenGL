#version 330 core
out vec4 fragColor;

in vec3 texDir;

uniform samplerCube skybox;

void main()
{
	fragColor = texture(skybox, texDir);
}