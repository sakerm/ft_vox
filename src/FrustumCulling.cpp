#include "FrustumCulling.hpp"

FrustumCulling::FrustumCulling(glm::mat4 projection) : projection(projection)
{
	view = glm::mat4(1.0);
	planes = new float*[6];
	for (int i = 0; i < 6; i++)
		planes[i] =  new float[4];
}

void	FrustumCulling::setView(glm::mat4 v)
{
	this->view = v;
}

void	FrustumCulling::setPlanes()
{
	glm::mat4 matrix = projection * view;

	planes[0][0] = matrix[0][3] + matrix[0][0];
	planes[0][1] = matrix[1][3] + matrix[1][0];
	planes[0][2] = matrix[2][3] + matrix[2][0];
	planes[0][3] = matrix[3][3] + matrix[3][0];
	
	planes[1][0] = matrix[0][3] - matrix[0][0];
	planes[1][1] = matrix[1][3] - matrix[1][0];
	planes[1][2] = matrix[2][3] - matrix[2][0];
	planes[1][3] = matrix[3][3] - matrix[3][0];
	
	planes[2][0] = matrix[0][3] - matrix[0][1];
	planes[2][1] = matrix[1][3] - matrix[1][1];
	planes[2][2] = matrix[2][3] - matrix[2][1];
	planes[2][3] = matrix[3][3] - matrix[3][1];
	
	planes[3][0] = matrix[0][3] + matrix[0][1];
	planes[3][1] = matrix[1][3] + matrix[1][1];
	planes[3][2] = matrix[2][3] + matrix[2][1];
	planes[3][3] = matrix[3][3] + matrix[3][1];
	
	planes[4][0] = matrix[0][3] + matrix[0][2];
	planes[4][1] = matrix[1][3] + matrix[1][2];
	planes[4][2] = matrix[2][3] + matrix[2][2];
	planes[4][3] = matrix[3][3] + matrix[3][2];
	
	planes[5][0] = matrix[0][3] - matrix[0][2];
	planes[5][1] = matrix[1][3] - matrix[1][2];
	planes[5][2] = matrix[2][3] - matrix[2][2];
	planes[5][3] = matrix[3][3] - matrix[3][2];

	float	fscale;
	for (int i = 0; i < 6; i++)
	{
		fscale = sqrtf(planes[i][0] * planes[i][0] + planes[i][1] * planes[i][1] + planes[i][2] * planes[i][2]);
		planes[i][0] /= fscale;
		planes[i][1] /= fscale;
		planes[i][2] /= fscale;
		planes[i][3] /= fscale;
	}
}

static float	distance(glm::vec3 v1, glm::vec3 v2, float d)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + d);
}

bool		FrustumCulling::pointIn(glm::vec3 pos) {
	glm::vec3	plane;

	for(int i = 0; i < 6; i++)
	{
		plane = glm::vec3(planes[i][0], planes[i][1], planes[i][2]);
		if(distance(plane, pos, planes[i][3]) <= -pos.y)
			return false;
	}
	return true;
}