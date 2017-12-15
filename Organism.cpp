#include "Organism.h"

Organism::Organism()
{
	_positionX = randomReal(0, (double)SIMULATION_X);
	_positionY = randomReal(0, (double)SIMULATION_Y);

	//Colors
	_red = randomInt(0, 255);
	_green = randomInt(0, 255);
	_blue = randomInt(0, 255);
	_alpha = randomInt(128, 255);

	//Size
	_size = SIZE_ORGANISM;

	//Body funtionalities
	_energyHeatProduction = ENERGY_HEAT_PRODUCTION;
	_heatLoss = HEAT_LOSS_FACTOR;
	_foodEnergyFactor = FOOD_ENERGY_FACTOR;

	//Randomness in every stat

	_red = _red + mutateStat(_red);
	_green = _green + mutateStat(_green);
	_blue = _blue + mutateStat(_blue);
	_alpha = _alpha + mutateStat(_alpha);

	_size = _size + mutateStat(_size);

	_energyHeatProduction = _energyHeatProduction + mutateStat(_energyHeatProduction);
	_heatLoss = _heatLoss + mutateStat(_heatLoss);

	//Condition
	_energy = STARTING_ENERGY;
	_temperature = STARTING_TEMPERATURE;
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
	if (child._positionX > SIMULATION_X)
	{
		child._positionX = SIMULATION_X;
	}
	if (child._positionX < 0)
	{
		child._positionX = 0;
	}
	if (child._positionY > SIMULATION_Y)
	{
		child._positionY = SIMULATION_Y;
	}
	if (child._positionY < 0)
	{
		child._positionY = 0;
	}

	double newRed = _red + mutateStat(_red) + randomReal(-25.0, 15.0);
	if (newRed < 0) { newRed = 0; }
	if (newRed > 255) { newRed = 255; }
	child.setRed(newRed);

	double newGreen = _green + mutateStat(_green) + randomReal(-25.0, 15.0);
	if (newGreen < 0) { newGreen = 0; }
	if (newGreen > 255) { newGreen = 255; }
	child.setGreen(newGreen);

	double newBlue = _blue + mutateStat(_blue) + randomReal(-25.0, 15.0);
	if (newBlue < 0) { newBlue = 0; }
	if (newBlue > 255) { newBlue = 255; }
	child.setBlue(newBlue);

	double newAlpha = _alpha + mutateStat(_alpha) + randomReal(-25.0, 15.0);
	if (newAlpha < 128) { newAlpha = 128; }
	if (newAlpha > 255) { newAlpha = 255; }
	child.setAlpha(newAlpha);

	double newSize = _size + mutateStat(_size);
	if (newSize < 0.1) { newSize = 0.1; }
	child.setSize(newSize);

	double newEHP = _energyHeatProduction + mutateStat(_energyHeatProduction);
	if (newEHP < 0.0) { newEHP = 0.0; }
	_energyHeatProduction = newEHP;
	child.setHeatEnergyProduction(newEHP);

	double newHL = _heatLoss + mutateStat(_heatLoss);
	if (newHL < LOWEST_HEAT_LOSS_VALUE) { newEHP = LOWEST_HEAT_LOSS_VALUE; }
	if (newHL < HIGHEST_HEAT_LOSS_VALUE) { newEHP = HIGHEST_HEAT_LOSS_VALUE; }
	_heatLoss = newHL;
	child.setHeatLossFactor(newHL);

	return child;
}


