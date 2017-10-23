#version 330 core
out vec4 fragColor;

in vec3 vertexNormal;
in vec3 fragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

//uniform float time;

void main()
{
	//simulate a simple Ambient light
	float ambientStrength = 0.1f;
//	float ambientStrength = (sin(time) + 1.0f) / 2.0f;
	vec3 ambient = ambientStrength * lightColor;

	//diffuse
	vec3 norm = normalize(vertexNormal);
	vec3 lightDir = normalize(lightPos - fragPos); //fragPos point to lightPos
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	//specular
	float specularStrength = 0.5f;
//	float specularStrength = (sin(time) + 1.0f) / 2.0f;
	vec3 viewDir = normalize(viewPos - fragPos);

	/*
	vec3 reflectDir = reflect(-lightDir, norm); //-lightPos: lightPos point to fragPos
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;
	*/

	//another way to caculate specular  Computationally smaller(math for 3d gameprogramming)
	
	vec3 intermediateDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(norm, intermediateDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;
	

	vec3 result = (ambient + diffuse + specular) * objectColor;
	fragColor = vec4(result, 1.0f);
}