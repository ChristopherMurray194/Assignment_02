/*
 * SphereAsset.cpp
 *
 *  Created on: 27 Mar 2015
 *      Author: cmurray
 */

#include "SphereAsset.h"

SphereAsset::SphereAsset(const GLfloat radius,
						 const GLuint stacks,
						 const GLuint slices,
						 const char * texture_file_path,
						 GLfloat x_pos,
						 GLfloat y_pos,
						 GLfloat z_pos)
{
	// load the texture
	textureID = SOIL_load_OGL_texture(texture_file_path,
									SOIL_LOAD_AUTO,								// specify image format
									SOIL_CREATE_NEW_ID,							// Create new texture ID
									SOIL_FLAG_MIPMAPS | SOIL_FLAG_POWER_OF_TWO);	// Specify flags

	//Define texture parameters
	glBindTexture(GL_TEXTURE_BUFFER, textureID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Assign the new positions
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->z_pos = z_pos;

	const GLfloat PI = 3.1415926535;	// define PI

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	std::vector<GLushort> indices;

	for(GLuint i = 0; i <= stacks; i++)
	{
		for(GLuint j = 0; j  < slices; j++)
		{
			GLfloat phi = i * PI / stacks;	// Calculate the theta angle (angle on the z and y axis)
			GLfloat theta = j * 2 * PI / slices;	// Calculate the phi angle (angle on the x and y axis)

			GLfloat x, y, z;
			x = radius * sin(phi) * cos(theta);	// Calculate the x of the vertex
			y = radius * sin(phi) * sin(theta);	// Calculate the y of the vertex
			z = radius * cos(phi);			// Calculate the z of the vertex


			//---Add the vertex to the vertex vector--//
			vertices.push_back(glm::vec3(x, y, z));

			GLfloat d = std::sqrt((x * x) + (y * y) + (z * z));	// length of vertex

			if(d != 0.0)
			{
			//Generate UV coordinates
			const GLfloat PI = 3.1415926535;	// define PI
			GLfloat U = (atan2(y, x) / PI + 1.0f) * 0.5;
			GLfloat V = acos(z / d) / PI;

			texcoords.push_back(glm::vec2(U, V));

			}
		}
	}

	for(GLuint i = 0; i < stacks; i++)
	{
		for(GLuint j = 0; j  <= slices; j++)
		{
			indices.push_back((i * slices) + (j % slices));
			indices.push_back(((i + 1) * slices) + (j % slices));
		}
	}

	// Calculate vertex normals
	for(GLuint i = 0; i < indices.size(); i++)
	{
		glm::vec3 U = vertices[i+1] - vertices[i];
		glm::vec3 V = vertices[i+2] - vertices[i];

		glm::vec3 surfaceNormal = glm::cross(U, V);	// Calculate the surface normal

		glm::vec3 normalised_surface = normalise(surfaceNormal); // Normalise surface normal

		glm::vec3 vertex_normals = normalise(normalised_surface);

		normals.push_back(vertex_normals);
	}

	GLuint vertex_buffer_length = vertices.size();
	GLuint texture_buffer_length = texcoords.size();
	GLuint normals_buffer_length = normals.size();
	element_buffer_length = indices.size();

	//for(GLuint i = 0; i < normals.size(); i++) std::cout << normals[i].x + normals[i].y + normals[i].z << std::endl;

	//--------Vertex buffer--------//
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertex_buffer_length, &vertices[0], GL_STATIC_DRAW);
	//-----------------------------//

	//--------Texture buffer-------//
	glGenBuffers(1, &texturebuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texturebuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * texture_buffer_length, &texcoords[0], GL_STATIC_DRAW);
	//-----------------------------//

	//--------Normals buffer-------//
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals_buffer_length, &normals[0], GL_STATIC_DRAW);
	//----------------------------//

	//-------Element buffer--------//
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * element_buffer_length, &indices[0], GL_STATIC_DRAW);
	//-----------------------------//

	// Clear vectors
	vertices.clear();
	texcoords.clear();
	normals.clear();
	indices.clear();
}

SphereAsset::~SphereAsset()
{
	// TODO Auto-generated destructor stub
}

glm:: vec3 SphereAsset::normalise(glm::vec3 v)
{
	glm::vec3 normalised_vector;

	GLfloat d = std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));	// length of vertex

	if(d != 0.0)
	{
		v.x /= d;	// normalise x
		v.y /= d;	// normalise y
		v.z /= d;	// normalise z

		normalised_vector = glm::vec3(v.x, v.y, v.z);
	}
	return normalised_vector;
}

glm::mat4 SphereAsset::rotate_x(GLfloat theta)
{
	return glm::mat4(
			glm::vec4(1.0, 0.0, 0.0, 0.0),
			glm::vec4(0.0, cos(theta), -sin(theta), 0.0),
			glm::vec4(0.0, sin(theta), cos(theta), 0.0),
			glm::vec4(0.0, 0.0, 0.0, 1.0)
		);
}

glm::mat4 SphereAsset::rotate_y(float theta)
{
	return glm::mat4(
			glm::vec4(cos(theta), 0.0, sin(theta), 0.0),
			glm::vec4(0.0, 1.0, 0.0, 0.0),
			glm::vec4(-sin(theta), 0.0, cos(theta), 0.0),
			glm::vec4(0.0, 0.0, 0.0, 1.0)
		);
}

void SphereAsset::Draw(GLuint program_token)
{
	glUseProgram(program_token);

	if(rotate_angle >= 0.0)
	{
		rotate_angle++;
	}
	else if(rotate_angle > 360.0)
	{
		rotate_angle = 0.0;
	}

	// create model matrix
	glm::mat4 model_matrix = rotate_y(glm::radians(rotate_angle)) * rotate_x(glm::radians(90.0)) *  glm::translate(glm::mat4(1.0f), glm::vec3(x_pos, y_pos, z_pos));
	GLuint model_attrib = glGetUniformLocation(program_token, "model_matrix");
	// Send model matrix to vertex shader
	glUniformMatrix4fv(model_attrib, 1, GL_FALSE, &model_matrix[0][0]);

	// Comment out the following line to make sphere solid
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// Display as wireframe

	GLuint position_attrib = glGetAttribLocation(program_token, "position");
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


	GLuint normals_attrib = glGetAttribLocation(program_token, "normals");
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
			normals_attrib,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);
	glEnableVertexAttribArray(normals_attrib);

	GLuint texture_attrib = glGetUniformLocation(program_token, "texSampler");
	glProgramUniform1i(program_token, texture_attrib, 0);	// Send texture to shader

	GLuint texCoord_attrib = glGetAttribLocation(program_token, "texCoords");
	glBindBuffer(GL_ARRAY_BUFFER,texturebuffer);
	glVertexAttribPointer(
			texCoord_attrib,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);
	glEnableVertexAttribArray(texCoord_attrib);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glDrawElements(
				GL_TRIANGLE_STRIP,
				element_buffer_length,
				GL_UNSIGNED_SHORT,
				(GLvoid*)0
				);

	glDisableVertexAttribArray(position_attrib);
	glDisableVertexAttribArray(texture_attrib);
	glDisableVertexAttribArray(normals_attrib);
}

