/*
 * SphereAsset.cpp
 *
 *  Created on: 27 Mar 2015
 *      Author: cmurray
 */

#include "SphereAsset.h"

SphereAsset::SphereAsset()
{
	/*
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	*/

	GLfloat t = (1.0 + std::sqrt(5.0f)) / 2.0;

	// An array of 3 vectors which represents 3 vertices
	GLfloat vertex_buffer_data[]
	{
		-1.0, t, 0.0,
		1.0, t, 0.0,
		-1.0, -t, 0.0,
		1.0, -t, 0.0,

		0.0, -1.0, t,
		0.0, 1.0, t,
		0.0, -1.0, -t,
		0.0, 1.0, -t,

		t, 0.0, -1.0,
		t, 0.0, 1.0,
		-t, 0.0, -1.0,
		-t, 0.0, 1.0
	};

	element_buffer_length = 60;
	GLuint element_buffer_data[]
	{
		0,11,5,
		0,5,1,
		0,1,7,
		0,7,10,
		0,10,11,

		1,5,9,
		5,11,4,
		11,10,2,
		10,7,6,
		7,1,8,

		3,9,4,
		3,4,2,
		3,2,6,
		3,6,8,
		3,8,9,

		4,9,5,
		2,4,11,
		6,2,10,
		8,6,7,
		9,8,1
	};

	//--------Vertex buffer--------//
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 36, vertex_buffer_data, GL_STATIC_DRAW);
	//-----------------------------//

	//-------Element buffer--------//
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * element_buffer_length, element_buffer_data, GL_STATIC_DRAW);
	//-----------------------------//
}

SphereAsset::~SphereAsset()
{
	// TODO Auto-generated destructor stub
}

void SphereAsset::subDivide(
						GLfloat v1x, GLfloat v1y, GLfloat v1z,
						GLfloat v2x, GLfloat v2y, GLfloat v2z,
						GLfloat v3x, GLfloat v3y, GLfloat v3z,
						GLint subLevel
						){
	if(subLevel == 0)
	{
		// If the icosphere has been subdivided required number of times
		// TODO Draw triangle
	}else
	{
		// Calculate middle of the first edge
		GLfloat v12x = 0.5 * (v1x + v2x);
		GLfloat v12y = 0.5 * (v1y + v2y);
		GLfloat v12z = 0.5 * (v1z + v2z);

		// Renormalize to get a point on the sphere
		GLfloat s = 1.0 / std::sqrt(v12x * v12x + v12y * v12y + v12z * v12z);
		v12x *= s;
		v12y *= s;
		v12z *= s;

		GLfloat v13x = 0.5 * (v1x + v3x);
		GLfloat v13y = 0.5 * (v1y + v3y);
		GLfloat v13z = 0.5 * (v1z + v3z);
		s = 1.0 / std::sqrt(v13x * v13x + v13y * v13y + v13z * v13z);
		v13x *= s;
		v13y *= s;
		v13z *= s;

		GLfloat v23x = 0.5 * (v2x + v3x);
		GLfloat v23y = 0.5 * (v2y + v3y);
		GLfloat v23z = 0.5 * (v2z + v3z);
		s = 1.0 / std::sqrt(v23x * v23x + v23y * v23y + v23z * v23z);
		v23x *= s;
		v23y *= s;
		v23z *= s;

		// Make the recursive calls
		subDivide(
				v1x, v1y, v1z,
				v12x, v12y, v12z,
				v13x, v13y, v13z,
				subLevel -1
				);
		subDivide(
				v12x, v12y, v12z,
				v2x, v2y, v2z,
				v23x, v23y, v23z,
				subLevel -1
				);
		subDivide(
				v13x, v13y, v13z,
				v23x, v23y, v23z,
				v3x, v3y, v3z,
				subLevel -1
				);
		subDivide(
				v12x, v12y, v12z,
				v23x, v23y, v23z,
				v13x, v13y, v13z,
				subLevel -1
				);
	}
}

void SphereAsset::Draw(GLuint program_token)
{

	GLuint position_attrib = glGetAttribLocation(program_token, "position");

	glUseProgram(program_token);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// Display as wireframe

	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glVertexAttribPointer(
			position_attrib,		// attribute 0.
			3, 						// size
			GL_FLOAT,				// type
			GL_FALSE, 				// normalized?
			0,						// stride
			(void*)0				// array buffer offset
		);
	glEnableVertexAttribArray(position_attrib);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	glDrawElements(
				GL_TRIANGLES,
				element_buffer_length,
				GL_UNSIGNED_INT,
				(GLvoid*)0
				);

	glDisableVertexAttribArray(position_attrib);
}

