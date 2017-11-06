#version 330 core
out vec4 fragColor;

in vec3 normal;
in vec3 position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
//	float ratio = 1.0f / 1.52f;
	vec3 I = normalize(position - cameraPos);
//	vec3 R = refract(I, normalize(normal), ratio);
	vec3 R = reflect(I, normalize(normal));
	fragColor = texture(skybox, R);
}