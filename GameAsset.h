/*
 * GameAsset.h
 *
 *  Created on: 21 Apr 2015
 *      Author: cmurray
 */

#ifndef GAMEASSET_H_
#define GAMEASSET_H_

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>

class GameAsset
{
public: virtual void Draw(GLuint) = 0;

};
#endif /* GAMEASSET_H_ */
