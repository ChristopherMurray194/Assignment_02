#version 130

uniform sampler2D texSampler;

in vec4 norm;
in vec2 texCoordinates;
in vec2 xy_position;

out vec4 color;

/**
* solution for fixing texture wrapping error where two tex coords are for example
* 0.9, 0.0 and 0.0, 1.0 insteas of 0.9, 0.0 and 0.0, 1.0 insteas of 0.9, 1.0 and 0.0, 0.1
* - http://stackoverflow.com/questions/9511499/seam-issue-when-mapping-a-texture-to-a-sphere-in-opengl - (User: Sarge Borsch)
*/
void main()
{
	const float PI = 3.1415926535;

	vec2 texCoord = texCoordinates;
	texCoord.x = (PI + atan(xy_position.y, xy_position.x)) / (2 * PI);
	color = texture2D(texSampler, texCoord);
}