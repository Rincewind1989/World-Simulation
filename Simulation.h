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
	//----------------------------------------------------------------------
	//Getters/Setters
	Landscape &getLandscape();
	//----------------------------------------------------------------------
	Organism &getOrganismByIndex(int index);
	vector<Organism> &getOrganisms();
	//----------------------------------------------------------------------
	void setInformationOrganism(Organism* org);
	Organism* getInformationOrganism() const;
	//----------------------------------------------------------------------
	//Gets all the defined inputs for position
	vector<double> getInputs(Organism &organism);
	//----------------------------------------------------------------------
	void deltaTime();
	//----------------------------------------------------------------------
	//Updates the whole simulatipn
	void updateSimulation();
	//----------------------------------------------------------------------
	//Updates all dynamics by time
	void updateWorld();
	//Update all food on every tile
	void updateFood();
	//Update the temperature on every tile
	void updateTemperature();
	//----------------------------------------------------------------------
	//Updates all organisms by time
	void updateOrganisms();
	//Updates washit to false in the beginning
	void updateWasHit();
	//Update the neural network of all organisms
	void updateNeuralNetworks(Organism *organism);
	//Update Body functions based on neural network output
	void updateBodyFuncViaNeuralNetwork(Organism *organism);
	//Updates every organism if it attacks nearby entity
	void updateAttack(Organism *organism);
	//Updates the movement of every organism
	void updateMovement(Organism *organism);
	//Update eating for every organism
	void updateEating(Organism *organism);
	//Update the energy of all organisms
	void updateHeatEnergy(Organism *organism);
	//Update the energy of all organisms based on size
	void updateEnergy(Organism *organism);
	//Update the Heat-Control of an Organism
	void updateHeatControl(Organism *organism);
	//Checks every Organism if it died
	bool checkForDeath(Organism *organism);
	//Update fitness by time
	void updateFitness(Organism *organism);
	//----------------------------------------------------------------------
	//Create new organisms until the maximum Population is reached
	void createOrganismViaAsexuell(Organism *organism);
	//Create Organisms if number of Org goes under min value of living organism
	void createOrganismBeforeExtinction(Organism *organism);
	//Create new organisms until the maximum Population is reached
	void createOrganismViaFitness(Organism *organism);
	//----------------------------------------------------------------------
	//Gets the highest fitness
	double getHighestFitness();
	//Gets the average fitness of all Organisms
	double getAvgFitness();
	//----------------------------------------------------------------------
	//Gets the efficiency of the body functions based on the optimum temperature
	double getTempBasedFunction(Organism &organism);
	//----------------------------------------------------------------------
	//Gets the position of the tile with the position of the organism
	void getTileXYViaOrganism(int &x, int &y, const Organism *organism);
	//Random generator 
	double randomReal(const double lowerBoundary, const double upperBoundary);
	int randomInt(const int lowerBoundary, const int upperBoundary);
	static random_device seed_generator;
	static unsigned seed;
	static mt19937 mersenne_generator;

private:
	Landscape _landscape;
	vector<Organism> _organisms;
	Organism* _informationOrganism = NULL;
	sf::Clock _clock;
	double _deltaTime;
	double _accDeltaTime;
	double _highestFitness = 0.0;
};

