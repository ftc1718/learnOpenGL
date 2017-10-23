#version 330 core
out vec4 fragColor;

in vec3 vertexNormal;
in vec3 fragPos;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
	//ambient
	vec3 ambient = light.ambient * material.ambient;

	//diffuse
	vec3 norm = normalize(vertexNormal);
	vec3 lightDir = normalize(light.position - fragPos); //fragPos point to lightPos
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//specular
	vec3 viewDir = normalize(viewPos - fragPos);
	
	vec3 reflectDir = reflect(-lightDir, norm); //-lightPos: lightPos point to fragPos
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);
	
	//another way to caculate specular  Computationally smaller(math for 3d gameprogramming)
	/*
	vec3 intermediateDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(norm, intermediateDir), 0.0f), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);
	*/
	
	vec3 result = ambient + diffuse + specular;
	fragColor = vec4(result, 1.0f);
}