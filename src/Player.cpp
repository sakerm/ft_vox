#include "Player.hpp"

#include <iostream>

Player::Player()
{
	Projection = glm::perspective(glm::radians(FOV), (float)Wscreen / (float)Hscreen, 0.1f, VIEW_DISTANCE);
	frustum = new FrustumCulling(Projection);
	View = glm::lookAt(
			glm::vec3(4,6,3),
			glm::vec3(0,1,0),
			glm::vec3(0,1,0)
		);
	frustum->setView(View);
	frustum->setPlanes();
	Model = glm::mat4(1.0f);
	mvp = Projection * View * Model;
	position = glm::vec3(0,140,0);
	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	initialFoV = FOV;
	speed = 1.0f;
	mouseSpeed = 0.05f;
}

Player::~Player()
{
	delete(frustum);
}

void	Player::mouseControl(GLFWwindow *window)
{
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);
	horizontalAngle += mouseSpeed * g_deltaTime * float(Wscreen/2 - x);
	verticalAngle += mouseSpeed * g_deltaTime * float(Hscreen/2 - y);
	glm::vec3 direction(
    	cos(verticalAngle) * sin(horizontalAngle),
   		sin(verticalAngle),
   		cos(verticalAngle) * cos(horizontalAngle)
	);
	glm::vec3 right = glm::vec3(
    	sin(horizontalAngle - 3.14f/2.0f),
    	0,
    	cos(horizontalAngle - 3.14f/2.0f)
	);
	glm::vec3 up = glm::cross(right, direction);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	    position += direction * g_deltaTime * speed;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	    position -= direction * g_deltaTime * speed;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	    position += right * g_deltaTime * speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	    position -= right * g_deltaTime * speed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	    position.y += g_deltaTime * speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	    position.y -= g_deltaTime * speed;
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS && speed < 20.0f)
		speed = 20.0f;
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS && speed > 1.0f)
		speed = 1.0f;
	View = glm::lookAt(position, position+direction, up);
	frustum->setView(View);
	frustum->setPlanes();
	mvp = Projection * View * Model;
	glfwSetCursorPos(window, Wscreen/2, Hscreen/2);
}

glm::vec3	Player::GetPos()
{
	return position;
}
