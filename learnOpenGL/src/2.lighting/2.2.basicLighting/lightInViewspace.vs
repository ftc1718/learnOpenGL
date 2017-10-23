#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 vertexNormal;
out vec3 fragPosInVS;
out vec3 lightPosInVS; //light position in view space

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	fragPosInVS = vec3(view * model * vec4(position, 1.0f));
	vertexNormal = mat3(transpose(inverse(view  * model))) * normal;
	lightPosInVS = vec3(view * vec4(lightPos, 1.0f));
}