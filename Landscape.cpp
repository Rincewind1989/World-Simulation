#include "Landscape.h"
#include "Perlin Noise.h"



Landscape::Landscape()
{
	m_SmiulationHeight = SIMULATION_Y;
	m_SimulationWidth = SIMULATION_X;
	float max = 0, min = 0;

	//Using the Perlin Noise to get a height map
	for (int y = 0; y < m_SmiulationHeight; y++)
	{
		for (int x = 0; x < m_SimulationWidth; x++)
		{
			double noise = ValueNoise_2D(x, y);
			m_tiles[y][x].setHeight(noise);
			if (noise > max) { max = noise; }
			if (noise < min) { min = noise; }
		}
	}

	//Parameter settings
	m_heightMax = max;
	m_heightMin = min;

	//Reseeding the Perlin noise
	random_device seed_generator;
	unsigned seed = seed_generator();
	mt19937 mersenne_generator(seed);
	uniform_real_distribution<double> distribution_real(0.4, 0.8);
	persistence = distribution_real(mersenne_generator);
	uniform_int_distribution<int> distribution_int(0, maxPrimeIndex - 1);
	primeIndex = distribution_int(mersenne_generator);

	//Using the Perlin Noise to get a temperature map
	for (int y = 0; y < m_SmiulationHeight; y++)
	{
		for (int x = 0; x < m_SimulationWidth; x++)
		{
			double noise = ValueNoise_2D(x, y);
			if (m_tiles[y][x].getHeight() > 0)
			{
				m_tiles[y][x].setTemperature(m_tiles[y][x].getHeight() * (-1) * 100 + noise * 5.0 + 25.0);
			}
			else
			{
				m_tiles[y][x].setTemperature(noise * 7.5 + 3.0);
			}
			
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
Tile &Landscape::getTilesByIndex(
	int x, 
	int y)
{
	return m_tiles[y][x];
}


//Returns the maximum and minimum height value for this simulation
vector<double> Landscape::getHeightMaxMin()
{
	vector<double> tmp;
	tmp.push_back(m_heightMax);
	tmp.push_back(m_heightMin);
	return tmp;
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