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
	//----------------------------------------------------------------------
	//Returns the vector of vector of tiles of this landscape
	vector<vector<Tile>> &getTiles();
	//----------------------------------------------------------------------
	//Returns a tile of the landscape by its index
	Tile &getTilesByIndex(int x, int y);
	//----------------------------------------------------------------------
	//Returns the maximum and minimum height value for this simulation
	vector<double> getHeightMaxMin();
	//----------------------------------------------------------------------
	//Random generator 
	double randomReal(const double lowerBoundary,const double upperBoundary);
	int randomInt(const int lowerBoundary,const int upperBoundary);
	static random_device seed_generator;
	static unsigned seed;
	static mt19937 mersenne_generator;
private:
	vector<vector<Tile>> _tiles = vector<vector<Tile>>(SIMULATION_Y, vector<Tile>(SIMULATION_X));
	//----------------------------------------------------------------------
	//Height map properties
	double _heightMax;
	double _heightMin;
};

