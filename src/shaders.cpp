/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:28:07 by lvasseur          #+#    #+#             */
/*   Updated: 2019/03/07 13:58:08 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.hpp"
#include <vector>

shaders::shaders()
{

}

shaders::~shaders()
{

}

static char	*strjoin(const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (s1 && s2)
	{
		if ((str = (char*)malloc(sizeof(char) * (strlen(s1) +
						strlen(s2) + 1))) == 0)
			return (NULL);
		i = 0;
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		j = 0;
		while (s2[j])
			str[i++] = s2[j++];
		str[i] = '\0';
		return (str);
	}
	else
		return (NULL);
}

static char	*strnew(size_t size)
{
	char	*str;

	if ((str = (char*)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	while (size != (size_t)-1)
		str[size--] = '\0';
	return (str);
}

char		*shaders::load_file(char *filename)
{
	char	buf[BUFF_SIZE];
	char	*file;
	char	*tmp;
	int		r;
	int		fd;

	file = strnew(BUFF_SIZE);
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		std::cout << "Failed to get a fd" << std::endl;
		exit(0);
	}
	while ((r = read(fd, buf, BUFF_SIZE)))
	{
		buf[r] = '\0';
		tmp = file;
		file = strjoin(file, buf);
		free(tmp);
	}
	close(fd);
	return (file);
}

GLuint		shaders::create_shader(char *filename, int shadertype)
{
	GLuint		shader;
	char		*file;
	GLint		success;

	success = 0;
	shader = glCreateShader(shadertype);
	file = load_file(filename);
	glShaderSource(shader, 1, (const char **)&file, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		std::cout << "Failed to compile shader" << std::endl;
		exit(0);
	}
	free(file);
	return (shader);
}

GLuint		shaders::create_program(GLuint vertex, GLuint fragment)
{
	GLuint		program_id;
	GLint		success;
	int			maxLength;

	success = 0;
	program_id = glCreateProgram();
	glAttachShader(program_id, vertex);
	glAttachShader(program_id, fragment);
	glLinkProgram(program_id);
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorlog(maxLength);
		glGetProgramInfoLog(program_id, maxLength, &maxLength, &errorlog[0]);
		std::cout << "Failed to link program: " << &errorlog[0] << std::endl;
		exit(0);
	}
	glDetachShader(program_id, vertex);
	glDetachShader(program_id, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return (program_id);
}
