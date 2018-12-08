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

	//Mutates a stat of the organism by chance
	double mutateStat(double colorValue);

	//Getters/Setters
	void setPositionX(const double &positionX);
	void addPositionX(const double &positionX);
	const double &getPositionX() const;
	void setdeltaX(const double &deltaX);
	const double &getDeltaX() const;
	//----------------------------------------------------------------------
	void setPositionY(const double &positionY);
	void addPositionY(const double &positionY);
	const double &getPositionY() const;
	void setdeltaY(const double &deltay);
	const double &getDeltaY() const;
	//----------------------------------------------------------------------
	void setRotation(const double &rotation);
	void addRotation(const double &rotation);
	const double &getRotation() const;
	void setDeltaRotation(const double &rotation);
	const double &getDeltaRotation() const;
	//----------------------------------------------------------------------
	void setDeltaDistanceForward(const double &delta);
	void addDeltaDistanceForward(const double &rotation);
	const double &getDeltaDistanceForward() const;
	//----------------------------------------------------------------------
	void setEnergy(const double &energy);
	void addEnergy(const double &energy);
	void addEnergyViaFood(const double &food);
	const double &getEnergy() const;
	const double getMaxEnergy() const;
	const double getEnergyViaFoodValue(const double &food) const;
	//----------------------------------------------------------------------
	void setAge(const double &age);
	void addAge(const double &age);
	const double &getAge() const;
	//----------------------------------------------------------------------
	void setGeneration(const double &generation);
	void addGeneration(const double &generation);
	const int &getGeneration() const;
	//----------------------------------------------------------------------
	void setTemperature(const double &temperature);
	void addTemperature(const double &temperature);
	const double &getTemperature() const;
	//----------------------------------------------------------------------
	void setHeatEnergyProduction(const double &heatEnergyProduction);
	const double getHeatEnergyProduction() const;
	//----------------------------------------------------------------------
	void setHeatLossFactor(const double &heatLossFactor);
	const double &getHeatLossFactor() const;
	void setHeatLossViaNeuralNetwork(const double &heatLossFactor);
	const double &getHeatLossViaNeuralNetwork() const;
	//----------------------------------------------------------------------
	void setSize(const double &size);
	const double &getSize() const;
	//----------------------------------------------------------------------
	void setRed(const int &red);
	const double &getRed() const;
	//----------------------------------------------------------------------
	void setGreen(const int &green);
	const double &getGreen() const;
	//----------------------------------------------------------------------
	void setBlue(const int &blue);
	const double &getBlue() const;
	//----------------------------------------------------------------------
	void setAlpha(const int &transparency);
	const double &getAlpha() const;
	//----------------------------------------------------------------------
	void setFoodEnergyFctor(const int &foodEnergyFactor);
	const double &getFoodEnergyFctor() const;
	//----------------------------------------------------------------------
	const double &getFitness() const;
	void setFitness(const double &fitness);
	void addFitness(const double &fitness);
	//----------------------------------------------------------------------
	void setDied(const bool dead);
	bool getDied();
	//----------------------------------------------------------------------
	void setWasHit(const bool hit);
	bool getWasHit();
	//----------------------------------------------------------------------
	NeuralNetwork &getNeuralNetwork();
	//----------------------------------------------------------------------
	//Random generator 
	double randomReal(const double lowerBoundary, const double upperBoundary);
	int randomInt(const int lowerBoundary, const int upperBoundary);	 
	static random_device seed_generator;
	static unsigned seed;
	static mt19937 mersenne_generator;
	//----------------------------------------------------------------------


private:
	//Brain...kind of
	NeuralNetwork _neuralNetwork;
	//Organism Properties
	//X-Y Position and rotation
	double _positionX;
	double _positionY;
	double _deltaDistanceForward = 0.0;
	double _deltaX;
	double _deltaY;
	double _rotation = 0.0;
	double _deltaRotation = 0.0;
	//----------------------------------------------------------------------
	int _red;
	int _green;
	int _blue;
	int _alpha;
	//----------------------------------------------------------------------
	double _fitness = 0.0;
	//----------------------------------------------------------------------
	double _size = SIZE_ORGANISM;
	//----------------------------------------------------------------------
	//Body funtionalities
	double _energyHeatProduction = ENERGY_HEAT_PRODUCTION;
	double _heatLoss = HEAT_LOSS_FACTOR;
	double _heatControleViaNeuralNetwork = 1.0;
	double _foodEnergyFactor = FOOD_ENERGY_FACTOR;
	//----------------------------------------------------------------------!
	//Condition
	double _energy = STARTING_ENERGY;
	double _age = 0.0;
	double _temperature = STARTING_TEMPERATURE;
	bool _dead = false;
	bool _washit = false;
	int _generation = 0;
};

