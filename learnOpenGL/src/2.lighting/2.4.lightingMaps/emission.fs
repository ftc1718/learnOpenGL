#version 330 core
out vec4 fragColor;

in vec3 vertexNormal;
in vec3 fragPos;
in vec2 texCoords;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
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
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

	//diffuse
	vec3 norm = normalize(vertexNormal);
	vec3 lightDir = normalize(light.position - fragPos); //fragPos point to lightPos
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, texCoords)));

	//specular
	vec3 viewDir = normalize(viewPos - fragPos);
	
	vec3 reflectDir = reflect(-lightDir, norm); //-lightPos: lightPos point to fragPos
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, texCoords)));

	//emission
	vec3 emission = vec3(texture(material.emission, texCoords));

	vec3 result = ambient + diffuse + specular + emission;
	fragColor = vec4(result, 1.0f);
}