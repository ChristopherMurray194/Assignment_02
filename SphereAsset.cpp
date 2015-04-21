/*
 * SphereAsset.cpp
 *
 *  Created on: 27 Mar 2015
 *      Author: cmurray
 */

#include "SphereAsset.h"

SphereAsset::SphereAsset(GLfloat radius, GLuint stacks, GLuint slices, GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	// Assign the new positions
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->z_pos = z_pos;

	const GLfloat PI = 3.1415926535;	// define PI

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> textcoords;
	std::vector<GLuint> indices;

	for(GLuint i = 0; i <= stacks; i++)
	{
		for(GLuint j = 0; j  < slices; j++)
		{
			GLfloat theta = i * PI / stacks;	// Calculate the theta angle (angle on the z and y axis)
			GLfloat phi = j * 2 * PI / slices;	// Calculate the phi angle (angle on the x and y axis)

			GLfloat x, y, z;
			x = radius * sin(theta) * cos(phi);	// Calculate the x of the vertex
			y = radius * sin(theta) * sin(phi);	// Calculate the y of the vertex
			z = radius * cos(theta);			// Calculate the z of the vertex

			normalise(x, y, z, normals);	// Normalise the vertex

			//---Add the vertex to the vertex vector--//
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		}
	}

	for(GLuint i = 0; i < stacks; i++)
	{
		for(GLuint j = 0; j <= slices; j++)
		{
			indices.push_back((i * slices) + (j % slices));
			indices.push_back(((i + 1) * slices) + (j % slices));
		}
	}

	GLuint vertex_buffer_length = vertices.size();
	GLuint normals_buffer_length = normals.size();
	element_buffer_length = indices.size();

	//--------Vertex buffer--------//
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertex_buffer_length, &vertices[0], GL_STATIC_DRAW);
	//-----------------------------//

	glGenBuffers(1, &normalsbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalsbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals_buffer_length, &normals[0], GL_STATIC_DRAW);

	//-------Element buffer--------//
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * element_buffer_length, &indices[0], GL_STATIC_DRAW);
	//-----------------------------//
}

SphereAsset::~SphereAsset()
{
	// TODO Auto-generated destructor stub
}

void SphereAsset::normalise(GLfloat vx, GLfloat vy, GLfloat vz, std::vector<GLfloat> &normals)
{
	GLfloat d = std::sqrt(vx * vx + vy * vy + vz * vz);
	if(d != 0.0)
	{
		vx /= d;
		vy /= d;
		vz /= d;
		normals.push_back(vx);
		normals.push_back(vy);
		normals.push_back(vz);
	}
}

glm::mat4 SphereAsset::rotate_x(GLfloat theta)
{
	return glm::mat4(
			glm::vec4(1.0, 0.0, 0.0, 0.0),
			glm::vec4(0.0, cos(theta), sin(theta), 0.0),
			glm::vec4(0.0, -sin(theta), cos(theta), 0.0),
			glm::vec4(0.0, 0.0, 0.0, 1.0)
		);
}

glm::mat4 SphereAsset::rotate_y(float theta)
{
	return glm::mat4(
			glm::vec4(cos(theta), 0.0, -sin(theta), 0.0),
			glm::vec4(0.0, 1.0, 0.0, 0.0),
			glm::vec4(sin(theta), 0.0, cos(theta), 0.0),
			glm::vec4(0.0, 0.0, 0.0, 1.0)
		);
}

void SphereAsset::Draw(GLuint program_token)
{
	if(rotate_angle >= 0.0)
	{
		rotate_angle++;
	}
	else if(rotate_angle > 360.0)
	{
		rotate_angle = 0.0;
	}

	// create model matrix
	glm::mat4 model_matrix = rotate_y(glm::radians(rotate_angle)) * rotate_x(glm::radians(90.0)) *  glm::translate(glm::mat4(1.0f), glm::vec3(-x_pos, -y_pos, -z_pos));

	GLuint model_attrib = glGetUniformLocation(program_token, "model_matrix");
	// Send camera matrix to vertex shader
	glUniformMatrix4fv(model_attrib, 1, GL_FALSE, &model_matrix[0][0]);

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
				GL_TRIANGLE_STRIP,
				element_buffer_length,
				GL_UNSIGNED_INT,
				(GLvoid*)0
				);

	glDisableVertexAttribArray(position_attrib);
}

