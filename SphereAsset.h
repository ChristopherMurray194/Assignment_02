/*
 * SphereAsset.h
 *
 *  Created on: 27 Mar 2015
 *      Author: cmurray
 */

#ifndef SPHEREASSET_H_
#define SPHEREASSET_H_

#include <iostream>
#include <GL/glew.h>

class SphereAsset {
public:
	SphereAsset();
	virtual ~SphereAsset();

	/**
	 * Draws sphere asset
	 *
	 * @param - takes program to use as parameter
	 */
	void Draw(GLint);

private:
	GLuint VertexArrayID;
	// This will identify out vertex buffer
	GLuint vertexbuffer;
};

#endif /* SPHEREASSET_H_ */
