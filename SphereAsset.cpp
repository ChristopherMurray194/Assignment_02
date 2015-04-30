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

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	std::vector<GLushort> indices;

	calcVerticesAndTexCoords(stacks, slices, radius, vertices, texcoords); // Calculate vertex and texture coordinates

	calcIndices(stacks, slices, indices);

	normaliseVertices(stacks, slices, vertices, normals);	// Calculate the vertex normals

	GLuint vertex_buffer_length = vertices.size();
	GLuint texture_buffer_length = texcoords.size();
	GLuint normals_buffer_length = normals.size();
	indices_buffer_length = indices.size();

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
	glGenBuffers(1, &indicesbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices_buffer_length, &indices[0], GL_STATIC_DRAW);
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

void SphereAsset::calcVerticesAndTexCoords(const GLuint stacks, const GLuint slices, const GLfloat radius, std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &texcoords)
{
	const GLfloat PI = 3.1415926535;	// define PI
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

			GLfloat d = std::sqrt((x * x) + (y * y) + (z * z));	// magnitude of vector

			if(d != 0.0)
			{
			/*
			 * Generate UV coordinates
			 * Calculate UV method from http://sol.gfxile.net/sphere/
			 */
			GLfloat U = (atan2(y, x) / PI + 1.0f) * 0.5;
			GLfloat V = acos(z / d) / PI;

			texcoords.push_back(glm::vec2(U, V));

			}
		}
	}
}

void SphereAsset::calcIndices(const GLuint stacks, const GLuint slices, std::vector<GLushort> &indices)
{
	for(GLuint i = 0; i < stacks; i++)
	{
		for(GLuint j = 0; j  <= slices; j++)
		{
			indices.push_back((i * slices) + (j % slices));
			indices.push_back(((i + 1) * slices) + (j % slices));
			indices.push_back((i * slices) + (j % slices) +1);
			indices.push_back((i * slices) + (j % slices) +1);
			indices.push_back(((i + 1) * slices) + (j % slices));
			indices.push_back(((i + 1) * slices) + (j % slices) +1);
		}
	}
}

glm::vec3 SphereAsset::normalise(const glm::vec3 &v)
{
	GLfloat magnitude = glm::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));	// Get the magnitude of the vector
	return glm::vec3(v.x / magnitude, v.y / magnitude, v.z / magnitude);	// Normalize and return
}

void SphereAsset::normaliseVertices(const GLuint stacks, const GLuint slices, const std::vector<glm::vec3> vertices, std::vector<glm::vec3> &normals)
{
	for(GLuint i = 1; i < stacks; i++)
	{
		for(GLuint j = 1; j <= slices; j++)
		{
			// Get the indices for the adjacent vertices to pi (the vertex we want to normalize)
			GLushort pi = ((i * slices) + (j % slices));
			GLushort li = pi -1;									// left vertex index
			GLushort ri = pi +1;									// right vertex index
			GLushort di = ((i + 1) * slices) + (j % slices);		// down vertex index
			GLushort ui = ((i - 1) * slices) + (j % slices);		// up vertex index

			glm::vec3 up = vertices[ui];							// up vertex
			glm::vec3 right = vertices[ri];							// right vertex
			glm::vec3 down = vertices[di];							// down vertex
			glm::vec3 left = vertices[li];							// left vertex

			glm::vec3 N1 = normalise(glm::cross(up, left));			// Adjacent triangle normal 1
			glm::vec3 N2 = normalise(glm::cross(up, right));		// Adjacent triangle normal 2
			glm::vec3 N3 = normalise(glm::cross(right, down));		// Adjacent triangle normal 3
			glm::vec3 N4 = normalise(glm::cross(left, down));		// Adjacent triangle normal 4

			glm::vec3 sum = (N1 + N2 + N3 + N4);

			glm::vec3 vertex_normal = normalise(sum);

			normals.push_back(vertex_normal);
		}
	}
}

glm::mat4 SphereAsset::rotate_x(GLfloat theta)
{
	return glm::mat4(
			glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, cos(theta), -sin(theta), 0.0f),
			glm::vec4(0.0f, sin(theta), cos(theta), 0.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		);
}

glm::mat4 SphereAsset::rotate_y(float theta)
{
	return glm::mat4(
			glm::vec4(cos(theta), 0.0f, sin(theta), 0.0f),
			glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
			glm::vec4(-sin(theta), 0.0f, cos(theta), 0.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		);
}

void SphereAsset::Draw(GLuint program_token)
{
	if(rotate_angle >= 0.0f)
	{
		rotate_angle++;
	}
	else if(rotate_angle > 360.0f)
	{
		rotate_angle = 0.0f;
	}

	// create model matrix
	glm::mat4 model_matrix = rotate_y(glm::radians(rotate_angle)) * rotate_x(glm::radians(90.0f)) *  glm::translate(glm::mat4(1.0f), glm::vec3(x_pos, y_pos, z_pos));
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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesbuffer);
	glDrawElements(
				GL_TRIANGLES,
				indices_buffer_length,
				GL_UNSIGNED_SHORT,
				(GLvoid*)0
				);

	glDisableVertexAttribArray(position_attrib);
	glDisableVertexAttribArray(texture_attrib);
	glDisableVertexAttribArray(normals_attrib);

	glUseProgram(program_token);
}
