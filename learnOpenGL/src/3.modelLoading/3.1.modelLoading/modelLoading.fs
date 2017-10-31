

#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

/*struct Material
{
	sampler2D diffuse;
	sampler2D specular;
};*/

//uniform Material material;
uniform sampler2D texture_diffuse1;

void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords);
}

