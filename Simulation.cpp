#include "Simulation.h"

#include <iostream>

Simulation::Simulation()
{
	for (int i = 0; i < STARTING_NUMBER_ORGANISM; i++)
	{
		Organism tmp;
		_organisms.push_back(tmp);
	}

}


Simulation::~Simulation()
{
}


//Getters/Setters
Landscape &Simulation::getLandscape()
{
	return _landscape;
}


Organism &Simulation::getOrganismByIndex(int index)
{
	return _organisms[index];
}


vector<Organism> &Simulation::getOrganisms()
{
	return _organisms;
}


//Gets all the defined inputs for the organism
vector<double> Simulation::getInputs(Organism &organism)
{
	vector<double> inputs = vector<double>(2 * (2 * ADJACENT_TILES_RADIUS + 1) * (2 * ADJACENT_TILES_RADIUS + 1) + INPUTS_FOR_BODY_PROPERTIES);

	int positionX = (int)organism.getPositionX();
	int positionY = (int)organism.getPositionY();
	int index = 0;
	//Get the temperature on the adjacent tiles
	for (int i = -ADJACENT_TILES_RADIUS; i < ADJACENT_TILES_RADIUS + 1; i++)
	{
		for (int j = -ADJACENT_TILES_RADIUS; j < ADJACENT_TILES_RADIUS + 1; j++)
		{
			if (positionY + i > (SIMULATION_Y - 1) || positionY + i < 0 || positionX + j > (SIMULATION_X - 1) || positionX + j < 0)
			{
				inputs[index] = 0.0;				
			}
			else
			{
				inputs[index] = _landscape.getTiles()[positionY + i][positionX + j].getTemperature();
			}
			index++;
		}
	}

	//Gets the food on the adjacent tiles
	for (int i = -ADJACENT_TILES_RADIUS; i < ADJACENT_TILES_RADIUS + 1; i++)
	{
		for (int j = -ADJACENT_TILES_RADIUS; j < ADJACENT_TILES_RADIUS + 1; j++)
		{
			if (positionY + i >(SIMULATION_Y - 1) || positionY + i < 0 || positionX + j >(SIMULATION_X - 1) || positionX + j < 0)
			{
				inputs[index] = 0.0;				
			}
			else
			{
				inputs[index] = _landscape.getTiles()[positionY + i][positionX + j].getFood();
			}
			index++;
		}
	}
	
	//Get the body properties of the organism
	inputs[index] = organism.getTemperature();
	index++;
	inputs[index] = organism.getEnergy();

	return inputs;
}


//Updates the whole simulation
void Simulation::updateSimulation()
{
	updateOrganisms();
	updateWorld();
}


//Updates all dynamics by time
void Simulation::updateWorld()
{
	updateFood();

}


//Updates all organisms by time
void Simulation::updateOrganisms()
{
	updateFitness();
	createOrganism();
	updateHeatEnergy();
	updateEating();
	updateNeuralNetworks();
	updateMovement();
}


//Update the neural network of all organisms
void Simulation::updateNeuralNetworks()
{
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end())
	{
		it->getNeuralNetwork().feedForward(getInputs((*it)));
		++it;
	}
}


//Updates the movement of every organism
void Simulation::updateMovement()
{
	vector<Organism>::iterator it = _organisms.begin();
	double energy = 0.0;
	double movementAdd = 0.0;
	while (it != _organisms.end())
	{	
		//Change x-coordinate
		movementAdd = it->getNeuralNetwork().getOutputs()[0];
		movementAdd = _deltaTime * MOVEMENT_SPEED * it->getNeuralNetwork().getOutputs()[0];
		it->addPositionX(movementAdd);
		if (it->getPositionX() < 0.0)
		{
			it->setPositionX(0.0);
		}
		if (it->getPositionX() > SIMULATION_X)
		{
			it->setPositionX(SIMULATION_X);
		}

		//Change y-coordinate
		movementAdd = it->getNeuralNetwork().getOutputs()[1];
		movementAdd = _deltaTime * MOVEMENT_SPEED * it->getNeuralNetwork().getOutputs()[1];
		it->addPositionY(movementAdd);
		if (it->getPositionY() < 0.0)
		{
			it->setPositionY(0.0);
		}
		if (it->getPositionY() > SIMULATION_Y)
		{
			it->setPositionY(SIMULATION_Y);
		}

		energy = -1 * _deltaTime * MOVEMENT_ENERGY_LOST * sqrt((it->getNeuralNetwork().getOutputs()[0] * it->getNeuralNetwork().getOutputs()[0]) + fabs(it->getNeuralNetwork().getOutputs()[1] * it->getNeuralNetwork().getOutputs()[1]));
		it->addEnergy(energy);
		++it;
	}
}


//Update the energy of all organisms based on body properties and enviromnent
void Simulation::updateHeatEnergy()
{
	double energy;
	double temperature;
	int x = 0;
	int y = 0;
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end())
	{
		energy = -1 * _deltaTime * it->getHeatEnergyProduction() * ENERGY_CONSUMPTION_FACTOR;
		x = (int)it->getPositionX();
		y = (int)it->getPositionY();
		if (x < 0)
		{
			x = 0;
		}
		if (x > SIMULATION_X - 1)
		{
			x = SIMULATION_X - 1;
		}
		if (y < 0)
		{
			y = 0;
		}
		if (y > SIMULATION_Y - 1)
		{
			y = SIMULATION_Y - 1;
		}
		temperature = _deltaTime * it->getHeatEnergyProduction() - _deltaTime * HEAT_LOSS_FACTOR * (it->getTemperature() - _landscape.getTiles()[y][x].getTemperature());
		it->addEnergy(energy);
		it->addTemperature(temperature);
		if (it->getEnergy() <= 0.0 || it->getTemperature() <= 20.0)
		{
			it = _organisms.erase(it);
		}
		else ++it;
	}
}


