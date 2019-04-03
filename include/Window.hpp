#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "VoxException.hpp"
#include "ChunkHandler.hpp"
#include "shaders.hpp"
#include "Texture.hpp"

class Window
{
	public:
		Window();
		~Window();
		void	init();
		void	loop(bool is_seed, unsigned int seed);
	private:
		GLFWwindow		*window;
		void			handleTime();
		void			create_skybox();
		void			loadSkybox();
		GLuint			vaoID;
		GLuint			skyboxVaoID;
		GLuint			programID;
		GLuint			skybox_programID;
		GLuint			skyboxVBO;
		shaders			s;
		Texture			texture;
		GLuint			MatrixID;
		GLuint			SkyboxProjectionID;
		GLuint			SkyboxViewID;
		GLuint			grassID;
		GLuint			stoneID;
		GLuint			sandID;
		GLuint			waterID;
		GLuint			skyboxID;
		GLuint			grass;
		GLuint			stone;
		GLuint			sand;
		GLuint			water;
		GLuint			skybox;
};
