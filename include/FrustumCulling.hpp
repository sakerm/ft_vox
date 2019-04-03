#pragma once

#include "Maths.hpp"
#include <iostream>

class FrustumCulling
{
	public:
		FrustumCulling(glm::mat4 projection);
		bool		pointIn(glm::vec3 pos);
		void		setPlanes();
		void		setView(glm::mat4 view);
	private:
		glm::mat4	projection;
		glm::mat4	view;
		float		**planes;
};