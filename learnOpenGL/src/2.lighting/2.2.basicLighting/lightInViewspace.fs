#version 330 core
out vec4 fragColor;

in vec3 vertexNormal;
in vec3 fragPosInVS;
in vec3 lightPosInVS;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	//simulate a simple Ambient light
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	//diffuse
	vec3 norm = normalize(vertexNormal);
	vec3 lightDir = normalize(lightPosInVS - fragPosInVS); //fragPos point to lightPos
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	//specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(-fragPosInVS);

	
	vec3 reflectDir = reflect(-lightDir, norm); //-lightPos: lightPos point to fragPos
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;
	

	//another way to caculate specular  Computationally smaller(math for 3d gameprogramming)	
	/*
	vec3 intermediateDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(norm, intermediateDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;
	*/

	vec3 result = (ambient + diffuse + specular) * objectColor;
	fragColor = vec4(result, 1.0f);
}