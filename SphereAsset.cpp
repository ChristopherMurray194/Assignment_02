/*
 * SphereAsset.cpp
 *
 *  Created on: 27 Mar 2015
 *      Author: cmurray
 */

#include "SphereAsset.h"

SphereAsset::SphereAsset()
{
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// An array of 3 vectors which represents 3 vertices
	const GLfloat g_vertex_buffer_data[] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	// Generate 1 buffer, put the reuslting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Give out vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

SphereAsset::~SphereAsset()
{
	// TODO Auto-generated destructor stub
}

void SphereAsset::Draw(GLint program_token)
{

	glUseProgram(program_token);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glVertexAttribPointer(
			0,				// attribute 0. No particular reason for 0, but must match the layout in the shader
			3, 				// size
			GL_FLOAT,		// type
			GL_FALSE, 		// normalized?
			0,				// stride
			(void*)0		// array buffer offset
		);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);
}

