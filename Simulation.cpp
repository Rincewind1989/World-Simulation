#include <algorithm>
#include <iostream>

#include "Simulation.h"
#include "Equations.h"

Simulation::Simulation()
{
	_organisms.reserve(10000);
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
				inputs[index] = _landscape.getTiles()[positionY + i][positionX + j].getTemperature() / OPTIM_TEMPERATURE;
				index++;
				inputs[index] = _landscape.getTiles()[positionY + i][positionX + j].getFood() / MAX_FOOD_ON_TILE;
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

	//Gets the 4 next entities with their distance, color and size
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
			distance = sqrt((it->getPositionX() - organism.getPositionX()) * (it->getPositionX() - organism.getPositionX()) 
							+ (it->getPositionY() - organism.getPositionY()) * (it->getPositionY() - organism.getPositionY()));
			if (distance < minDistance && find(nearestOrganisms.begin(), nearestOrganisms.end(), &(*it)) != nearestOrganisms.end() && distance < RADIUS_NEXT_ENTITIES)
			{
				minDistance = distance;
				tmpNearestOrganism = &(*it);
			}
		}
		if (tmpNearestOrganism != NULL)
		{
			nearestOrganisms.push_back(tmpNearestOrganism);
			inputs[index] = (tmpNearestOrganism->getPositionX() - organism.getPositionX()) / RADIUS_NEXT_ENTITIES;
			index++;
			inputs[index] = (tmpNearestOrganism->getPositionY() - organism.getPositionY()) / RADIUS_NEXT_ENTITIES;
			index++;
			inputs[index] = tmpNearestOrganism->getSize() / SIZE_ORGANISM;
			index++;
			inputs[index] = tmpNearestOrganism->getAlpha() / 255.0;
			index++;
			inputs[index] = tmpNearestOrganism->getBlue() / 255.0;
			index++;
			inputs[index] = tmpNearestOrganism->getGreen() / 255.0;
			index++;
			inputs[index] = tmpNearestOrganism->getRed() / 255.0;
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
	inputs[index] = organism.getTemperature() / OPTIM_TEMPERATURE;
	index++;
	inputs[index] = organism.getEnergy() / organism.getMaxEnergy();
	index++;
	inputs[index] = organism.getSize() / SIZE_ORGANISM;
	index++;
	inputs[index] = organism.getAlpha() / 255.0;
	index++;
	inputs[index] = organism.getRed() / 255.0;
	index++;
	inputs[index] = organism.getBlue() / 255.0;
	index++;
	inputs[index] = organism.getRed() / 255.0;

	return inputs;
}

//----------------------------------------------------------------------

//Updates the whole simulation
void Simulation::updateSimulation()
{
	_accDeltaFrame += 1.0;
	updateOrganisms();
	updateWorld();
}

//----------------------------------------------------------------------

//Updates all dynamics by time
void Simulation::updateWorld()
{
	updateTemperature();
	updateFoodAsODE();
}


//----------------------------------------------------------------------

