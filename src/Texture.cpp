#include "Texture.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

Texture::Texture()
{

}

Texture::~Texture()
{

}

GLuint	Texture::load_cubemap(char *top_name, char *side_name, char *bot_name)
{
	unsigned int	width;
	unsigned int	height;
	GLuint	texture_id;
	unsigned char *top_data;
	unsigned char *side_data;
	unsigned char *bot_data;

	top_data = load_bmp(top_name, &width, &height);
	side_data = load_bmp(side_name, &width, &height);
	bot_data = load_bmp(bot_name, &width, &height);
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_BGR,
				GL_UNSIGNED_BYTE, side_data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_BGR,
				GL_UNSIGNED_BYTE, side_data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_BGR,
				GL_UNSIGNED_BYTE, top_data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_BGR,
				GL_UNSIGNED_BYTE, bot_data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_BGR,
				GL_UNSIGNED_BYTE, side_data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_BGR,
				GL_UNSIGNED_BYTE, side_data);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	free(top_data);
	free(bot_data);
	free(side_data);
	return texture_id;
}

GLuint	Texture::load_skybox(char *top_name, char *left_name, char *right_name, char *back_name, char *front_name, char *bot_name)
{
	int	width;
	int	height;
	int	nrChannels;
	GLuint	texture_id;
	unsigned char *top_data;
	unsigned char *right_data;
	unsigned char *left_data;
	unsigned char *front_data;
	unsigned char *back_data;
	unsigned char *bot_data;

	top_data = stbi_load(top_name, &width, &height, &nrChannels, 0);
	right_data = stbi_load(right_name, &width, &height, &nrChannels, 0);
	left_data = stbi_load(left_name, &width, &height, &nrChannels, 0);
	front_data = stbi_load(front_name, &width, &height, &nrChannels, 0);
	back_data = stbi_load(back_name, &width, &height, &nrChannels, 0);
	bot_data = stbi_load(bot_name, &width, &height, &nrChannels, 0);
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB,
				GL_UNSIGNED_BYTE, right_data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB,
				GL_UNSIGNED_BYTE, left_data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB,
				GL_UNSIGNED_BYTE, top_data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB,
				GL_UNSIGNED_BYTE, bot_data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB,
				GL_UNSIGNED_BYTE, front_data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB,
				GL_UNSIGNED_BYTE, back_data);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	free(top_data);
	free(right_data);
	free(left_data);
	free(front_data);
	free(back_data);
	free(bot_data);
	return texture_id;
}

unsigned char	*Texture::load_bmp(char *filename, unsigned int *width, unsigned int *height)
{
	int				fd;
	unsigned char	header[54];
	unsigned int	datapos;
	unsigned int	image_size;
	unsigned char	*data;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		std::cout << "not a correct BMP file !" << std::endl;
		exit(0);
	}
	if (read(fd, header, 54) != 54)
	{
		std::cout << "not a correct BMP file !" << std::endl;
		exit(0);
	}
	if (header[0] != 'B' || header[1] != 'M')
	{
		std::cout << "not a correct BMP file !" << std::endl;
		exit(0);
	}
	datapos = *(int*)&(header[0x0A]);
	image_size = *(int*)&(header[0x22]);
	*width = *(int*)&(header[0x12]);
	*height = *(int*)&(header[0x16]);
	if (image_size == 0)
		image_size = (*width) * (*height) * 3;
	if (datapos == 0)
		datapos = 54;
	data = (unsigned char*)malloc(sizeof(unsigned char) * image_size);
	read(fd, data, image_size);
	close(fd);
	return data;
}
