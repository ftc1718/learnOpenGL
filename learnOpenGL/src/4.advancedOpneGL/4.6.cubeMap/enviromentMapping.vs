#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;

out vec3 normal;
out vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	normal = mat3(transpose(inverse(model))) * vNormal;
	position = vec3(model * vec4(vPos, 10.f));
	gl_Position = projection * view * model * vec4(vPos, 1.0f);
}