//Updates all organisms by time
void Simulation::updateOrganisms()
{
	vector<Organism>::iterator it = _organisms.begin();
	updateWasHit();
	while (it != _organisms.end() && _organisms.size() > 0)
	{
		//Update thinking and movement
		updateNeuralNetworks(&(*it));
		//updateBodyFuncViaNeuralNetwork(&(*it));
		updateMovement(&(*it));

		//Update body properties
		updateHeatEnergy(&(*it));
		updateEnergy(&(*it));
		updateEating(&(*it));
		updateAttack(&(*it));
		updateAge(&(*it));

		//Create organisms
		createOrganismViaAsexuell(&(*it));
		//createOrganismViaFitness(&(*it));	//Creates every X frames (Default 25) a child breeded by chance from the fittest organisms
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
void Simulation::updateNeuralNetworks(Organism* organism)
{
	organism->getNeuralNetwork().feedForward(getInputs((*organism)));
}

/*//Update Body functions based on neural network output
void Simulation::updateBodyFuncViaNeuralNetwork(Organism *organism)
{
	updateHeatControl(&(*organism));
}*/

//Updates the movement of every organism
void Simulation::updateMovement(Organism* organism)
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
	organism->setdeltaX(getTempBasedFunction(*organism) / organism->getSize() * MOVEMENT_SPEED * organism->getNeuralNetwork().getOutputs()[0]);
	organism->addPositionX(organism->getDeltaX() * movementFactorIfinWater);
	if (organism->getPositionX() < 0.0)
		organism->setPositionX(0.0);
	if (organism->getPositionX() > SIMULATION_X - 1)
		organism->setPositionX(SIMULATION_X - 1);

	//Change y-coordinate
	organism->setdeltaY(getTempBasedFunction(*organism) / organism->getSize() * MOVEMENT_SPEED * organism->getNeuralNetwork().getOutputs()[1]);
	organism->addPositionY((organism->getDeltaY() * MOVEMENT_REDUCTION_IN_WATER));
	if (organism->getPositionY() < 0.0)
		organism->setPositionY(0.0);
	if (organism->getPositionY() > SIMULATION_Y - 1)
		organism->setPositionY(SIMULATION_Y - 1);
}


//Checks every Organism if it died
bool Simulation::checkForDeath(Organism* organism)
{
	if (organism->getDied())
	{
		if (&(*organism) == &(*_informationOrganism))
			_informationOrganism = NULL;

		if (&(*organism) == &(_organisms[_organisms.size() - 1]))
		{
			_organisms.pop_back();
			return true;
		}

		*organism = _organisms[_organisms.size() - 1];
		if (&(_organisms[_organisms.size() - 1]) == &(*_informationOrganism))
			_informationOrganism = &(*organism);
		_organisms.pop_back();			
	}
	return false;
}

//Update fitness by time
void Simulation::updateFitness(Organism* organism)
{
	organism->addFitness(0.1);
	if (organism->getFitness() > _highestFitness)
		_highestFitness = organism->getFitness();
}

//----------------------------------------------------------------------

//Create new organisms until the maximum Population is reached
void Simulation::createOrganismViaAsexuell(Organism* organism)
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
void Simulation::createOrganismBeforeExtinction(Organism* organism)
{
	while (_organisms.size() < MIN_NUMBER_ORGANISM)
	{
		Organism org;
		_organisms.push_back(org);

	}
}

//Create new organisms until the maximum Population is reached
void Simulation::createOrganismViaFitness(Organism* organism)
{

	if (_accDeltaFrame >= TIME_FOR_FITNESS_REPRODUCTION)
	{
		_accDeltaFrame -= TIME_FOR_FITNESS_REPRODUCTION;
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
//Get Average size
double Simulation::getAvgSize()
{
	double sum = 0.0;
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end() && _organisms.size() > 0)
	{
		sum += it->getSize();
		++it;
	}
	return sum / _organisms.size();
}

//Get Smallest Size
double Simulation::getSmallSize()
{
	double size = 100000000.0;
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end() && _organisms.size() > 0)
	{
		if (it->getSize() < size)
			size = it->getSize();
		++it;
	}
	return size;
}

//Get biggest Size
double Simulation::getBiggestSize()
{
	double size = 0.0;
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end() && _organisms.size() > 0)
	{
		if (it->getSize() > size)
			size = it->getSize();
		++it;
	}
	return size;
}

//----------------------------------------------------------------------
//Get Average size
double Simulation::getAvgAge()
{
	double sum = 0.0;
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end() && _organisms.size() > 0)
	{
		sum += it->getAge();
		++it;
	}
	return sum / _organisms.size();
}

//Get biggest Size
double Simulation::getHighestAge()
{
	double age = 0.0;
	vector<Organism>::iterator it = _organisms.begin();
	while (it != _organisms.end() && _organisms.size() > 0)
	{
		if (it->getAge() > age)
			age = it->getAge();
		++it;
	}
	return age;
}

//----------------------------------------------------------------------

//Updates the time elapsed since last update
void Simulation::deltaTime()
{
	const sf::Time delta = _clock.restart();
	_deltaTime = (delta.asSeconds());
	_accDeltaTime += _deltaTime;
}

//Check if delta time is greater than slowmotion time
bool Simulation::timelapseCheck()
{
	if (_accDeltaTime >= 1.0 / ((TIME_LAPSE + 1) * 5))
	{
		_accDeltaTime -= 1.0 / ((TIME_LAPSE + 1) * 5);
		return true;
	}
	return false;
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
		x = 0;
	if (x > SIMULATION_X - 1)
		x = SIMULATION_X - 1;
	if (y < 0)
		y = 0;
	if (y > SIMULATION_Y - 1)
		y = SIMULATION_Y - 1;
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