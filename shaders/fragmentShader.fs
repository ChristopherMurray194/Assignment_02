#version 130

in vec2 texCoordinates;

out vec4 color;

uniform sampler2D texSampler;

void main()
{
	color = texture2D(texSampler, texCoordinates.st);
}