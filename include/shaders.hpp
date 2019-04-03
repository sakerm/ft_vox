#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

# define BUFF_SIZE 64

class shaders
{
	public:
		shaders();
		~shaders();
		char		*load_file(char *filename);
		GLuint		create_shader(char *filename, int shadertype);
		GLuint		create_program(GLuint vertex, GLuint fragment);
};