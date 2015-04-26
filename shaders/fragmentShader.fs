#version 130

uniform sampler2D texSampler;
uniform vec4 diffuse;
uniform vec4 diffuse_material;
uniform vec4 ambient;
uniform vec4 ambient_material;
uniform float shininess_material;
uniform vec4 spec;
uniform vec4 specular_material;

in vec3 norm;
in vec3 eyeVec;
in vec3 lightDirection;
in vec2 texCoordinates;
in vec2 xy_position;

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
	(gl_FrontLightModelProduct.sceneColor * ambient_material) + 
	(ambient * ambient_material);
	
	vec3 N = normalize(norm);
	vec3 L = normalize(lightDirection);
	
	float lambertTerm = dot(N, L);
	
	if(lambertTerm > 0.0)
	{
		finalColor += diffuse
						* diffuse_material 
						* lambertTerm;
					  			
		vec3 E = normalize(eyeVec);
		vec3 R = reflect(-L, N);
		float specular = pow(max(dot(R,E), 0.0),
						 shininess_material);
		
		finalColor += spec 
						* specular_material 
						* specular;
	}
	
	vec2 texCoord = texCoordinates;
	texCoord.x = (PI + atan(xy_position.y, xy_position.x)) / (2 * PI);
	color = finalColor * texture2D(texSampler, texCoord);
}