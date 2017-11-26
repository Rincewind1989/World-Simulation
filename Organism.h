#pragma once

#include <random>

#include "SimulationData.h"
#include "NeuralNetwork.h"

using namespace std;

class Organism
{
public:
	Organism();

	//Asexual breeding for an organism
	Organism asexualBreeding();

	//Sexuell breeding
	Organism(const Organism &father, const Organism &mother);
	~Organism();

	//Mutates the color of the organism by chance
	double mutateStat(double colorValue);

	//Getters/Setters
	void setPositionX(const double &positionX);

	void addPositionX(const double &positionX);

	const double &getPositionX() const;

	void setPositionY(const double &positionY);

	void addPositionY(const double &positionY);

	const double &getPositionY() const;

	void setEnergy(const double &energy);

	void addEnergy(const double &energy);

	void addEnergyViaFood(const double &food);

	const double &getEnergy() const;

	void setTemperature(const double &temperature);

	void addTemperature(const double &temperature);

	const double &getTemperature();

	void setHeatEnergyProduction(const double &heatEnergyProduction);

	const double getHeatEnergyProduction() const;

	void setHeatLossFactor(const double &heatLossFactor);

	const double &getHeatLossFactor() const;

	void setSize(const double &size);

	const double &getSize() const;

	void setRed(const int &red);

	const double &getRed() const;

	void setGreen(const int &green);

	const double &getGreen() const;

	void setBlue(const int &blue);

	const double &getBlue() const;

	void setAlpha(const int &transparency);

	const double &getAlpha() const;

	const double &getFitness() const;

	void setFitness(const double &fitness);

	void addFitness(const double &fitness);

	void setDied(const bool dead);

	bool getDied();

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

	//Brain...kind of
	NeuralNetwork _neuralNetwork;

private:

	//Organism Properties
	//X-Y Position
	double _positionX;
	double _positionY;

	int _red;
	int _green;
	int _blue;
	int _alpha;

	double _fitness = 0.0;

	double _size = SIZE_ORGANISM;

	//Body funtionalities
	double _energyHeatProduction = ENERGY_HEAT_PRODUCTION;
	double _heatLoss = HEAT_LOSS_FACTOR;
	double _foodEnergyFactor = FOOD_ENERGY_FACTOR;

	//Condition
	double _energy = STARTING_ENERGY;
	double _temperature = STARTING_TEMPERATURE;
	bool _dead = false;

};

