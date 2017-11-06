

#version 330 core
out vec4 fragColor;

in vec2 texCoords;
in vec3 normal;
in vec3 position;

uniform samplerCube skybox;
uniform vec3 cameraPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_reflection1;

void main()
{    
	vec4 diffuseColor = texture(texture_diffuse1, texCoords);
	float reflectIntensity = texture(texture_reflection1,texCoords).r;
    vec3 I = normalize(position - cameraPos);
    vec3 R = reflect(I, normalize(normal));
    vec4 reflectColor;
	if(reflectIntensity > 0.1f)
	{
		reflectColor = texture(skybox, R) * reflectIntensity;
	}
    fragColor = diffuseColor + reflectColor;
}

