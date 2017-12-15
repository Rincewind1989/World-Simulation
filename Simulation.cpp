#include <algorithm>
#include <iostream>

#include "Simulation.h"

Simulation::Simulation()
{
	_organisms.reserve(5000);
	for (int i = 0; i < STARTING_NUMBER_ORGANISM; i++)
	{
		_organisms.push_back(Organism());
	}
}

Simulation::~Simulation()
{
}

//----------------------------------------------------------------------

Landscape &Simulation::getLandscape()
{
	return _landscape;
}

//----------------------------------------------------------------------

//Gets an organism by index
Organism &Simulation::getOrganismByIndex(int index)
{
	return _organisms[index];
}

//Gets the Organisms of this simulation
vector<Organism> &Simulation::getOrganisms()
{
	return _organisms;
}

//----------------------------------------------------------------------

//Sets the Information of the organism
void Simulation::setInformationOrganism(Organism* org)
{
	_informationOrganism = org;
}

//Gets the Information of the Organism
Organism* Simulation::getInformationOrganism() const
{
	return _informationOrganism;
}

//----------------------------------------------------------------------
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

	//Gets the 4 next entities with their position, color and size
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
			inputs[index] = tmpNearestOrganism->getPositionX() - organism.getPositionX();
			index++;
			inputs[index] = tmpNearestOrganism->getPositionY() - organism.getPositionY();
			index++;
			inputs[index] = tmpNearestOrganism->getSize();
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
	index++;
	inputs[index] = organism.getSize();
	index++;
	inputs[index] = organism.getAlpha();
	index++;
	inputs[index] = organism.getRed();
	index++;
	inputs[index] = organism.getBlue();
	index++;
	inputs[index] = organism.getRed();

	return inputs;
}

//----------------------------------------------------------------------

//Updates the whole simulation
void Simulation::updateSimulation()
{
	updateOrganisms();
	updateWorld();
}

//----------------------------------------------------------------------

