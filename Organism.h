#pragma once

#include <random>

#include "SimulationData.h"

using namespace std;

class Organism
{
public:
	Organism();
	~Organism();

	//Getters/Setters
	void setPositionX(
		double positionX);

	void addPositionX(
		double positionX);

	double getPositionX();

	void setPositionY(
		double positionY);

	void addPositionY(
		double positionY);

	double getPositionY();

	void setEnergy(
		double energy);

	void addEnergy(
		double energy);

	double getEnergy();

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

	//Organism Properties
	//X-Y Position
	double m_positionX;
	double m_positionY;

	//Condition
	double m_energy = 100.0;
	double temperature = 25.0;
};

