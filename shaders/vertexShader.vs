#version 330 core

layout(location = 0) in vec3 vPosition;

void main()
{
	gl_position.xyz = vPosition;
	gl_position.w = 1.0;
}