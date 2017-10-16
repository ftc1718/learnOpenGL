#version 330 core

out vec4 fragColor;

in vec3 vertexColor;
in vec2 vertexTexCoord;

uniform float mixValue;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	vec4 texel0, texel1;
	texel0 = texture(texture0, vertexTexCoord);
	texel1 = texture(texture1, vertexTexCoord);
	fragColor = mix(texel0, texel1, texel1.a * mixValue);
}
