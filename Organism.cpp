#include "Organism.h"

#include <iostream>

Organism::Organism()
{
	_positionX = randomReal(0, (double)SIMULATION_X);
	_positionY = randomReal(0, (double)SIMULATION_Y);
}


Organism::Organism(Organism &father, Organism &mother)
{
	Organism child;
	vector<double> weights = vector<double>(father.getNeuralNetwork().getWeights().size());
	if (randomInt(0, 1) == 0)
	{
		for (int i = 0; i < weights.size(); i++)
		{
			if (i % 2)
			{
				weights[i] = father.getNeuralNetwork().getWeights()[i];
			}
			else
			{
				mother.getNeuralNetwork().getWeights()[i];
			}
		}
		child.getNeuralNetwork().setWeights(weights);
		child.getNeuralNetwork().processMutations();
		_positionX = father.getPositionX();
		_positionY = father.getPositionY();
	}
	else
	{
		for (int i = 0; i < weights.size(); i++)
		{
			if (i % 2)
			{
				mother.getNeuralNetwork().getWeights()[i];				
			}
			else
			{
				weights[i] = father.getNeuralNetwork().getWeights()[i];
			}
		}
		child.getNeuralNetwork().setWeights(weights);
		child.getNeuralNetwork().processMutations();
		_positionX = mother.getPositionX();
		_positionY = mother.getPositionY();
	}	
}


Organism::~Organism()
{
}


//Getters/Setters
void Organism::setPositionX(
	double positionX)
{
	_positionX = positionX;
}


void Organism::addPositionX(
	double positionX)
{
	_positionX += positionX;
}


double Organism::getPositionX()
{
	return _positionX;
}


void Organism::setPositionY(
	double positionY)
{
	_positionY = positionY;
}


void Organism::addPositionY(
	double positionY)
{
	_positionY += positionY;
}


double Organism::getPositionY()
{
	return _positionY;
}


void Organism::setEnergy(
	double energy)
{
	_energy = energy;
}


void Organism::addEnergy(
	double energy)
{
	_energy += energy;
}


void Organism::addEnergyViaFood(
	double food)
{
	_energy += _foodEnergyFactor * food;
}


double Organism::getEnergy()
{
	return _energy;
}


void Organism::setTemperature(
	double temperature)
{
	_temperature = temperature;
}


void Organism::addTemperature(
	double temperature)
{
	_temperature += temperature;
}


double Organism::getTemperature()
{
	return _temperature;
}


void Organism::setHeatEnergyProduction(
	double heatEnergyProduction)
{
	_energyHeatProduction = heatEnergyProduction;
}


double Organism::getHeatEnergyProduction()
{
	return _energyHeatProduction;
}


void Organism::setSize(
	double size)
{
	_size = size;
}


double Organism::getSize()
{
	return _size;
}


void Organism::setRed(
	int red)
{
	_red = red;
}


double Organism::getRed()
{
	return _red;
}


void Organism::setGreen(
	int green)
{
	_green = green;
}


double Organism::getGreen()
{
	return _green;
}


void Organism::setBlue(
	int blue)
{
	_blue = blue;
}


double Organism::getBlue()
{
	return _blue;
}


void Organism::setAlpha(
	int alpha)
{
	_alpha = alpha;
}


double Organism::getAlpha()
{
	return _alpha;
}


NeuralNetwork &Organism::getNeuralNetwork()
{
	return _neuralNetwork;
}


double &Organism::getFitness()
{
	return _fitness;
}


void Organism::setFitness(double &fitness)
{
	_fitness = fitness;
}


void Organism::addFitness(double &fitness)
{
	_fitness += fitness;
}


//Random engine call
double Organism::randomReal(
	const double lowerBoundary,
	const double upperBoundary)
{
	uniform_real_distribution<double> distribution_real(lowerBoundary, upperBoundary);
	return distribution_real(mersenne_generator);
}

int Organism::randomInt(
	const int lowerBoundary,
	const int upperBoundary)
{
	uniform_int_distribution<int> distribution_int(lowerBoundary, upperBoundary);
	return distribution_int(mersenne_generator);
}

//Random engine initialisation
random_device Organism::seed_generator;
unsigned Organism::seed = seed_generator();
mt19937 Organism::mersenne_generator(Organism::seed);
