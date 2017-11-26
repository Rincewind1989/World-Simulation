#include "Organism.h"

Organism::Organism()
{
	_positionX = randomReal(0, (double)SIMULATION_X);
	_positionY = randomReal(0, (double)SIMULATION_Y);

	_red = randomInt(0, 255);
	_green = randomInt(0, 255);
	_blue = randomInt(0, 255);
	_alpha = randomInt(128, 255);
}

//Asexual breeding for an organism
Organism Organism::asexualBreeding()
{
	Organism child;
	vector<double> weights = _neuralNetwork.getWeights();
	child.getNeuralNetwork().setWeights(weights);
	child.getNeuralNetwork().processMutations();
	child._positionX = _positionX + randomReal(-10.0, 10.0);
	child._positionY = _positionY + randomReal(-10.0, 10.0);
	if (_positionX > SIMULATION_X)
	{
		_positionX = SIMULATION_X;
	}
	if (_positionX < 0)
	{
		_positionX = 0;
	}
	if (_positionY > SIMULATION_Y)
	{
		_positionY = SIMULATION_Y;
	}
	if (_positionY < 0)
	{
		_positionY = 0;
	}

	child._red = _red + mutateStat(_red);
	child._green = _green + mutateStat(_green);
	child._blue = _blue + mutateStat(_blue);
	child._alpha = _alpha + mutateStat(_alpha);
	child._size = _size + mutateStat(_size);


	if (_alpha < ALPHA_MIN)
	{
		child._alpha = ALPHA_MIN;
	}

	return child;
}


//sexual breeding
Organism::Organism(const Organism &father, const Organism &mother)
{

	vector<double> weights = vector<double>(father._neuralNetwork.getWeights().size());
	if (randomInt(0, 1) == 0)
	{
		for (int i = 0; i < weights.size(); i++)
		{
			if (i % 2 == 0)
			{
				weights[i] = father._neuralNetwork.getWeights()[i];
			}
			else
			{
				weights[i] = mother._neuralNetwork.getWeights()[i];
			}
		}
		getNeuralNetwork().setWeights(weights);
		getNeuralNetwork().processMutations();
		_positionX = father.getPositionX() + randomReal(-10.0, 10.0);
		_positionY = father.getPositionY() + randomReal(-10.0, 10.0);

		_red = father.getRed() + mutateStat(father.getRed());
		_green = father.getGreen() + mutateStat(father.getGreen());
		_blue = father.getBlue() + mutateStat(father.getBlue());
		_alpha = father.getAlpha() + mutateStat(father.getAlpha());
		_size = father.getSize() + mutateStat(father.getSize());


		if (_alpha < ALPHA_MIN)
		{
			_alpha = ALPHA_MIN;
		}
	}
	else
	{
		for (int i = 0; i < weights.size(); i++)
		{
			if (i % 2 == 0)
			{
				weights[i] = mother._neuralNetwork.getWeights()[i];
			}
			else
			{
				weights[i] = father._neuralNetwork.getWeights()[i];
			}
		}
		getNeuralNetwork().setWeights(weights);
		getNeuralNetwork().processMutations();
		_positionX = mother.getPositionX() + randomReal(-10.0, 10.0);
		_positionY = mother.getPositionY() + randomReal(-10.0, 10.0);

		_red = mother.getRed() + mutateStat(mother.getRed());
		_green = mother.getGreen() + mutateStat(mother.getGreen());
		_blue = mother.getBlue() + mutateStat(mother.getBlue());
		_alpha = mother.getAlpha() + mutateStat(mother.getAlpha());
		_size = mother.getSize() + mutateStat(mother.getSize());


		if (_alpha < ALPHA_MIN)
		{
			_alpha = ALPHA_MIN;
		}
	}

	if (_positionX > SIMULATION_X)
	{
		_positionX = SIMULATION_X;
	}
	if (_positionX < 0)
	{
		_positionX = 0;
	}
	if (_positionY > SIMULATION_Y)
	{
		_positionY = SIMULATION_Y;
	}
	if (_positionY < 0)
	{
		_positionY = 0;
	}

}


Organism::~Organism()
{
}


//Mutates the color of the organism by chance
double Organism::mutateStat(double value)
{
	if (randomReal(0.0, 1.0) < MUTATE_COLOR)
	{
		return value * randomReal(-0.1, 0.1);
	}
}


//Getters/Setters
void Organism::setPositionX(const double &positionX)
{
	_positionX = positionX;
}


void Organism::addPositionX(const double &positionX)
{
	_positionX += positionX;
}


const double &Organism::getPositionX() const
{
	return _positionX;
}


void Organism::setPositionY(const double &positionY)
{
	_positionY = positionY;
}


void Organism::addPositionY(const double &positionY)
{
	_positionY += positionY;
}


const double &Organism::getPositionY() const
{
	return _positionY;
}


void Organism::setEnergy(const double &energy)
{
	_energy = energy;
}


void Organism::addEnergy(const double &energy)
{
	_energy += energy;
}


void Organism::addEnergyViaFood(const double &food)
{
	_energy += _foodEnergyFactor * food;
}


const double &Organism::getEnergy() const
{
	return _energy;
}


void Organism::setTemperature(const double &temperature)
{
	_temperature = temperature;
}


void Organism::addTemperature(const double &temperature)
{
	_temperature += temperature;
}


const double &Organism::getTemperature()
{
	return _temperature;
}


void Organism::setHeatEnergyProduction(const double &heatEnergyProduction)
{
	_energyHeatProduction = heatEnergyProduction;
}


const double Organism::getHeatEnergyProduction() const
{
	return _energyHeatProduction;
}


void Organism::setHeatLossFactor(const double &heatLossFactor)
{
	_heatLoss = heatLossFactor;
}

const double &Organism::getHeatLossFactor() const
{
	return _heatLoss;
}


void Organism::setSize(const double &size)
{
	_size = size;
}


const double &Organism::getSize() const
{
	return _size;
}


void Organism::setRed(const int &red)
{
	_red = red;
}


const double &Organism::getRed() const
{
	return _red;
}


void Organism::setGreen(const int &green)
{
	_green = green;
}


const double &Organism::getGreen() const
{
	return _green;
}


void Organism::setBlue(const int &blue)
{
	_blue = blue;
}


const double &Organism::getBlue() const
{
	return _blue;
}


void Organism::setAlpha(const int &alpha)
{
	_alpha = alpha;
}


const double &Organism::getAlpha() const
{
	return _alpha;
}


NeuralNetwork &Organism::getNeuralNetwork()
{
	return _neuralNetwork;
}


const double &Organism::getFitness() const
{
	return _fitness;
}


void Organism::setFitness(const double &fitness)
{
	_fitness = fitness;
}


void Organism::addFitness(const double &fitness)
{
	_fitness += fitness;
}


void Organism::setDied(const bool dead)
{
	_dead = dead;
}



bool Organism::getDied()
{
	return _dead;
}


//Random engine call
double Organism::randomReal(const double lowerBoundary, const double upperBoundary)
{
	uniform_real_distribution<double> distribution_real(lowerBoundary, upperBoundary);
	return distribution_real(mersenne_generator);
}

int Organism::randomInt(const int lowerBoundary, const int upperBoundary)
{
	uniform_int_distribution<int> distribution_int(lowerBoundary, upperBoundary);
	return distribution_int(mersenne_generator);
}

//Random engine initialisation
random_device Organism::seed_generator;
unsigned Organism::seed = seed_generator();
mt19937 Organism::mersenne_generator(Organism::seed);
