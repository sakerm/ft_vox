#pragma once

# define FOV 80.0f
# define VIEW_DISTANCE 160.0f * 1.4f + 32.0f
# define Wscreen 2560
# define Hscreen 1440

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Maths.hpp"
#include "FrustumCulling.hpp"

class Player
{
	public:
		Player();
		~Player();
		glm::vec3		GetPos();
		void			mouseControl(GLFWwindow *window);
		glm::mat4		mvp;
		FrustumCulling	*frustum;
		glm::mat4		Projection;
		glm::mat4		View;
	private:
		glm::mat4		Model;
		glm::vec3		position;
		float			horizontalAngle;
		float			verticalAngle;
		float			initialFoV;
		float			speed;
		float			mouseSpeed;
};

extern float					g_deltaTime;
extern Player					g_player;
