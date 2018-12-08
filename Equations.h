#pragma once
#include "Simulation.h"
#include "Organism.h"

//Updates world and organism properties with every frame

//Update all food on every tile
void Simulation::updateFoodAsODE()
{
	double foodAdd;
	for (vector<vector<Tile>>::iterator it = _landscape.getTiles().begin() + 1; it != _landscape.getTiles().end() - 1; ++it)
	{
		for (vector<Tile>::iterator it2 = it->begin() + 1; it2 != it->end() - 1; ++it2)
		{

			if (CHANCE_FOOD_GROWTH >= 1.0 || randomReal(0.0, 1.0) < CHANCE_FOOD_GROWTH)
			{
				foodAdd = randomReal(0.0, (MAX_FOOD_ON_TILE - it2->getFood()) * FOOD_GROWTH_FACTOR);
				it2->addFood(foodAdd);
				if (it2->getFood() > MAX_FOOD_ON_TILE)
					it2->setFood(MAX_FOOD_ON_TILE);
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
			tempAdd = (it2->getOrignTemperature() - it2->getTemperature()) * 0.001;
			it2->addTemperature(tempAdd);
		}
	}
}


//-------------------------------------------------------------
//Updates properties of organisms

//Update the energy of all organisms based on temperature loss
void Simulation::updateHeatEnergy(Organism* organism)
{
	double deltaTemperature;
	int x = 0;
	int y = 0;
	getTileXYViaOrganism(x, y, &(*organism));

	//Get lost temperature
	double lostTemperature = HEAT_TIME_FACTOR * organism->getHeatLossFactor() * (organism->getTemperature() - _landscape.getTiles()[y][x].getTemperature());

	//Get added temperature
	double addTemperature = HEAT_TIME_FACTOR * organism->getHeatEnergyProduction();

	//Add/subtract temperature from environment and organism
	deltaTemperature = addTemperature - lostTemperature;
	_landscape.getTiles()[y][x].addTemperature(lostTemperature * TEMPERATURE_AIR_FLUX_FACTOR);
	organism->addTemperature(deltaTemperature);

	//Check if organism died from temperatureloss
	if (organism->getTemperature() <= COLD_TEMP_DEATH || organism->getTemperature() >= HEAT_TEMP_DEATH)
	{
		DEATH_BY_TEMP++;
		DEATHS++;
		organism->setDied(true);
	}
	++organism;
}

//Update the energy of all organisms based on size
void Simulation::updateEnergy(Organism* organism)
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
		movementFactorIfinWater = MOVEMENT_ENERGY_FACTOR_IN_WATER;
	addEnergy += -1 * MOVEMENT_ENERGY_LOST * movementFactorIfinWater * (organism->getDeltaDistanceForward() * organism->getDeltaDistanceForward());


	organism->addEnergy(addEnergy);

	//Check if organism died from energyloss
	if (organism->getEnergy() <= 0.0)
	{
		DEATH_BY_ENERGY++;
		DEATHS++;
		organism->setDied(true);
	}
}

//Updates every organism if it attacks nearby entity
void Simulation::updateAttack(Organism* organism)
{
	//Attack neary Entity if Neural network tells so and entity is close enough
	Organism* closestOrganism = NULL;
	if (organism->getNeuralNetwork().getOutputs()[4] > 0.0)
	{
		if (organism->getSize() * ATTACK_DAMAGE + organism->getEnergy() > organism->getMaxEnergy())
			return;
		double distanceClosestOrganism = 1000000000.0;
		double distance = 0.0;
		for (vector<Organism>::iterator it2 = _organisms.begin(); it2 != _organisms.end(); ++it2)
		{
			if (&(*it2) == &(*organism))
				continue;

			distance = sqrt((organism->getPositionX() - it2->getPositionX()) * (organism->getPositionX() - it2->getPositionX())
				+ (organism->getPositionY() - it2->getPositionY()) * (organism->getPositionY() - it2->getPositionY()));
			if (distanceClosestOrganism > distance)
			{
				distanceClosestOrganism = distance;
				closestOrganism = &(*it2);
			}
		}

		if (distanceClosestOrganism < organism->getSize() / 2.0)
		{
			closestOrganism->setWasHit(true);
			double energy = organism->getSize() * ATTACK_DAMAGE;
			//cout << "Organism " << &(*it) << " attacks for: " << energy << endl;
			if (energy > closestOrganism->getEnergy())
				energy = closestOrganism->getEnergy();
			closestOrganism->addEnergy(-energy);
			organism->addEnergy(energy);
		}
	}



	//Check if organism died from energy- or temperatureloss
	if (closestOrganism != NULL)
	{
		if (closestOrganism->getEnergy() <= 0.0)
		{
			DEATH_BY_ENERGY++;
			DEATHS++;
			closestOrganism->setDied(true);
		}
	}
}

//Update eating for every organism
void Simulation::updateEating(Organism* organism)
{
	double food = 0.0;
	int x = 0;
	int y = 0;
	food = 0.0;
	getTileXYViaOrganism(x, y, &(*organism));
	if (x < 0)
		x = 0;
	if (x > SIMULATION_X - 1)
		x = SIMULATION_X - 1;
	if (y < 0)
		y = 0;
	if (y > SIMULATION_Y - 1)
		y = SIMULATION_Y - 1;

	double movementFactorIfinWater = 1.0;
	getTileXYViaOrganism(x, y, &(*organism));
	if (_landscape.getTiles()[y][x].getHeight() < WATER_LEVEL)
	{
		movementFactorIfinWater = MOVEMENT_ENERGY_FACTOR_IN_WATER;
	}

	food = getTempBasedFunction(*organism) * CONSUMPTION_FACTOR * (1.0 - sqrt((organism->getDeltaDistanceForward() * organism->getDeltaDistanceForward()))/(getTempBasedFunction(*organism) / organism->getSize() * MOVEMENT_SPEED));
	if ((organism->getEnergyViaFoodValue(food) + organism->getEnergy()) > organism->getMaxEnergy())
		return;

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

//Updates every organism if it attacks nearby entity
void Simulation::updateAge(Organism* organism)
{
	organism->addAge(0.001);
	if (organism->getAge() > AVG_AGE_DEATH)
	{
		if (randomReal(0.0, 1.0) < 0.01 * fabs(organism->getAge() - AVG_AGE_DEATH))
		{
			DEATH_BY_AGE++;
			DEATHS++;
			organism->setDied(true);
		}
	}
}

/*//Update the Heat-Control of an Organism
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
}*/