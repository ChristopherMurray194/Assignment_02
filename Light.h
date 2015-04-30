/*
 * Light.h
 *
 *  Created on: 26 Apr 2015
 *      Author: cmurray
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#define GLM_FORCE_RADIANS

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

};

#endif /* LIGHT_H_ */
