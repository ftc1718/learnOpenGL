#version 330 core
out vec4 fragColor;

in vec2 texCoords;

uniform sampler2D screenTexture;

void main()
{
//	fragColor = vec4(1.0f - texture(screenTexture, texCoords).rgb, 1.0f); // inversion
	//grayscale
	vec4 color = texture(screenTexture, texCoords);
	//float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;  much more better
	fragColor = vec4(vec3((color.r + color.g + color.b) / 3.0f), 1.0f);
}