//sexual breeding
Organism::Organism(const Organism &father, const Organism &mother)
{
	double mutateAdd;
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

		double newX = father.getPositionX() + randomReal(-10.0, 10.0);
		if (newX < 0) { newX = 0; }
		if (newX > SIMULATION_X) { newX = SIMULATION_X; }
		_positionX = newX;

		double newY = father.getPositionY() + randomReal(-10.0, 10.0);
		if (newY < 0) { newY = 0; }
		if (newY > SIMULATION_Y) { newY = SIMULATION_Y; }
		_positionY = newY;

		mutateAdd = mutateStat(father.getRed()) + randomReal(-25.0, 15.0);
		double newRed = father.getRed() + mutateAdd;
		if (newRed < 0) { newRed = 0; }
		if (newRed > 255) { newRed = 255; }
		_red = newRed;

		mutateAdd = mutateStat(father.getGreen()) + randomReal(-25.0, 15.0);
		double newGreen = father.getGreen() + mutateAdd;
		if (newGreen < 0) { newGreen = 0; }
		if (newGreen > 255) { newGreen = 255; }
		_green = newGreen;

		mutateAdd = mutateStat(father.getBlue()) + randomReal(-25.0, 15.0);
		double newBlue = father.getBlue() + mutateAdd;
		if (newBlue < 0) { newBlue = 0; }
		if (newBlue > 255) { newBlue = 255; }
		_blue = newBlue;

		mutateAdd = mutateStat(father.getAlpha()) + randomReal(-25.0, 15.0);
		double newAlpha = father.getAlpha() + mutateAdd;
		if (newAlpha < ALPHA_MIN) { newAlpha = ALPHA_MIN; }
		if (newAlpha > 255) { newAlpha = 255; }
		_alpha = newAlpha;

		mutateAdd = mutateStat(father.getSize());
		double newSize = father.getSize() + mutateAdd;
		if (newSize < 0.1) { newSize = 0.1; }
		_size = newSize;

		double newEHP = father.getHeatEnergyProduction() + mutateStat(father.getHeatEnergyProduction());
		if (newEHP < 0.0) { newEHP = 0.0; }
		_energyHeatProduction = newEHP;

		double newHL = father.getHeatLossFactor() + mutateStat(father.getHeatLossFactor());
		if (newHL < LOWEST_HEAT_LOSS_VALUE) { newEHP = LOWEST_HEAT_LOSS_VALUE; }
		if (newHL < HIGHEST_HEAT_LOSS_VALUE) { newEHP = HIGHEST_HEAT_LOSS_VALUE; }
		_heatLoss = newHL;

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

		double newX = mother.getPositionX() + randomReal(-10.0, 10.0);
		if (newX < 0) { newX = 0; }
		if (newX > SIMULATION_X) { newX = SIMULATION_X; }
		_positionX = newX;

		double newY = mother.getPositionY() + randomReal(-10.0, 10.0);
		if (newY < 0) { newY = 0; }
		if (newY > SIMULATION_Y) { newY = SIMULATION_Y; }
		_positionY = newY;

		mutateAdd = mutateStat(father.getRed()) + randomReal(-25.0, 15.0);
		double newRed = father.getRed() + mutateAdd;
		if (newRed < 0) { newRed = 0; }
		if (newRed > 255) { newRed = 255; }
		_red = newRed;

		mutateAdd = mutateStat(father.getGreen()) + randomReal(-25.0, 15.0);
		double newGreen = father.getGreen() + mutateAdd;
		if (newGreen < 0) { newGreen = 0; }
		if (newGreen > 255) { newGreen = 255; }
		_green = newGreen;

		mutateAdd = mutateStat(father.getBlue()) + randomReal(-25.0, 15.0);
		double newBlue = father.getBlue() + mutateAdd;
		if (newBlue < 0) { newBlue = 0; }
		if (newBlue > 255) { newBlue = 255; }
		_blue = newBlue;

		mutateAdd = mutateStat(father.getAlpha()) + randomReal(-25.0, 15.0);
		double newAlpha = father.getAlpha() + mutateAdd;
		if (newAlpha < ALPHA_MIN) { newAlpha = ALPHA_MIN; }
		if (newAlpha > 255) { newAlpha = 255; }
		_alpha = newAlpha;

		mutateAdd = mutateStat(father.getSize());
		double newSize = mother.getSize() + mutateAdd;
		if (newSize < 0.1) { newSize = 0.1; }
		_size = newSize;

		double newEHP = mother.getHeatEnergyProduction() + mutateStat(mother.getHeatEnergyProduction());
		if (newEHP < 0.0) { newEHP = 0.0; }
		_energyHeatProduction = newEHP;

		double newHL = mother.getHeatLossFactor() + mutateStat(mother.getHeatLossFactor());
		if (newHL < LOWEST_HEAT_LOSS_VALUE) { newEHP = LOWEST_HEAT_LOSS_VALUE; }
		if (newHL < HIGHEST_HEAT_LOSS_VALUE) { newEHP = HIGHEST_HEAT_LOSS_VALUE; }
		_heatLoss = newHL;
	}
}


