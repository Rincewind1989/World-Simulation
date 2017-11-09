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

	void setTemperature(
		double temperature);

	void addTemperature(
		double temperature);

	double getTemperature();

	void setHeatEnergyProduction(
		double heatEnergyProduction);

	double getHeatEnergyProduction();

	void setSize(
		double size);

	double getSize();

	void setRed(
		int red);

	double getRed();

	void setGreen(
		int green);

	double getGreen();

	void setBlue(
		int blue);

	double getBlue();

	void setAlpha(
		int transparency);

	double getAlpha();


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
	double m_size = 1.0;

	int m_red = randomInt(0,255);
	int m_green = randomInt(0, 255);
	int m_blue = randomInt(0, 255);
	int m_alpha = randomInt(128, 255);

	//Body funtionalities
	double m_energyHeatProduction = ENERGY_HEAT_PRODUCTION;
	double m_heatLoss = HEAT_LOSS_FACTOR;

	//Condition
	double m_energy = STARTING_ENERGY;
	double m_temperature = STARTING_TEMPERATURE;
};

