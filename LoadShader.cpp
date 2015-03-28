/*
 * LoadShader.cpp
 *
 *  Created on: 27 Mar 2015
 *      Author: cmurray
 */

#include "LoadShader.h"

LoadShader::LoadShader() {
	std::string vertex_shader("shaders/vertexShader.vs");
	std::string fragment_shader("shaders/fragment shader.fs");

	program_token = LoadShaders(vertex_shader.c_str(), fragment_shader.c_str());
}

LoadShader::~LoadShader() {
	glDeleteProgram(program_token);
}

GLint LoadShader::getProgram_token()
{
	return program_token;
}

std::string LoadShader::readShader(const char* filePath)
{
	// Read the shader code from the file
	std::string shaderCode;
	std::ifstream shaderStream(filePath, std::ios::in); // Read file

	if(shaderStream.is_open())	// check the file opened correctly
	{
		std::string line = "";
		while(getline(shaderStream, line)) shaderCode += "\n" + line;
		shaderStream.close();	// close file
	}
	else
	{
		std::cout << "The file: " << filePath << " cannot be opened. File does not exist!";
	}
	return shaderCode;
}


GLuint LoadShader::LoadShaders(const char * vertex_file_path,const char * fragment_file_path)
{
	// Create the shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderStr = readShader(vertex_file_path);
	std::string fragmentShaderStr = readShader(fragment_file_path);
	const char * vertexSource = vertexShaderStr.c_str();
	const char * fragmentSource = fragmentShaderStr.c_str();

	GLint result = GL_FALSE;

	// Compile vertex shader
	std::cout << "Compiling vertex shader." << std::endl;
	glShaderSource(vertexShaderID, 1, &vertexSource, NULL);
	glCompileShader(vertexShaderID);

	// Check vertex shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	if(!result) // If compilation fails
	{
		GLint infoLogLength;
		glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);	// Query log length
		std::vector<GLchar> vertexShaderErrorMessage(infoLogLength);		// allocate sufficient memory
		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);	// get log
		std::cout << &vertexShaderErrorMessage[0] << std::endl;	// print the log to console

		// Exit with failure
		glDeleteShader(vertexShaderID);	// Don't leak the shader
		exit(-1);
	}

	// Compile fragment shader
	std::cout << "Compiling fragment shader." << std::endl;
	glShaderSource(fragmentShaderID, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShaderID);

	// Check fragment shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	if(!result)	// If compilation fails
	{
		GLint infoLogLength;
		glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<GLchar> fragmentShaderErrorMessage(infoLogLength);
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		std::cout << &fragmentShaderErrorMessage[0] << std::endl;

		// Exit with failure
		glDeleteShader(vertexShaderID);		// Don't leak the shader
		glDeleteShader(fragmentShaderID);	// Don't leak the shader
		exit(-1);
	}

	// Shaders compiled successfully.
	std::cout << "Shaders compiled successfully.";

	// link the program
	std::cout << "Linking the program." << std::endl;
	GLuint programID = glCreateProgram();			// Create a program object
	glAttachShader(programID, vertexShaderID);		// attach shader to program
	glAttachShader(programID, fragmentShaderID);	// attach shader to program
	glLinkProgram(programID);						// Link the program

	// check the program has linked
	GLint isLinked = GL_FALSE;
	glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);
	if(!isLinked)
	{
		GLint infoLogLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<GLchar> programErrorMessage(infoLogLength);
		glGetShaderInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		std::cout << &programErrorMessage[0] << std::endl;

		// Exit with failure
		glDeleteProgram(programID); // Don't leak the program
		// Don't leak the shaders either
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		exit(-1);
	}

	// Always detach shaders after a successful link;
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}
