/*
 * LoadShader.h
 *
 *  Created on: 27 Mar 2015
 *      Author: cmurray
 */

#ifndef LOADSHADER_H_
#define LOADSHADER_H_

#include <iostream>

#include <fstream>
#include <GL/glew.h>
#include <vector>

class LoadShader {
public:
	LoadShader();
	virtual ~LoadShader();

	GLint getProgram_token();
private:
	/**
	 * Read the shader files
	 */
	std::string readShader(const char*);

	/**
	 * Handles loading of the shaders
	 */
	GLuint LoadShaders(const char*, const char*);

	GLint program_token;
};

#endif /* LOADSHADER_H_ */
