/*
 * Camera.cpp
 *
 *  Created on: 17 Apr 2015
 *      Author: cmurray
 */

#include "Camera.h"

	glm::vec3 position {0.0f, 1.0f, 5.0f};			// The position (or eye) of the camera

	GLfloat yaw = 0.0f;								// Yaw = left-right rotation
	GLfloat pitch = 0.0f;							// Pitch = up-down rotation

	glm::vec3 viewDirection {0.0f, 0.0f, 1.0f};		// The direction the camera is viewing
	const glm::vec3 UP {0.0f, 1.0f, 0.0f};			// The UP direction in the world

	GLfloat movement_speed = 0.2;

Camera::Camera() {
	// TODO Auto-generated constructor stub
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::forward()
{
	position -= viewDirection * movement_speed;
}

void Camera::backward()
{
	position += viewDirection * movement_speed;
}

void Camera::left()
{
	position -= glm::cross(UP, viewDirection) * movement_speed;
}

void Camera::right()
{
	position += glm::cross(UP, viewDirection) * movement_speed;
}

void Camera::up()
{
	position += UP * movement_speed;
}

void Camera::down()
{
	position -= UP * movement_speed;
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

	viewDirection = zaxis;	// The view direction is along the z axis

	return glm::mat4(
				glm::vec4(xaxis.x, yaxis.x, zaxis.x, 0.0f),
				glm::vec4(xaxis.y, yaxis.y, zaxis.y, 0.0f),
				glm::vec4(xaxis.z, yaxis.z, zaxis.z, 0.0f),
				glm::vec4(-glm::dot(xaxis, eye), -glm::dot(yaxis, eye), -glm::dot(zaxis, eye), 1.0f)
			);
}

void Camera::Draw(GLuint program_token)
{
	// create view matrix
	glm::mat4 camera = view_matrix(position, glm::radians(pitch), glm::radians(yaw));

	GLuint camera_attrib = glGetUniformLocation(program_token, "camera");
	// Send camera matrix to vertex shader
	glUniformMatrix4fv(camera_attrib, 1, GL_FALSE, &camera[0][0]);
}
