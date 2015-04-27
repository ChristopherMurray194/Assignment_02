#version 150

uniform sampler2D texSampler;
uniform vec4 As;
uniform vec4 diffuse;
uniform vec4 diffuse_material;
uniform vec4 ambient;
uniform vec4 ambient_material;
uniform float shininess_material;
uniform vec4 spec;
uniform vec4 specular_material;

in Data {
	vec3 norm;
	vec3 eyeVec;
	vec3 lightDirection;
	vec2 texCoordinates;
	vec2 xy_position;
} DataIn;

out vec4 color;

/**
* solution for fixing texture wrapping error where two tex coords are for example
* 0.9, 0.0 and 0.0, 1.0 insteas of 0.9, 0.0 and 0.0, 1.0 insteas of 0.9, 1.0 and 0.0, 0.1
* - http://stackoverflow.com/questions/9511499/seam-issue-when-mapping-a-texture-to-a-sphere-in-opengl - (User: Sarge Borsch)
*
* Lighting method from http://www.ozone3d.net/tutorials/glsl_lighting_phong_p2.php
*/
void main()
{
	const float PI = 3.1415926535;
	
	vec4 finalColor = 
	(As * ambient_material) + 
	(ambient * ambient_material);
	
	vec3 N = normalize(DataIn.norm);
	vec3 L = normalize(DataIn.lightDirection);
	
	float lambertTerm = dot(N, L);
	
	if(lambertTerm > 0.0f)
	{
		finalColor += diffuse
						* diffuse_material 
						* lambertTerm;
					  			
		vec3 E = normalize(DataIn.eyeVec);
		vec3 R = reflect(-L, N);
		float specular = pow(max(dot(R,E), 0.0),
						 shininess_material);
		
		finalColor += spec 
						* specular_material 
						* specular;
	}
	
	vec2 texCoord = DataIn.texCoordinates;
	texCoord.x = (PI + atan(DataIn.xy_position.y, DataIn.xy_position.x)) / (2 * PI);
	color = finalColor * texture2D(texSampler, texCoord);
}