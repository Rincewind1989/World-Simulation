#include "Organism.h"

#include <iostream>

Organism::Organism()
{
	m_positionX = randomReal(0, (double)SIMULATION_X);
	m_positionY = randomReal(0, (double)SIMULATION_Y);
}


Organism::~Organism()
{
}


//Getters/Setters
void Organism::setPositionX(
	double positionX)
{
	m_positionX = positionX;
}


void Organism::addPositionX(
	double positionX)
{
	m_positionX += positionX;
}


double Organism::getPositionX()
{
	return m_positionX;
}


void Organism::setPositionY(
	double positionY)
{
	m_positionY = positionY;
}


void Organism::addPositionY(
	double positionY)
{
	m_positionY += positionY;
}


double Organism::getPositionY()
{
	return m_positionY;
}


void Organism::setEnergy(
	double energy)
{
	m_energy = energy;
}


void Organism::addEnergy(
	double energy)
{
	m_energy += energy;
}


double Organism::getEnergy()
{
	return m_energy;
}


void Organism::setTemperature(
	double temperature)
{
	m_temperature = temperature;
}


void Organism::addTemperature(
	double temperature)
{
	m_temperature += temperature;
}


double Organism::getTemperature()
{
	return m_temperature;
}


void Organism::setHeatEnergyProduction(
	double heatEnergyProduction)
{
	m_energyHeatProduction = heatEnergyProduction;
}


double Organism::getHeatEnergyProduction()
{
	return m_energyHeatProduction;
}


void Organism::setSize(
	double size)
{
	m_size = size;
}


double Organism::getSize()
{
	return m_size;
}


void Organism::setRed(
	int red)
{
	m_red = red;
}


double Organism::getRed()
{
	return m_red;
}


void Organism::setGreen(
	int green)
{
	m_green = green;
}


double Organism::getGreen()
{
	return m_green;
}


void Organism::setBlue(
	int blue)
{
	m_blue = blue;
}


double Organism::getBlue()
{
	return m_blue;
}


void Organism::setAlpha(
	int alpha)
{
	m_alpha = alpha;
}

double Organism::getAlpha()
{
	return m_alpha;
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
