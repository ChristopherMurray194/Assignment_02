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

#include <memory>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameAsset.h"

class Camera : public GameAsset{
public:
	Camera();
	virtual ~Camera();

	  /**
	   * Move camera forward
	   * @param deltaTime : time between each frame
	   */
	  void forward();

	  /**
	   * Move camera back
	   * @param deltaTime : time between each frame
	   */
	  void backward();

	  /**
	   * Strafe camera left
	   * @param deltaTime : time between each frame
	   */
	  void left();

	  /**
	   * Strafe camera right
	   * @param deltaTime : time between each frame
	   */
	  void right();

	  /**
	   * Strafe camera up
	   * @param deltaTime : time between each frame
	   *
	   */
	  void up();

	  /**
	   * Strafe camera down
	   * @param deltaTime : time between each frame
	   *
	   */
	  void down();

	  /**
	   * rotate left with Q key
	   */
	  void rotLeft();

	  /**
	   * rotate right with E key
	   */
	  void rotRight();

	  /**
	   * Handles the camera control using the mouse
	   */
	  void mouseMovement(GLfloat, GLfloat, bool);

	  /**
	   * Get the camera position
	   * @bug The camera's look at point does not change, as a result forward for example is always the same direction.
	   * @bug The camera's rotation does not function correctly once the cursor leaves the window.
	   * @param program to send camera to
	   */
	  virtual void Draw(GLuint);

private:
	  // define PI
	  const GLfloat PI = 3.1415926535;
};

#endif /* CAMERA_H_ */
