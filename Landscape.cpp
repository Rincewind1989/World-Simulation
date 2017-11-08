#include "Landscape.h"
#include "Perlin Noise.h"



Landscape::Landscape()
{
	m_height = SIMULATION_Y;
	m_width = SIMULATION_X;

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			Tile tmp2;
			double noise = ValueNoise_2D(x, y);
			tmp2.setHeight(noise);
			m_tiles[y][x] = tmp2;
		}
	}
}


Landscape::~Landscape()
{
}


//Returns the vector of vector of tiles of this landscape
vector<vector<Tile>> &Landscape::getTiles()
{
	return m_tiles;
}


//Returns a tile of the landscape by its index
Tile &Landscape::getTilesByIndex(int x, int y)
{
	return m_tiles[y][x];
}


//Random engine call
double Landscape::randomReal(
	const double lowerBoundary,
	const double upperBoundary)
{
	uniform_real_distribution<double> distribution_real(lowerBoundary, upperBoundary);
	return distribution_real(mersenne_generator);
}

int Landscape::randomInt(
	const int lowerBoundary,
	const int upperBoundary)
{
	uniform_int_distribution<int> distribution_int(lowerBoundary, upperBoundary);
	return distribution_int(mersenne_generator);
}

//Random engine initialisation
random_device Landscape::seed_generator;
unsigned Landscape::seed = seed_generator();
mt19937 Landscape::mersenne_generator(Landscape::seed);
