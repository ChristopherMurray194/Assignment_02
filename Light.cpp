/*
 * Light.cpp
 *
 *  Created on: 26 Apr 2015
 *      Author: cmurray
 */

#include "Light.h"

Light::Light() {
	// TODO Auto-generated constructor stub

}

Light::~Light() {
	// TODO Auto-generated destructor stub
}

void Light::Draw(GLuint program_token)
{
	//--------Define light intensities---------------//
	GLfloat As[4] {0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat ambient[4] {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat diffuse[4] {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat specular[4] {10.0f, 10.0f, 10.0f, 10.0f};

	GLfloat light_pos[4] {0.0f, 1.0f, 6.0f, 1.0f};
	//-----------------------------------------//

	//--------Define material color------------//
	GLfloat ambient_material[4] {1.5f, 1.5f, 1.5f, 1.0f};
	GLfloat diffuse_material[4] {2.0f, 0.0f, 0.0f, 1.0f};
	GLfloat specular_material[4] {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat shininess = 10.0f;								// Cannot be 0.0
	//-----------------------------------------//

	// Pass to shader
	GLuint as_attrib = glGetUniformLocation(program_token, "As");
	glUniform4fv(as_attrib, 1, As);

	GLuint pos_attrib = glGetUniformLocation(program_token, "lightPosition");
	glUniform4fv(pos_attrib, 1, light_pos);

	GLuint diff_attrib = glGetUniformLocation(program_token, "diffuse");
	glUniform4fv(diff_attrib, 1, diffuse);

	GLuint diff_mat_attrib = glGetUniformLocation(program_token, "diffuse_material");
	glUniform4fv(diff_mat_attrib, 1, diffuse_material);

	GLuint amb_attrib = glGetUniformLocation(program_token, "ambient");
	glUniform4fv(amb_attrib, 1, ambient);

	GLuint amb_mat_attrib = glGetUniformLocation(program_token, "ambient_material");
	glUniform4fv(amb_mat_attrib, 1, ambient_material);

	GLuint shininess_mat_attrib = glGetUniformLocation(program_token, "shininess_material");
	glUniform1f(shininess_mat_attrib, shininess);

	GLuint spec_attrib = glGetUniformLocation(program_token, "spec");
	glUniform4fv(spec_attrib, 1, specular);

	GLuint spec_mat_attrib = glGetUniformLocation(program_token, "specular_material");
	glUniform4fv(spec_mat_attrib, 1, specular_material);
}
