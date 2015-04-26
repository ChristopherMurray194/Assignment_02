/*
 * Light.h
 *
 *  Created on: 26 Apr 2015
 *      Author: cmurray
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameAsset.h"

class Light : public GameAsset{
public:
	Light();
	virtual ~Light();

	virtual void Draw(GLuint);

private:

	//--------Define light intensities---------------//
	GLfloat As[4] {0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat ambient[4] {0.1, 0.1f, 0.1f, 1.0f};
	GLfloat diffuse[4] {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat specular[4] {1.0f, 1.0f, 1.0f, 1.0f};

	GLfloat light_pos[4] {0.0f, 0.0f, 0.0f, 1.0f};
	//-----------------------------------------//

	//--------Define material color------------//
	GLfloat ambient_material[4] {0.3f, 0.3f, 0.3f, 1.0f};	// ambient
	GLfloat diffuse_material[4] {0.9f, 0.5f, 0.5f, 1.0f};	// + diffuse = 1.0
	GLfloat specular_material[4] {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat shininess = 0.0f;
	//-----------------------------------------//

	void initLight();
};

#endif /* LIGHT_H_ */
