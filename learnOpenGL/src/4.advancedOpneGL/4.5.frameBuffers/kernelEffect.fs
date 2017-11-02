//http://setosa.io/ev/image-kernels/  many different image kernels
#version 330 core
out vec4 fragColor;

in vec2 texCoords;

uniform sampler2D screenTexture;

const float offset = 1.0f / 500.0f;

void main()
{
	vec2 offsets[9] = 
	{
		vec2(-offset, offset), //top left
		vec2( 0.0f,   offset), //top
		vec2( offset, offset), //top right
		vec2(-offset,  0.0f),
		vec2( 0.0f,    0.0f),
		vec2( offset,  0.0f),
		vec2(-offset, -offset),
		vec2( 0.0f,   -offset),
		vec2( offset, -offset),
	};

	//sharpen
	/*float kernel[9] = 
	{
		-1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
	};*/

	//blur
	float kernel[9] =
	{
		1.0 / 16, 2.0 / 16, 1.0 / 16,
		2.0 / 16, 4.0 / 16, 2.0 / 16,
		1.0 / 16, 2.0 / 16, 1.0 / 16 
	};

	vec3 sampleTex[9];
	for(int i = 0; i < 9; i++)
	{
		sampleTex[i] = vec3(texture(screenTexture, texCoords.st + offsets[i]));
	}

	vec3 color = vec3(0.0f);
	for(int i = 0; i < 9; i++)
	{
		color += sampleTex[i] * kernel[i];
	}
	
	fragColor = vec4(color, 1.0f);
}