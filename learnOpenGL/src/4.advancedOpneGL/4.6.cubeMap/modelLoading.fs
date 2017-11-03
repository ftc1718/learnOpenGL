

#version 330 core
out vec4 fragColor;

in vec2 texCoords;
in vec3 normal;
in vec3 position;

uniform samplerCube skybox;
uniform vec3 cameraPos;

void main()
{    
    vec3 I = normalize(position - cameraPos);
    vec3 R = reflect(I, normalize(normal));
    fragColor = vec4(texture(skybox, R).rgb, 1.0);
}

