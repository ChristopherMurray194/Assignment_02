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

class SphereAsset {
public:
	SphereAsset();
	virtual ~SphereAsset();

	/**
	 * Subdivide the given triangle (as vertices)
	 *
	 * Reference:
	 * 	from http://stackoverflow.com/questions/26790422/recursive-subdivision-on-octahedron-in-opengl (answer (user: Reto Koradi))
	 */
	void subDivide(
					GLfloat, GLfloat, GLfloat,
					GLfloat, GLfloat, GLfloat,
					GLfloat, GLfloat, GLfloat,
					GLint
				   );
	/**
	 * Draws sphere asset
	 *
	 * @param - takes program to use as parameter
	 */
	void Draw(GLuint);

private:
	GLuint VertexArrayID;
	GLuint vertexbuffer;			// This will identify the vertex buffer
	GLuint elementbuffer;			// This will identify the element buffer
	GLuint element_buffer_length;	// This will identify the length of the element buffer

	const GLfloat PI = 3.1415926535;	// define PI

};

#endif /* SPHEREASSET_H_ */
