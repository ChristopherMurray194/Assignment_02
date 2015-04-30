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
#include <glm/ext.hpp> // glm::translate
#include <SOIL/SOIL.h>

#include "GameAsset.h"

class SphereAsset : public GameAsset{
public:
	/**
	 * Algorithm for creating stacked sphere from http://www.gamedev.net/topic/350823-rendering-a-sphere-using-triangle-strips/ - (user: Enigma's answer)
	 *
	 * Create a stacked sphere
	 *
	 * @param radius - radius of sphere (determines size)
	 * @param stacks - number of stacks (verticle segments)
	 * @param slices - number of slices (horizontal segments)
	 * @param texture_file_path - path to the texture to be loaded
	 * @param x_pos - x position (Default: 0.0)
	 * @param y_pos - y position (Default: 0.0)
	 * @param z_pos - z position (Default: 1.0)
	 */
	SphereAsset( const char*, const GLfloat = 1.0f, const GLuint = 20, const GLuint = 40, GLfloat x_pos = 0.0, GLfloat y_pos = 0.0, GLfloat z_pos = 1.0);
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
	GLuint texturebuffer;			// This will identify the texture buffer
	GLuint normalbuffer;			// This will identify the normals buffer
	GLuint indicesbuffer;			// This will identify the element buffer
	GLuint indices_buffer_length;	// This will store the length of the element buffer

	GLuint textureID;					// This will identify the texture used

	GLfloat x_pos, y_pos, z_pos;	// Position variables to be passed to vertex_shader

	GLfloat rotate_angle = 0.0;		// This is the rotation angle

	/**
	 * Calculate vertices and texture coordinates
	 */
	void calcVerticesAndTexCoords(const GLuint, const GLuint, const GLfloat, std::vector<glm::vec3>&, std::vector<glm::vec2>&);

	/**
	 * Calculate indices
	 */
	void calcIndices(const GLuint, const GLuint, std::vector<GLushort>&);

	/**
	 * Normalise the given vector
	 *
	 */
	glm::vec3 normalise(const glm::vec3&);

	/**
	 * Calculate the vertex normals per vertex
	 * adapted from http://stackoverflow.com/questions/6656358/calculating-normals-in-a-triangle-mesh - User: Kosta's answer
	 */
	void normaliseVertices(const GLuint, const GLuint, const std::vector<glm::vec3>, std::vector<glm::vec3>&);

	/**
	 * rotate on the x axis
	 * @param angle of rotation
	 */
	glm::mat4 rotate_x(GLfloat);

	/**
	 * rotate on the y axis
	 * @param angle of rotation
	 */
	glm::mat4 rotate_y(GLfloat);

	/**
	 * rotate on the z axi
	 * @aparam angle of rotation
	 */
	glm::mat4 rotate_z(GLfloat);
};

#endif /* SPHEREASSET_H_ */
