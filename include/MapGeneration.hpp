#pragma once

#include <cstdlib>
#include <ctime>
#include <cmath>

class MapGeneration
{
	public:
		MapGeneration();
		MapGeneration(unsigned int seed);
		~MapGeneration();
		unsigned int	seed;
		float	noise(float x, float y, float z);
		float	OctavePerlin(float x, float y, float z, int octaves, float persistence);
	private:
		int				*p;
};