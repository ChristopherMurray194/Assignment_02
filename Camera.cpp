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

}

void Camera::down()
{

}

void Camera::rotLeft()
{
	x--;
	if(x < -360)x += 360;
}

void Camera::rotRight()
{
	x ++;
	if(x > 360) x -= 360;
}

void Camera::mouseMovement(GLfloat mouseX, GLfloat mouseY, bool mouseIn)
{/*
	x = mouseX;
	y = mouseY;

	if(mouseIn)
	{
		int midX = 320;
		int midY = 240;

		SDL_ShowCursor(SDL_DISABLE);	// Hide the cursor

		int tempX, tempY;
		SDL_GetMouseState(&tempX, &tempY);	// Get the mouse X and Y
		y+=sensitivity*(midX-tempX);
		x-=sensitivity*(midY-tempY);
		//SDL_WarpMouseInWindow(window, midX, midY);	// Reset mouse to middle of window
		const Uint8* state=SDL_GetKeyboardState(NULL);	// Get the currently pressed keys
		if(state [SDLK_w])
		{
			if(x!= 90 && x != -90)
				forward();
			up();
		}else if(state [SDLK_s])
		{
			if(x != 90 && x != -90)
				backward();
			down();
		}else if(state [SDLK_a])
		{
			left();
		}else if(state [SDLK_d])
		{
			right();
		}
	}*/
}

void Camera::Draw(GLuint program_token)
{
	// create camera matrix
	glm::mat4 camera = glm::translate(glm::mat4(1.0f), glm::vec3(-x, -y, -z));

	GLuint camera_attrib = glGetUniformLocation(program_token, "camera");
	// Send camera matrix to vertex shader
	glUniformMatrix4fv(camera_attrib, 1, GL_FALSE, &camera[0][0]);
}
