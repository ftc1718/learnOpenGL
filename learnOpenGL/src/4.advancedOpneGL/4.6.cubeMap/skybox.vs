#version 330 core

layout (location = 0) in vec3 vPos;

out vec3 texDir;

uniform mat4 projection;
uniform mat4 view;

void main()
{	
	vec4 pos = projection * view * vec4(vPos, 1.0f);
	gl_Position = pos.xyww;
	texDir = vPos;
}