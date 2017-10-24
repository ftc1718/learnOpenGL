#version 330 core
out vec4 fragColor;

in vec3 vertexNormal;
in vec3 fragPos;
in vec2 texCoords;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 direction;
	float cutOff;

	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
	vec3 lightDir = normalize(light.position - fragPos);
	float theta = dot(lightDir, normalize(-light.direction));
	if(theta > light.cutOff)
	{
		//ambient
		vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

		//diffuse
		vec3 norm = normalize(vertexNormal);
		float diff = max(dot(norm, lightDir), 0.0f);
		vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, texCoords)));

		//specular
		vec3 viewDir = normalize(viewPos - fragPos);	
		vec3 reflectDir = reflect(-lightDir, norm); //-lightPos: lightPos point to fragPos
		float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
		vec3 specular = light.specular * (spec * vec3(texture(material.specular, texCoords)));

		//attenuation
		float distance = length(light.position - fragPos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

		vec3 result = ambient + (diffuse + specular) * attenuation;
		fragColor = vec4(result, 1.0f);
	}
	else
	{
		fragColor = vec4(light.ambient * vec3(texture(material.diffuse, texCoords)), 1.0f);
	}
}