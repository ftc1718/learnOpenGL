

#version 330 core
out vec4 fragColor;

in vec2 texCoords;
in vec3 normal;
in vec3 position;

uniform samplerCube skybox;
uniform vec3 cameraPos;

void main()
{    
	float ratio = 1.0 / 1.52;
    vec3 I = normalize(position - cameraPos);
    vec3 R = refract(I, normalize(normal), ratio);
    fragColor = vec4(texture(skybox, R).rgb, 1.0);
}

