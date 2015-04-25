/*
 * Camera.cpp
 *
 *  Created on: 17 Apr 2015
 *      Author: cmurray
 */

#include "Camera.h"

	GLfloat x =  0.0;	///< camera position x
	GLfloat y =  1.0;	///< camera position y
	GLfloat z = 5.0;	///< camera position z

	GLfloat yaw = 0.0f;
	GLfloat pitch = 0.0f;

Camera::Camera() {
	// TODO Auto-generated constructor stub
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::forward()
{
	GLfloat x_radians = (x/180 * PI);
	GLfloat y_radians = (y/180 * PI);

	x += GLfloat(sin(y_radians)) * 0.2;
	y -= GLfloat(sin(x_radians)) * 0.2;
	z -= GLfloat(cos(y_radians)) * 0.2;
}

void Camera::backward()
{
	GLfloat x_radians = (x/180 * PI);
	GLfloat y_radians = (y/180 * PI);

	x -= GLfloat(sin(y_radians)) * 0.2;
	y += GLfloat(sin(x_radians)) * 0.2;
	z += GLfloat(cos(y_radians)) * 0.2;
}

void Camera::left()
{
	GLfloat y_radians = (y/180 * PI);
	x -= GLfloat(cos(y_radians)) * 0.2;
	z -= GLfloat(sin(y_radians)) * 0.2;
}

void Camera::right()
{
	GLfloat y_radians = (y/180 * PI);
	x += GLfloat(cos(y_radians)) * 0.2;
	z += GLfloat(sin(y_radians)) * 0.2;
}

void Camera::up()
{
	GLfloat y_radians = (y/180 * PI);
	y += GLfloat(cos(y_radians)) * 0.2;
}

void Camera::down()
{
	GLfloat y_radians = (y/180 * PI);
	y -= GLfloat(cos(y_radians)) * 0.2;
}

void Camera::rotLeft(GLfloat delta)
{
	GLfloat sensitivity = 0.5;
	yaw += sensitivity * delta;
}

void Camera::rotRight(GLfloat delta)
{
	GLfloat sensitivity = 0.5;
	yaw -= sensitivity * delta;
}

void Camera::calcYaw(GLfloat mouseX)
{
	GLfloat sensitivity = 0.5;
	if(mouseX >= 640-2)	// mouse moved to the right boundary of window
	{
		yaw -= sensitivity;
	}
	else if(mouseX <= 0)	// mouse moved to the left boundary of window
	{
		yaw += sensitivity;
	}
}

void Camera::lookUp(GLfloat delta)
{
	GLfloat sensitivity = 0.5;
	pitch += sensitivity * delta;
}

void Camera::lookDown(GLfloat delta)
{
	GLfloat sensitivity = 0.5;
	pitch -= sensitivity * delta;
}

/**
 * Pitch = up-down rotation
 * Yaw = left-right rotation
 */
glm::mat4 Camera::view_matrix(glm::vec3 eye, GLfloat pitch, GLfloat yaw)
{
	//from http://www.3dgep.com/understanding-the-view-matrix/#Look_At_Camera
	GLfloat cosPitch = cos(pitch);
	GLfloat sinPitch = sin(pitch);
	GLfloat cosYaw = cos(yaw);
	GLfloat sinYaw = sin(yaw);

	glm::vec3 xaxis {cosYaw, 0.0f, -sinYaw};
	glm::vec3 yaxis {sinYaw * sinPitch, cosPitch, cosYaw * sinPitch};
	glm::vec3 zaxis {sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw};

	return glm::mat4(
				glm::vec4(xaxis.x, yaxis.x, zaxis.x, 0.0f),
				glm::vec4(xaxis.y, yaxis.y, zaxis.y, 0.0f),
				glm::vec4(xaxis.z, yaxis.z, zaxis.z, 0.0f),
				glm::vec4(-glm::dot(xaxis, eye), -glm::dot(yaxis, eye), -glm::dot(zaxis, eye), 1.0f)
			);
}

void Camera::Draw(GLuint program_token)
{
	glm::vec3 eye {x, y, z};
	// create view matrix
	glm::mat4 camera = view_matrix(eye, glm::radians(pitch), glm::radians(yaw));

	GLuint camera_attrib = glGetUniformLocation(program_token, "camera");
	// Send camera matrix to vertex shader
	glUniformMatrix4fv(camera_attrib, 1, GL_FALSE, &camera[0][0]);
}