Organism::~Organism()
{
}


//Mutates a state of the organism by chance
double Organism::mutateStat(double value)
{
	if (randomReal(0.0, 1.0) < MUTATE_STAT)
	{
		return value * randomReal(-0.1, 0.1);
	}

	return 0.0;
}

//----------------------------------------------------------------------

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

void Organism::setdeltaX(const double &deltaX)
{
	_deltaX = deltaX;
}

const double &Organism::getDeltaX() const
{
	return _deltaX;
}

//----------------------------------------------------------------------

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

void Organism::setdeltaY(const double &deltaY)
{
	_deltaY = deltaY;
}

const double &Organism::getDeltaY() const
{
	return _deltaY;
}

//----------------------------------------------------------------------

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

//----------------------------------------------------------------------

void Organism::setTemperature(const double &temperature)
{
	_temperature = temperature;
}

void Organism::addTemperature(const double &temperature)
{
	_temperature += temperature;
}

const double &Organism::getTemperature() const
{
	return _temperature;
}

//----------------------------------------------------------------------

void Organism::setHeatEnergyProduction(const double &heatEnergyProduction)
{
	_energyHeatProduction = heatEnergyProduction;
}

const double Organism::getHeatEnergyProduction() const
{
	return _energyHeatProduction;
}

//----------------------------------------------------------------------

void Organism::setHeatLossFactor(const double &heatLossFactor)
{
	_heatLoss = heatLossFactor;
}

const double &Organism::getHeatLossFactor() const
{
	return _heatLoss;
}

void Organism::setHeatLossViaNeuralNetwork(const double &heatLossViaNeuralNetwork)
{
	_heatControleViaNeuralNetwork = heatLossViaNeuralNetwork;
}

const double &Organism::getHeatLossViaNeuralNetwork() const
{
	return _heatControleViaNeuralNetwork;
}

//----------------------------------------------------------------------

void Organism::setFoodEnergyFctor(const int &foodEnergyFactor)
{
	_foodEnergyFactor = foodEnergyFactor;
}

const double &Organism::getFoodEnergyFctor() const
{
	return _foodEnergyFactor;
}

//----------------------------------------------------------------------

void Organism::setSize(const double &size)
{
	_size = size;
}

const double &Organism::getSize() const
{
	return _size;
}

//----------------------------------------------------------------------

void Organism::setRed(const int &red)
{
	_red = red;
}

const double &Organism::getRed() const
{
	return _red;
}

//----------------------------------------------------------------------

void Organism::setGreen(const int &green)
{
	_green = green;
}

const double &Organism::getGreen() const
{
	return _green;
}

//----------------------------------------------------------------------

void Organism::setBlue(const int &blue)
{
	_blue = blue;
}

const double &Organism::getBlue() const
{
	return _blue;
}

//----------------------------------------------------------------------

void Organism::setAlpha(const int &alpha)
{
	_alpha = alpha;
}

const double &Organism::getAlpha() const
{
	return _alpha;
}

//----------------------------------------------------------------------

NeuralNetwork &Organism::getNeuralNetwork()
{
	return _neuralNetwork;
}

//----------------------------------------------------------------------

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

//----------------------------------------------------------------------

void Organism::setDied(const bool dead)
{
	_dead = dead;
}

bool Organism::getDied()
{
	return _dead;
}

//----------------------------------------------------------------------
void Organism::setWasHit(const bool hit)
{
	_washit = hit;
}
bool Organism::getWasHit()
{
	return _washit;
}

//----------------------------------------------------------------------
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
