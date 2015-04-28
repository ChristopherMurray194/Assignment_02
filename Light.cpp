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

void Light::initLight()
{
	//--------Define light terms---------------//
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, As);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	//-----------------------------------------//

	//--------Define material terms------------//
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	//-----------------------------------------//
}

void Light::Draw(GLuint program_token)
{

	initLight();

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