//Updates all dynamics by time
void Simulation::updateWorld()
{
	updateTemperature();
	updateFood();
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
			if (randomReal(0.000, 1.000) < CHANCE_BIG_FOOD_GROWTH)
			{
				foodAdd = _deltaTime * randomReal(MAX_FOOD_ON_TILE / 5.0, MAX_FOOD_ON_TILE / 2.5);
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

//----------------------------------------------------------------------

//Updates all organisms by time
void Simulation::updateOrganisms()
{
	vector<Organism>::iterator it = _organisms.begin();
	updateWasHit();
	while (it != _organisms.end() && _organisms.size() > 0)
	{
		updateNeuralNetworks(&(*it));
		updateBodyFuncViaNeuralNetwork(&(*it));
		updateMovement(&(*it));
		updateHeatEnergy(&(*it));
		updateEnergy(&(*it));
		updateEating(&(*it));
		updateAttack(&(*it));	
		createOrganismViaAsexuell(&(*it));
		createOrganismViaFitness(&(*it));
		createOrganismBeforeExtinction(&(*it));
		updateFitness(&(*it));
		if (checkForDeath(&(*it))) { break; }
		++it;
	}
}

//Updates washit to false in the beginning
void Simulation::updateWasHit()
{
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end() && _organisms.size() > 0)
	{
		it->setWasHit(false);
		++it;
	}
}

//Update the neural network of all organisms
void Simulation::updateNeuralNetworks(Organism *organism)
{
	organism->getNeuralNetwork().feedForward(getInputs((*organism)));
}

//Update Body functions based on neural network output
void Simulation::updateBodyFuncViaNeuralNetwork(Organism *organism)
{
	updateHeatControl(&(*organism));
}

//Updates the movement of every organism
void Simulation::updateMovement(Organism *organism)
{
	int x = 0;
	int y = 0;
	double movementFactorIfinWater = 1.0;
	getTileXYViaOrganism(x, y, &(*organism));
	if (_landscape.getTiles()[y][x].getHeight() < WATER_LEVEL)
	{
		movementFactorIfinWater = MOVEMENT_REDUCTION_IN_WATER;
	}

	//Change x-coordinate
	organism->setdeltaX(getTempBasedFunction(*organism) / organism->getSize() * _deltaTime * MOVEMENT_SPEED * organism->getNeuralNetwork().getOutputs()[0]);
	organism->addPositionX(organism->getDeltaX() * MOVEMENT_REDUCTION_IN_WATER);
	if (organism->getPositionX() < 0.0)
	{
		organism->setPositionX(0.0);
	}
	if (organism->getPositionX() > SIMULATION_X)
	{
		organism->setPositionX(SIMULATION_X);
	}

	//Change y-coordinate
	organism->setdeltaY(getTempBasedFunction(*organism) / organism->getSize() * _deltaTime * MOVEMENT_SPEED * organism->getNeuralNetwork().getOutputs()[1]);
	organism->addPositionY((organism->getDeltaY() * MOVEMENT_REDUCTION_IN_WATER));
	if (organism->getPositionY() < 0.0)
	{
		organism->setPositionY(0.0);
	}
	if (organism->getPositionY() > SIMULATION_Y)
	{
		organism->setPositionY(SIMULATION_Y);
	}
}

//Update the energy of all organisms based on temperature loss
void Simulation::updateHeatEnergy(Organism *organism)
{
	double deltaTemperature;
	int x = 0;
	int y = 0;
	getTileXYViaOrganism(x, y, &(*organism));

	//Get lost temperature
	double lostTemperature = _deltaTime * organism->getHeatLossFactor() * organism->getHeatLossViaNeuralNetwork() * (organism->getTemperature() - _landscape.getTiles()[y][x].getTemperature());

	//Get added temperature
	double addTemperature = _deltaTime * organism->getHeatEnergyProduction();

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
	addEnergy += -1 * _deltaTime * organism->getSize() * organism->getSize() * SIZE_ENERGY_LOSS_FACTOR;

	//Update energy and temperature
	addEnergy += -1 * _deltaTime * organism->getHeatEnergyProduction() * ENERGY_CONSUMPTION_FACTOR;

	//Update Energy via movement
	int x = 0;
	int y = 0;
	double movementFactorIfinWater = 1.0;
	getTileXYViaOrganism(x, y, &(*organism));
	if (_landscape.getTiles()[y][x].getHeight() < WATER_LEVEL)
	{
		movementFactorIfinWater = MOVEMENT_ENERGY_FACTOR_IN_WATER;
	}
	addEnergy += -1 * _deltaTime * MOVEMENT_ENERGY_LOST * movementFactorIfinWater * sqrt((organism->getDeltaX() * organism->getDeltaX()) + fabs(organism->getDeltaY() * organism->getDeltaY()));


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
			double energy = organism->getSize() * _deltaTime * ATTACK_DAMAGE;
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

	food = getTempBasedFunction(*organism) * CONSUMPTION_FACTOR * _deltaTime;

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

//Checks every Organism if it died
bool Simulation::checkForDeath(Organism *organism)
{
	if (organism->getDied())
	{
		if (&(*organism) == &(_organisms[_organisms.size() - 1]))
		{
			_organisms.pop_back();
			_informationOrganism = NULL;
			return true;
		}

		*organism = _organisms[_organisms.size() - 1];
		_organisms.pop_back();
		if (&(_organisms[_organisms.size() - 1]) == &(*_informationOrganism))
		{
			_informationOrganism = &(*organism);
		}
			
		if (&(*organism) == &(*_informationOrganism))
		{
			_informationOrganism = NULL;
		}
	}

	return false;
}

//Update fitness by time
void Simulation::updateFitness(Organism *organism)
{
	organism->addFitness(_deltaTime);
	if (organism->getFitness() > _highestFitness)
	{
		_highestFitness = organism->getFitness();
	}
}

//----------------------------------------------------------------------

//Create new organisms until the maximum Population is reached
void Simulation::createOrganismViaAsexuell(Organism *organism)
{
	vector<Organism> newChilds;
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end())
	{
		if (it->getNeuralNetwork().getOutputs()[2] > 0.0 && it->getEnergy() > NEWLIFE_ENERGY_CONSUMPTION)
		{
			//Change adults energy
			it->addEnergy(-NEWLIFE_ENERGY_CONSUMPTION);

			//Create child
			Organism child = it->asexualBreeding();
			newChilds.push_back(child);
		}
		++it;
	}
	_organisms.insert(_organisms.end(), newChilds.begin(), newChilds.end());

}

//Create Organisms if number of Org goes under min value of living organism
void Simulation::createOrganismBeforeExtinction(Organism *organism)
{
	while (_organisms.size() < STARTING_NUMBER_ORGANISM)
	{
		Organism org;
		_organisms.push_back(org);

	}
}

//Create new organisms until the maximum Population is reached
void Simulation::createOrganismViaFitness(Organism *organism)
{

	if (_accDeltaTime >= TIME_FOR_FITNESS_REPRODUCTION)
	{
		_accDeltaTime -= TIME_FOR_FITNESS_REPRODUCTION;

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

//----------------------------------------------------------------------

//Gets the highest fitness
double Simulation::getHighestFitness()
{
	return _highestFitness;
}

//Gets the average fitness of all Organisms
double Simulation::getAvgFitness()
{
	double sum = 0.0;
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end() && _organisms.size() > 0)
	{
		sum += it->getFitness();
		++it;
	}
	return sum / _organisms.size();
}

//----------------------------------------------------------------------

//Updates the time elapsed since last update
void Simulation::deltaTime()
{
	const sf::Time delta = _clock.restart();
	if (TIME_LAPSE == 0)
	{
		_deltaTime = (delta.asSeconds());
	}
	if (TIME_LAPSE == 1)
	{
		_deltaTime = 1.0;
	}
	if (TIME_LAPSE == 2)
	{
		_deltaTime = delta.asSeconds() * 4.0;
	}
	_accDeltaTime += _deltaTime;
	if (SHOW_FPS)
	{
		printf("FPS: %f \n", 1 / _deltaTime);
	}
}

//----------------------------------------------------------------------

//Gets the efficiency of the body functions based on the optimum temperature
double Simulation::getTempBasedFunction(Organism &organism)
{
	double tempDifference = fabs(organism.getTemperature() - OPTIM_TEMPERATURE);
	return 1.0 - tempDifference / OPTIM_TEMPERATURE;
}

//----------------------------------------------------------------------

//Gets the position of the tile with the position of the organism
void Simulation::getTileXYViaOrganism(int &x, int &y, const Organism *organism)
{
	x = (int)organism->getPositionX();
	y = (int)organism->getPositionY();
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