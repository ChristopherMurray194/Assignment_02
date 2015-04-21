/*
 * SphereAsset.h
 *
 *	References:
 *		http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html - for creating the icosphere
 *
 *  Created on: 27 Mar 2015
 *      Author: cmurray
 */

#ifndef SPHEREASSET_H_
#define SPHEREASSET_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "GameAsset.h"

class SphereAsset : public GameAsset{
public:
	/**
	 * Algorithm for creating stacked sphere from http://www.gamedev.net/topic/350823-rendering-a-sphere-using-triangle-strips/ - (user: Enigma's answer)
	 *
	 * Create a stacked sphere
	 */
	SphereAsset(GLfloat, GLuint, GLuint);
	virtual ~SphereAsset();

	/**
	 * Draws sphere asset
	 *
	 * @param - takes program to use as parameter
	 */
	virtual void Draw(GLuint);

private:
	GLuint VertexArrayID;
	GLuint vertexbuffer;			// This will identify the vertex buffer
	GLuint normalsbuffer;			// This will identify the normals buffer
	GLuint elementbuffer;			// This will identify the element buffer
	GLuint element_buffer_length;	// This will store the length of the element buffer

	/**
	 * Normalise the given vertex
	 */
	void normalise(GLfloat, GLfloat, GLfloat, std::vector<GLfloat>&);
};

#endif /* SPHEREASSET_H_ */
