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

struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

#define POINT_LIGHT_NUMS 4

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[POINT_LIGHT_NUMS];
uniform SpotLight spotLight;
uniform vec3 viewPos;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDir);

void main()
{
	vec3 norm = normalize(vertexNormal);
	vec3 viewDir = normalize(viewPos - fragPos);

	//DirLight
	vec3 result = calcDirLight(dirLight, norm, viewDir);
	
	//PointLight
	for(int i = 0; i < POINT_LIGHT_NUMS; i++)
	{
		result += calcPointLight(pointLights[i], norm, viewDir);
	}
	
	//SpotLight
	result += calcSpotLight(spotLight, norm, viewDir); 
	
	fragColor = vec4(result, 1.0f);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	//ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

	//diffuse
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, texCoords)));

	//specular
	vec3 reflectDir = reflect(-lightDir, normal); //-lightPos: lightPos point to fragPos
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, texCoords)));
	
	return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	//ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

	//diffuse
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, texCoords)));

	//specular
	vec3 reflectDir = reflect(-lightDir, normal); //-lightPos: lightPos point to fragPos
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, texCoords)));

	//attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	return (ambient + diffuse + specular) * attenuation;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
   //ambient
    vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb;
    
    //diffuse 
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoords).rgb;  
    
    //specular
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, texCoords).rgb;  
    
    //spotlight (soft edges)
	float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;
	
	/*
	//another way to caculate spotlight intensity
	float p = 25.0f; //聚光灯发出光的聚集程度
	float intensity = pow(max(dot(normalize(-light.direction), lightDir), 0.0f), p);
    ambient  *= intensity;
	diffuse  *= intensity;
    specular *= intensity;
	*/
    
    //attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    ambient *= attenuation; 
    diffuse *= attenuation;
    specular *= attenuation;   
        
    return (ambient + diffuse + specular);
}
