/*
 * Camera.h
 *
 * References:
 * 		https://www.youtube.com/watch?v=H20stuPG-To - part 1  }
 * 		https://www.youtube.com/watch?v=oyctiGtnMiM - part 2  }	Used for keyboard camera control logic
 * 		https://www.youtube.com/watch?v=xsnrVg5up6E - part 3  }
 * 		http://www.swiftless.com/tutorials/opengl/camera.html }
 *
 *  Created on: 17 Apr 2015
 *      Author: cmurray
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameAsset.h"

class Camera : public GameAsset{
public:
	/**
	 * Camera movement logic from http://www.swiftless.com/tutorials/opengl/camera.html
	 */
	Camera();
	virtual ~Camera();

	  /**
	   * Move camera forward with W key
	   */
	  void forward();

	  /**
	   * Move camera back with S key
	   */
	  void backward();

	  /**
	   * Strafe camera left	with A key
	   */
	  void left();

	  /**
	   * Strafe camera right with D key
	   */
	  void right();

	  /**
	   * Strafe camera up with Z key
	   *
	   */
	  void up();

	  /**
	   * Strafe camera down with X key
	   *
	   */
	  void down();

	  /**
	   * rotate left with Q key
	   */
	  void rotLeft(GLfloat);

	  /**
	   * rotate right with E key
	   */
	  void rotRight(GLfloat);

	  /**
	   * Changes the yaw angle using the mouse
	   * @ the current x position of the mouse
	   */
	  void calcYaw(GLfloat);

	  /**
	   * Changed the pitch angle up with V key
	   */
	  void lookUp(GLfloat);

	  /**
	   * Changes the pitch angle down with C key
	   */
	  void lookDown(GLfloat);

	  /**
	   * The view matrix for a FPS (fly through) camera
	   */
	  glm::mat4 view_matrix(glm::vec3, GLfloat, GLfloat);

	  /**
	   * Get the camera position
	   * @param program to send camera to
	   */
	  virtual void Draw(GLuint);

private:
	  // define PI
	  const GLfloat PI = 3.1415926535;

	  GLfloat movementSpeed = 0.1;
};

#endif /* CAMERA_H_ */