//Update eating for every organism
void Simulation::updateEating()
{
	vector<Organism>::iterator it = _organisms.begin();
	double food = 0.0;
	int x = 0;
	int y = 0;
	while (it != _organisms.end())
	{
		x = (int)it->getPositionX();
		y = (int)it->getPositionY();
		if (x < 0)
		{
			x = 0;
		}
		if (x > SIMULATION_X - 1)
		{
			x = SIMULATION_X - 1;
		}
		if (y < 0)
		{
			y = 0;
		}
		if (y > SIMULATION_Y - 1)
		{
			y = SIMULATION_Y - 1;
		}
		if (_landscape.getTiles()[y][x].getFood() * _deltaTime > 0.0 && _landscape.getTiles()[y][x].getFood() > CONSUMPTION_FACTOR)
		{
			food = CONSUMPTION_FACTOR * _deltaTime;
			_landscape.getTiles()[y][x].addFood(-food);
		}
		else if (_landscape.getTiles()[y][x].getFood() * _deltaTime > 0.0 && _landscape.getTiles()[y][x].getFood() < CONSUMPTION_FACTOR)
		{
			food = _landscape.getTiles()[y][x].getFood() * _deltaTime;
			_landscape.getTiles()[y][x].addFood(-food);
		}
		it->addEnergyViaFood(food);
		++it;
	}
}


//Update all food on every tile
void Simulation::updateFood()
{
	double foodAdd;
	for (vector<vector<Tile>>::iterator it = _landscape.getTiles().begin(); it != _landscape.getTiles().end(); ++it)
	{
		for (vector<Tile>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
		{
			if (it2->getFood() >= MAX_FOOD_ON_TILE)
			{
				foodAdd = _deltaTime * (MAX_FOOD_ON_TILE - it2->getFood()) * FOOD_GROWTH_FACTOR;
				it2->addFood(foodAdd);
			}
			else
			{
				if (randomReal(0.0, 1.0) < CHANCE_FOOD_GROWTH)
				{					
					foodAdd = randomReal(0.0, _deltaTime * (MAX_FOOD_ON_TILE - it2->getFood()) * FOOD_GROWTH_FACTOR);
					it2->addFood(foodAdd);
				}
			}

			//Small chance for a big food growth
			if (randomReal(0.0, 1.0) < CHANCE_BIG_FOOD_GROWTH)
			{
				foodAdd = _deltaTime * randomReal(MAX_FOOD_ON_TILE / 2.0, MAX_FOOD_ON_TILE);
				it2->addFood(foodAdd);
			}
			
		}
	}			
}


//Create new organisms until the maximum Population is reached
void Simulation::createOrganism()
{
	double totalFitness = 0.0;
	int numberOrganisms = 0;
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end())
	{
		totalFitness += it->getFitness();
		numberOrganisms++;
		++it;
	}

	double chance = 0.0;
	double fitnessSoFar = 0.0;
	while (_organisms.size() < STARTING_NUMBER_ORGANISM)
	{
		chance = randomReal(0.0, totalFitness);
		fitnessSoFar = 0.0;
		//Find father
		it = _organisms.begin();
		Organism* father = &_organisms[0];
		while (it != _organisms.end())
		{
			fitnessSoFar += it->getFitness();
			if (chance < fitnessSoFar)
			{
				father = &(*it);
				break;
			}			
			++it;
		}

		chance = randomReal(0.0, totalFitness);
		fitnessSoFar = 0.0;
		//Find mother
		it = _organisms.begin();
		Organism* mother = &_organisms[0];
		while (it != _organisms.end())
		{
			fitnessSoFar += it->getFitness();
			if (chance < fitnessSoFar && &(*it) != father)
			{
				mother = &(*it);
				break;
			}
			++it;
		}
		
		//Create child
		Organism child(*father, *mother);
		_organisms.push_back(child);
	}
}


//Gets the highest fitness
double Simulation::getHighestFitness()
{
	return _highestFitness;
}


//Update fitness by time
void Simulation::updateFitness()
{
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end())
	{
		it->addFitness(_deltaTime);
		if (it->getFitness() > _highestFitness)
		{
			_highestFitness = it->getFitness();
		}		
		++it;
	}
}


//Updates the time elapsed since last update
void Simulation::deltaTime()
{
	const sf::Time delta = _clock.restart();
	_deltaTime = (delta.asSeconds());
	//printf("FPS: %f \n", 1 / _deltaTime);
}


//Random engine call
double Simulation::randomReal(
	const double lowerBoundary,
	const double upperBoundary)
{
	uniform_real_distribution<double> distribution_real(lowerBoundary, upperBoundary);
	return distribution_real(mersenne_generator);
}

int Simulation::randomInt(
	const int lowerBoundary,
	const int upperBoundary)
{
	uniform_int_distribution<int> distribution_int(lowerBoundary, upperBoundary);
	return distribution_int(mersenne_generator);
}

//Random engine initialisation
random_device Simulation::seed_generator;
unsigned Simulation::seed = seed_generator();
mt19937 Simulation::mersenne_generator(Simulation::seed);