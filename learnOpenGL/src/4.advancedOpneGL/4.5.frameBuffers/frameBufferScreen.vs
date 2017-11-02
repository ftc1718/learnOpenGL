#version 330 core

layout (location = 0) in vec2 vPos;
layout (location = 1) in vec2 vTexCoords;

out vec2 texCoords;

void main()
{		
	texCoords = vTexCoords;
	gl_Position = vec4(vPos.x, vPos.y, 0.0f, 1.0f);
}