#pragma once

#include <random>

#include "SimulationData.h"
#include "NeuralNetwork.h"

using namespace std;

class Organism
{
public:
	Organism();
	Organism(Organism &father, Organism &mother);
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

	void addEnergyViaFood(
		double food);

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

	double &getFitness();

	void setFitness(double &fitness);

	void addFitness(double &fitness);

	NeuralNetwork &getNeuralNetwork();


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
	double _positionX;
	double _positionY;
	double _size = 1.0;

	int _red = randomInt(0,255);
	int _green = randomInt(0, 255);
	int _blue = randomInt(0, 255);
	int _alpha = randomInt(128, 255);

	double _fitness = 0.0;

	//Body funtionalities
	double _energyHeatProduction = ENERGY_HEAT_PRODUCTION;
	double _heatLoss = HEAT_LOSS_FACTOR;
	double _foodEnergyFactor = FOOD_ENERGY_FACTOR;

	//Condition
	double _energy = STARTING_ENERGY;
	double _temperature = STARTING_TEMPERATURE;

	//Brain...kind of
	NeuralNetwork _neuralNetwork;
};

