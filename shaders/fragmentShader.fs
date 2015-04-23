#version 130

uniform sampler2D texSampler;

in vec4 texCoordinates;

out vec4 color;

void main()
{
	color = texture2D(texSampler, texCoordinates.xz);
}