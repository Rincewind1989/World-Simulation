#include "Organism.h"

#include <iostream>

Organism::Organism()
{
	m_positionX = randomReal(0, (double)SIMULATION_X);
	m_positionY = randomReal(0, (double)SIMULATION_Y);
	cout << m_positionX << "\t" << m_positionY << endl;
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
