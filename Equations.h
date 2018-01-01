#pragma once
#include "Simulation.h"
#include "Organism.h"

//Updates world properties

//Update all food on every tile
void Simulation::updateFoodAsODE()
{
	double foodAdd;
	for (vector<vector<Tile>>::iterator it = _landscape.getTiles().begin(); it != _landscape.getTiles().end(); ++it)
	{
		for (vector<Tile>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
		{
			if (it2->getFood() >= MAX_FOOD_ON_TILE)
			{
				foodAdd = (MAX_FOOD_ON_TILE - it2->getFood()) * FOOD_GROWTH_FACTOR;
				it2->addFood(foodAdd);
			}
			else
			{
				if (randomReal(0.0, 1.0) < CHANCE_FOOD_GROWTH)
				{
					foodAdd = randomReal(0.0, (MAX_FOOD_ON_TILE - it2->getFood()) * FOOD_GROWTH_FACTOR);
					it2->addFood(foodAdd);
				}
			}

			//Small chance for a big food growth
			if (randomReal(0.000, 1.000) < CHANCE_BIG_FOOD_GROWTH)
			{
				foodAdd = randomReal(MAX_FOOD_ON_TILE / 10.0, MAX_FOOD_ON_TILE / 5.0);
				it2->addFood(foodAdd);
			}

		}
	}
}

//Update all food discrete randomly distributed on the tiles
void Simulation::updateFoodDiscrete()
{
	double foodAdd;
	for (vector<vector<Tile>>::iterator it = _landscape.getTiles().begin(); it != _landscape.getTiles().end(); ++it)
	{
		for (vector<Tile>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
		{
			//Chance that food appears
			if (randomReal(0.00, 1.00) <= CHANCE_FOR_DISCRETE_FOOD_SPAWN)
			{
				foodAdd = randomReal(MAX_FOOD_ON_TILE / 5.0, MAX_FOOD_ON_TILE / 2.5);
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
			tempAdd = (it2->getOrignTemperature() - it2->getTemperature());
			it2->addTemperature(tempAdd);
		}
	}
}


//-------------------------------------------------------------
//Updates properties of organisms

//Update the energy of all organisms based on temperature loss
void Simulation::updateHeatEnergy(Organism *organism)
{
	double deltaTemperature;
	int x = 0;
	int y = 0;
	getTileXYViaOrganism(x, y, &(*organism));

	//Get lost temperature
	double lostTemperature = organism->getHeatLossFactor() * organism->getHeatLossViaNeuralNetwork() * (organism->getTemperature() - _landscape.getTiles()[y][x].getTemperature());

	//Get added temperature
	double addTemperature = organism->getHeatEnergyProduction();

	//Add/subtract temperature from environment and organism
	deltaTemperature = addTemperature - lostTemperature;
	_landscape.getTiles()[y][x].addTemperature(lostTemperature * TEMPERATURE_AIR_FLUX_FACTOR);
	organism->addTemperature(deltaTemperature);

	//Check if organism died from temperatureloss
	if (organism->getEnergy() <= 0.0 || organism->getTemperature() <= COLD_TEMP_DEATH || organism->getTemperature() >= HEAT_TEMP_DEATH)
	{
		organism->setDied(true);
	}
	++organism;
}

//Update the energy of all organisms based on size
void Simulation::updateEnergy(Organism *organism)
{
	double addEnergy = 0.0;
	//Update energy and temperature
	addEnergy += -1 * organism->getSize() * organism->getSize() * SIZE_ENERGY_LOSS_FACTOR;

	//Update energy and temperature
	addEnergy += -1 * organism->getHeatEnergyProduction();

	//Update Energy via movement
	int x = 0;
	int y = 0;
	double movementFactorIfinWater = 1.0;
	getTileXYViaOrganism(x, y, &(*organism));
	if (_landscape.getTiles()[y][x].getHeight() < WATER_LEVEL)
	{
		movementFactorIfinWater = MOVEMENT_ENERGY_FACTOR_IN_WATER;
	}
	addEnergy += -1 * MOVEMENT_ENERGY_LOST * movementFactorIfinWater * sqrt((organism->getDeltaX() * organism->getDeltaX()) + fabs(organism->getDeltaY() * organism->getDeltaY()));


	organism->addEnergy(addEnergy);

	//Check if organism died from energyloss
	if (organism->getEnergy() <= 0.0)
	{
		organism->setDied(true);
	}
}

//Updates every organism if it attacks nearby entity
void Simulation::updateAttack(Organism *organism)
{
	//Attack neary Entity if Neural network tells so and entity is close enough
	Organism* closestOrganism = NULL;
	if (organism->getNeuralNetwork().getOutputs()[4] > 0.0)
	{
		double distanceClosestOrganism = 1000000000.0;
		double distance = 0.0;
		for (vector<Organism>::iterator it2 = _organisms.begin(); it2 != _organisms.end(); ++it2)
		{
			if (&(*it2) == &(*organism))
			{
				continue;
			}

			distance = (organism->getPositionX() - it2->getPositionX()) * (organism->getPositionX() - it2->getPositionX())
				+ (organism->getPositionY() - it2->getPositionY()) * (organism->getPositionY() - it2->getPositionY());
			if (distanceClosestOrganism > distance)
			{
				distanceClosestOrganism = distance;
				closestOrganism = &(*it2);
			}
		}

		if (sqrt((organism->getPositionX() - closestOrganism->getPositionX()) * (organism->getPositionX() - closestOrganism->getPositionX())
			+ (organism->getPositionY() - closestOrganism->getPositionY()) * (organism->getPositionY() - closestOrganism->getPositionY())) < organism->getSize())
		{
			closestOrganism->setWasHit(true);
			double energy = organism->getSize() * ATTACK_DAMAGE;
			//cout << "Organism " << &(*it) << " attacks for: " << energy << endl;
			if (energy > closestOrganism->getEnergy())
			{
				energy = closestOrganism->getEnergy();
			}
			closestOrganism->addEnergy(-energy);
			organism->addEnergy(energy);
		}
	}



	//Check if organism died from energy- or temperatureloss
	if (closestOrganism != NULL)
	{
		if (closestOrganism->getEnergy() <= 0.0)
		{
			closestOrganism->setDied(true);
		}
	}
}

//Update eating for every organism
void Simulation::updateEating(Organism *organism)
{
	double food = 0.0;
	int x = 0;
	int y = 0;
	food = 0.0;
	getTileXYViaOrganism(x, y, &(*organism));
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

	food = getTempBasedFunction(*organism) * CONSUMPTION_FACTOR;

	if (_landscape.getTiles()[y][x].getFood() > food)
	{
		_landscape.getTiles()[y][x].addFood(-food);
	}
	else
	{
		food = _landscape.getTiles()[y][x].getFood();
		_landscape.getTiles()[y][x].addFood(-_landscape.getTiles()[y][x].getFood());
	}

	organism->addEnergyViaFood(food);
}

//Update the Heat-Control of an Organism
void Simulation::updateHeatControl(Organism *organism)
{
	//Update heatloss factor via neural network
	double heatControlViaNeuralNetwork = organism->getHeatLossViaNeuralNetwork() - organism->getNeuralNetwork().getOutputs()[3];
	if (heatControlViaNeuralNetwork < LOWEST_HEAT_LOSS_VALUE)
	{
		heatControlViaNeuralNetwork = LOWEST_HEAT_LOSS_VALUE;
	}
	if (heatControlViaNeuralNetwork > HIGHEST_HEAT_LOSS_VALUE)
	{
		heatControlViaNeuralNetwork = HIGHEST_HEAT_LOSS_VALUE;
	}
	organism->setHeatLossViaNeuralNetwork(heatControlViaNeuralNetwork);
}