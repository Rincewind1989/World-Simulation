#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Landscape.h"
#include "Organism.h"

using namespace std;

class Simulation
{
public:
	Simulation();
	~Simulation();

	//Getters/Setters
	Landscape &getLandscape();

	Organism &getOrganismByIndex(int index);

	vector<Organism> &getOrganisms();

	//Gets all the defined inputs for position
	vector<double> getInputs(Organism &organism);

	void deltaTime();

	//Updates the whole simulatipn
	void updateSimulation();

	//Updates all dynamics by time
	void updateWorld();

	//Updates all organisms by time
	void updateOrganisms();

	//Update the neural network of all organisms
	void updateNeuralNetworks();

	//Updates every organism if it attacks nearby entity
	void updateAttack();

	//Updates the movement of every organism
	void updateMovement();

	//Update eating for every organism
	void updateEating();

	//Update the energy of all organisms
	void updateHeatEnergy();

	//Update the energy of all organisms based on size
	void updateEnergy();

	//Update all food on every tile
	void updateFood();

	//Update the temperature on every tile
	void updateTemperature();

	//Create new organisms until the maximum Population is reached
	void createOrganismViaAsexuell();

	//Create Organisms if number of Org goes under min value of living organism
	void createOrganismBeforeExtinction();

	//Create new organisms until the maximum Population is reached
	void createOrganismViaFitness();

	//Update fitness by time
	void updateFitness();

	//Gets the highest fitness
	double getHighestFitness();

	//Gets the efficiency of the body functions based on the optimum temperature
	double getTempBasedFunction(Organism &organism);

	//Checks every Organism if it died
	void checkForDeath();

	//Random generator 
	double randomReal(const double lowerBoundary, const double upperBoundary);

	int randomInt(const int lowerBoundary, const int upperBoundary);

	static random_device seed_generator;
	static unsigned seed;
	static mt19937 mersenne_generator;

private:
	Landscape _landscape;
	vector<Organism> _organisms;
	sf::Clock _clock;
	double _deltaTime;
	double _accDeltaTime;

	double _highestFitness = 0.0;
};

