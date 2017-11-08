#pragma once

#include <random>
#include <vector>
#include "Tile.h"
#include "SimulationData.h"


using namespace std;

class Landscape
{
public:
	Landscape();
	~Landscape();

	vector<vector<Tile>> &getTiles();

	Tile &getTilesByIndex(int x, int y);

	//Random generator 
	double randomReal(
		const double lowerBoundary,
		const double upperBoundary);

	int randomInt(
		const int lowerBoundary,
		const int upperBoundary);

	static random_device seed_generator;
	static unsigned seed;
	static mt19937 mersenne_generator;

private:
	int m_height;
	int m_width;
	vector<vector<Tile>> m_tiles = vector<vector<Tile>>(SIMULATION_Y, vector<Tile>(SIMULATION_X));
};

