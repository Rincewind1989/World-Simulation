#include "Landscape.h"
#include "PerlinNoise.h"



Landscape::Landscape()
{
	//Creating the random generator for seeding the perlin noise
	random_device seed_generator;
	unsigned seed = seed_generator();
	mt19937 mersenne_generator(seed);
	uniform_int_distribution<int> distribution_int(0, 10000000);
	seed = distribution_int(mersenne_generator);

	//Creating the perlin noise
	PerlinNoise perlin(seed);
	const double fx = SIMULATION_X / FREQUENCY;
	const double fy = SIMULATION_Y / FREQUENCY;
	
	//Save max and min height for later calculations
	float max = 0, min = 0;

	//Using the Perlin Noise to get a height map
	for (int y = 0; y < SIMULATION_Y; y++)
	{
		for (int x = 0; x < SIMULATION_X; x++)
		{
			double height = (perlin.octaveNoise0_1(x / fx, y / fy, OCTAVES) - 0.5) * HEIGHT_MULITPLICATOR;
			_tiles[y][x].setHeight(height);
			if (height > max) { max = height; }
			if (height < min) { min = height; }
		}
	}

	//Parameter settings
	_heightMax = max;
	_heightMin = min;
	
	//Reseed the perlin noise for the temperature map
	perlin.reseed(distribution_int(mersenne_generator));

	//Getting the temperature based on the height map
	double optimumHeight = fabs(_heightMax * WATER_LEVEL + _heightMax * GRASS_LEVEL) / 2.0;
	double slope = (LOW_TEMPERATURE - OPT_TEMPERATURE) / (_heightMax - optimumHeight);
	for (int y = 0; y < SIMULATION_Y; y++)
	{
		for (int x = 0; x < SIMULATION_X; x++)
		{
			//Using the Perlin Noise to get a temperature map that is added on the height map temperature
			double noise = perlin.octaveNoise0_1(x / fx, y / fy, OCTAVES) - 0.5;
			if (_tiles[y][x].getHeight() > _heightMax * WATER_LEVEL)
			{
				_tiles[y][x].setTemperature(slope * fabs(_tiles[y][x].getHeight() - optimumHeight) + OPT_TEMPERATURE + noise * (OPT_TEMPERATURE - LOW_TEMPERATURE) / TEMPERATURE_FLUCTUATION_FACTOR);
				_tiles[y][x].setOrignTemperature(slope * fabs(_tiles[y][x].getHeight() - optimumHeight) + OPT_TEMPERATURE + noise * (OPT_TEMPERATURE - LOW_TEMPERATURE) / TEMPERATURE_FLUCTUATION_FACTOR);
			}
			else
			{
				_tiles[y][x].setTemperature(noise * 3.0 + 3.0);
				_tiles[y][x].setOrignTemperature(noise * 3.0 + 3.0);
			}
			
		}
	}

	//Reseed the perlin noise for the food map
	perlin.reseed(distribution_int(mersenne_generator));

	//Depending on the height and the temperature food is generated on every tile
	double food;
	for (int y = 0; y < SIMULATION_Y; y++)
	{
		for (int x = 0; x < SIMULATION_X; x++)
		{
			if (randomReal(0.0, 1.0) < CHANCE_FOOD_GROWTH)
			{
				double noise = perlin.octaveNoise0_1(x / fx, y / fy, OCTAVES) - 0.5;
				if (_tiles[y][x].getTemperature() * FOOD_TEMPERATURE_FACTOR + _tiles[y][x].getHeight() * FOOD_HEIGHT_FACTOR + noise * FOOD_NOISE_FACTOR > 0.0)
				{
					food = randomReal(0.0, _tiles[y][x].getTemperature() * FOOD_TEMPERATURE_FACTOR + _tiles[y][x].getHeight() * FOOD_HEIGHT_FACTOR + noise * FOOD_NOISE_FACTOR);
				}
				else
				{
					food = randomReal(_tiles[y][x].getTemperature() * FOOD_TEMPERATURE_FACTOR + _tiles[y][x].getHeight() * FOOD_HEIGHT_FACTOR + noise * FOOD_NOISE_FACTOR, 0.0);
				}
				if (_tiles[y][x].getHeight() > _heightMax * WATER_LEVEL)
				{
					if (food < 0)
					{
						_tiles[y][x].setFood(0.0);
					}
					else
					{
						_tiles[y][x].setFood(food);
					}
				}
				else
				{
					if (food < 0)
					{
						_tiles[y][x].setFood(food * (-1.0 / 2.0));
					}
					else
					{
						_tiles[y][x].setFood(food / 2.0);
					}
				}
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
	return _tiles;
}


//Returns a tile of the landscape by its index
Tile &Landscape::getTilesByIndex(
	int x, 
	int y)
{
	return _tiles[y][x];
}


//Returns the maximum and minimum height value for this simulation
vector<double> Landscape::getHeightMaxMin()
{
	vector<double> tmp;
	tmp.push_back(_heightMax);
	tmp.push_back(_heightMin);
	return tmp;
}


//Random engine call
double Landscape::randomReal(const double lowerBoundary, const double upperBoundary)
{
	uniform_real_distribution<double> distribution_real(lowerBoundary, upperBoundary);
	return distribution_real(mersenne_generator);
}

int Landscape::randomInt(const int lowerBoundary, const int upperBoundary)
{
	uniform_int_distribution<int> distribution_int(lowerBoundary, upperBoundary);
	return distribution_int(mersenne_generator);
}

//Random engine initialisation
random_device Landscape::seed_generator;
unsigned Landscape::seed = seed_generator();
mt19937 Landscape::mersenne_generator(Landscape::seed);