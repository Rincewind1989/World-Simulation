#include <algorithm>
#include <iostream>

#include "Simulation.h"

Simulation::Simulation()
{
	for (int i = 0; i < STARTING_NUMBER_ORGANISM; i++)
	{
		_organisms.push_back(Organism());
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
	vector<double> inputs = vector<double>(INPUT_NEURONS);

	int positionX = (int)organism.getPositionX();
	int positionY = (int)organism.getPositionY();
	int index = 0;

	//Get the temperature/food and number of entities on the adjacent tiles
	for (int i = -ADJACENT_TILES_RADIUS; i < ADJACENT_TILES_RADIUS + 1; i++)
	{
		for (int j = -ADJACENT_TILES_RADIUS; j < ADJACENT_TILES_RADIUS + 1; j++)
		{
			if (positionY + i > (SIMULATION_Y - 1) || positionY + i < 0 || positionX + j > (SIMULATION_X - 1) || positionX + j < 0)
			{
				inputs[index] = 0.0;
				index++;
				inputs[index] = 0.0;
			}
			else
			{
				inputs[index] = _landscape.getTiles()[positionY + i][positionX + j].getTemperature();
				index++;
				inputs[index] = _landscape.getTiles()[positionY + i][positionX + j].getFood();
			}
			index++;
			for (vector<Organism>::iterator it = _organisms.begin(); it != _organisms.end(); ++it)
			{
				if ((int)it->getPositionY() == positionY + i && (int)it->getPositionX() == positionX + j)
				{
					inputs[index] += 1.0;
				}
			}
			index++;
		}
	}

	index++;

	//Gets the 4 next entities with their distance
	vector<Organism*> nearestOrganisms;
	Organism* tmpNearestOrganism;
	double minDistance = 1000000000.0;
	double distance = 0.0;
	for (int i = 0; i < NUMBER_NEXT_ENTITES; i++)
	{
		minDistance = 1000000000.0;
		tmpNearestOrganism = NULL;
		for (vector<Organism>::iterator it = _organisms.begin(); it != _organisms.end(); ++it)
		{	
			distance = sqrt((it->getPositionX() - organism.getPositionX()) * (it->getPositionX() - organism.getPositionX()) + (it->getPositionY() - organism.getPositionY()) * (it->getPositionY() - organism.getPositionY()));
			if (distance < minDistance && find(nearestOrganisms.begin(), nearestOrganisms.end(), &(*it)) != nearestOrganisms.end())
			{
				minDistance = distance;
				tmpNearestOrganism = &(*it);
			}
		}
		if (tmpNearestOrganism != NULL)
		{
			nearestOrganisms.push_back(tmpNearestOrganism);
			inputs[index] = distance;
			index++;
			inputs[index] = tmpNearestOrganism->getAlpha();
			index++;
			inputs[index] = tmpNearestOrganism->getBlue();
			index++;
			inputs[index] = tmpNearestOrganism->getGreen();
			index++;
			inputs[index] = tmpNearestOrganism->getRed();
			index++;
		}
		else
		{
			nearestOrganisms.push_back(tmpNearestOrganism);
			inputs[index] = 0.0;
			index++;
			inputs[index] = 0.0;
			index++;
			inputs[index] = 0.0;
			index++;
			inputs[index] = 0.0;
			index++;
			inputs[index] = 0.0;
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
	updateTemperature();
	updateFood();
}


//Updates all organisms by time
void Simulation::updateOrganisms()
{
	updateNeuralNetworks();
	updateMovement();
	updateHeatEnergy();
	updateEnergy();
	updateEating();
	updateAttack();
	checkForDeath();
	createOrganismViaAsexuell();
	createOrganismViaFitness();
	createOrganismBeforeExtinction();
	updateFitness();
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
		movementAdd = getTempBasedFunction(*it) * _deltaTime * MOVEMENT_SPEED * it->getNeuralNetwork().getOutputs()[0];
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
		movementAdd = getTempBasedFunction(*it) * _deltaTime * MOVEMENT_SPEED * it->getNeuralNetwork().getOutputs()[1];
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


//Update the energy of all organisms based on temperature loss
void Simulation::updateHeatEnergy()
{
	double energy;
	double temperature;
	int x = 0;
	int y = 0;
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end())
	{
		//Update heatloss factor via neural network
		double newheatloss = it->getHeatLossFactor() - it->getNeuralNetwork().getOutputs()[3];
		if (newheatloss < LOWEST_HEAT_LOSS_VALUE)
		{
			newheatloss = LOWEST_HEAT_LOSS_VALUE;
		}
		if (newheatloss > HIGHEST_HEAT_LOSS_VALUE)
		{
			newheatloss = HIGHEST_HEAT_LOSS_VALUE;
		}
		it->setHeatLossFactor(newheatloss);


		//Update energy and temperature
		energy = -1 * _deltaTime * it->getHeatEnergyProduction() * (it->getHeatLossFactor() / HEAT_LOSS_FACTOR) * ENERGY_CONSUMPTION_FACTOR;
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

		//Get lost temperature
		double lostTemperature = _deltaTime * it->getHeatLossFactor() * (it->getTemperature() - _landscape.getTiles()[y][x].getTemperature());

		//Get added temperature
		double addTemperature = _deltaTime * it->getHeatEnergyProduction();

		//Add/subtract temperature from environment and organism
		temperature = addTemperature - lostTemperature;
		_landscape.getTiles()[y][x].addTemperature(lostTemperature * TEMPERATURE_AIR_FLUX_FACTOR);
		it->addEnergy(energy);
		it->addTemperature(temperature);

		//Check if organism died from energy- or temperatureloss
		if (it->getEnergy() <= 0.0 || it->getTemperature() <= COLD_TEMP_DEATH || it->getTemperature() >= HEAT_TEMP_DEATH)
		{
			it->setDied(true);
		}
		++it;
	}
}


//Update the energy of all organisms based on size
void Simulation::updateEnergy()
{
	vector<Organism>::iterator it = _organisms.begin();
	double energy;
	while (it != _organisms.end())
	{
		//Update energy and temperature
		energy = -1 * _deltaTime * it->getSize() * SIZE_ENERGY_LOSS_FACTOR;

		it->addEnergy(energy);

		//Check if organism died from energy- or temperatureloss
		if (it->getEnergy() <= 0.0)
		{
			it->setDied(true);
		}
		++it;
	}
}


//Updates every organism if it attacks nearby entity
void Simulation::updateAttack()
{
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end())
	{
		//Attack neary Entity if Neural network tells so and entity is close enough
		if (it->getNeuralNetwork().getOutputs()[4] > 0.0)
		{
			Organism* closestOrganism = NULL;
			double distanceClosestOrganism = 1000000000.0;
			double distance = 0.0;
			for (vector<Organism>::iterator it2 = _organisms.begin(); it2 != _organisms.end(); ++it2)
			{
				if (&(*it2) == &(*it))
				{
					continue;
				}

				distance = (it->getPositionX() - it2->getPositionX()) * (it->getPositionX() - it2->getPositionX()) 
					+ (it->getPositionY() - it2->getPositionY()) * (it->getPositionY() - it2->getPositionY());
				if (distanceClosestOrganism > distance)
				{
					distanceClosestOrganism = distance;
					closestOrganism = &(*it2);
				}
			}

			if (sqrt((it->getPositionX() - closestOrganism->getPositionX()) * (it->getPositionX() - closestOrganism->getPositionX()) 
				+ (it->getPositionY() - closestOrganism->getPositionY()) * (it->getPositionY() - closestOrganism->getPositionY())) < it->getSize())
			{
				double energy = it->getSize() * _deltaTime * ATTACK_DAMAGE;
				//cout << "Organism " << &(*it) << " attacks for: " << energy << endl;
				if (energy > closestOrganism->getEnergy())
				{
					energy = closestOrganism->getEnergy();
				}
				closestOrganism->addEnergy(-energy);
				it->addEnergy(energy);
			}
		}



		//Check if organism died from energy- or temperatureloss
		if (it->getEnergy() <= 0.0 || it->getTemperature() <= COLD_TEMP_DEATH || it->getTemperature() >= HEAT_TEMP_DEATH)
		{
			it->setDied(true);
		}		
		++it;
	}
}


//Checks every Organism if it died
void Simulation::checkForDeath()
{
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end())
	{
		if (it->getDied())
		{
			//cout << it->getDied() << endl;
			*it = _organisms[_organisms.size() - 1];
			if (&(*it) == &(_organisms[_organisms.size() - 1]))
			{
				_organisms.pop_back();
				break;
			}
			_organisms.pop_back();
			
		}
		else
		{
			++it;
		}
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
		food = 0.0;
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
			food = getTempBasedFunction(*it) * CONSUMPTION_FACTOR * _deltaTime;
			_landscape.getTiles()[y][x].addFood(-food);
		}
		else if (_landscape.getTiles()[y][x].getFood() * _deltaTime > 0.0 && _landscape.getTiles()[y][x].getFood() < CONSUMPTION_FACTOR)
		{
			food = getTempBasedFunction(*it) * _landscape.getTiles()[y][x].getFood() * _deltaTime;
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


//Update the temperature on every tile
void Simulation::updateTemperature()
{
	double tempAdd;
	for (vector<vector<Tile>>::iterator it = _landscape.getTiles().begin(); it != _landscape.getTiles().end(); ++it)
	{
		for (vector<Tile>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
		{
			tempAdd = _deltaTime * (it2->getOrignTemperature() - it2->getTemperature());
			it2->addTemperature(tempAdd);
		}
	}
}


//Create new organisms until the maximum Population is reached
void Simulation::createOrganismViaAsexuell()
{
	vector<Organism> newChilds;
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end())
	{
		if (it->getNeuralNetwork().getOutputs()[2] > 0.0 && it->getEnergy() > NEWLIFE_ENERGY_CONSUMPTION)
		{
			//Change adults energy
			it->addEnergy(-STARTING_ENERGY);

			//Create child
			Organism child = it->asexualBreeding();
			newChilds.push_back(child);
		
		}
		++it;
	}
	_organisms.insert(_organisms.end(), newChilds.begin(), newChilds.end());

}



//Create Organisms if number of Org goes under min value of living organism
void Simulation::createOrganismBeforeExtinction()
{
	while (_organisms.size() < STARTING_NUMBER_ORGANISM)
	{
		Organism org;
		_organisms.push_back(org);

	}
}


//Create new organisms until the maximum Population is reached
void Simulation::createOrganismViaFitness()
{

	if (_accDeltaTime >= 5.0)
	{
		_accDeltaTime -= 5.0;

		double totalFitness = 0.0;
		vector<Organism>::iterator it = _organisms.begin();
		while (it != _organisms.end())
		{
			totalFitness += it->getFitness();
			++it;
		}

		double chance = 0.0;
		double fitnessSoFar = 0.0;
	
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
	if (TIME_LAPSE)
	{
		_deltaTime = 1.0;
	}
	else
	{
		_deltaTime = (delta.asSeconds());
	}
	_accDeltaTime += _deltaTime;
	//printf("FPS: %f \n", 1 / _deltaTime);
}


//Gets the efficiency of the body functions based on the optimum temperature
double Simulation::getTempBasedFunction(Organism &organism)
{
	double tempDifference = fabs(organism.getTemperature() - OPTIM_TEMPERATURE);
	return 1.0 - tempDifference / OPTIM_TEMPERATURE;
}


//Random engine call
double Simulation::randomReal(const double lowerBoundary, const double upperBoundary)
{
	uniform_real_distribution<double> distribution_real(lowerBoundary, upperBoundary);
	return distribution_real(mersenne_generator);
}

int Simulation::randomInt(const int lowerBoundary, const int upperBoundary)
{
	uniform_int_distribution<int> distribution_int(lowerBoundary, upperBoundary);
	return distribution_int(mersenne_generator);
}

//Random engine initialisation
random_device Simulation::seed_generator;
unsigned Simulation::seed = seed_generator();
mt19937 Simulation::mersenne_generator(Simulation::seed);