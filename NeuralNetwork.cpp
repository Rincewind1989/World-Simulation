#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork()
{
	//Creating the network
	for (int i = 0; i < NUM_LAYERS; i++)
	{
		if (i == 0)
		{
			_numNeuronsInLayer.push_back(INPUT_NEURONS);
		}
		else if (i != 0 && i == NUM_LAYERS - 1)
		{
			_numNeuronsInLayer.push_back(OUTPUT_NEURONS);
		}
		else
		{
			_numNeuronsInLayer.push_back(HIDDEN_NEURONS);
		}
	}

	//Creating the weights, default constructor will create weights with random values
	for (int i = 0; i < _weights.size(); i++)
	{
		_weights[i] = randomReal(MIN_RANDOM_WEIGHT, MAX_RANDOM_WEIGHT);
	}
}


NeuralNetwork::~NeuralNetwork()
{
}


//Getters/Setters
const vector<double> &NeuralNetwork::getOutputs() const
{
	return _outputs;
}


//Getters/Setters
const vector<double> &NeuralNetwork::getWeights() const
{
	return _weights;
}


void NeuralNetwork::setWeights(const vector<double> &weights)
{
	_weights = weights;
}


//Adds random mutations to the weights
void NeuralNetwork::processMutations()
{
	for (int i = 0; i < _weights.size(); i++)
	{
		if (randomReal(0, 1.0) < CHANCE_MUTATE)
		{
			_weights[i] = _weights[i] * MUTATION_PERTUBATE_PROCENT + randomReal(-1.0, 1.0)*MUTATION_PERTUBATE_ADD;
		}
	}
}


//Feeds the momentarily saved input forward through the network
void NeuralNetwork::feedForward(const vector<double> &inputs)
{
	vector<double> layerOutput = inputs;
	layerOutput.push_back(1.0);
	vector<double> tmpOutput;
	double sum = 0.0;
	double result = 0.0;
	for (int layer = 1; layer < _numNeuronsInLayer.size(); layer++)
	{
		tmpOutput = vector<double>(_numNeuronsInLayer[layer]);
		for (int neuron = 0; neuron < _numNeuronsInLayer[layer]; neuron++)
		{
			sum = 0.0;
			for (int connection = 0; connection < _numNeuronsInLayer[layer - 1] + 1; connection++)
			{
				sum += layerOutput[connection] * _weights[neuron + connection*_numNeuronsInLayer[layer]];
			}
			result = sigmoid(sum);
			tmpOutput[neuron] = result;
		}
		layerOutput.clear();
		layerOutput = tmpOutput;
		layerOutput.push_back(1.0);
	}
	layerOutput.pop_back();
	_outputs = layerOutput;
}


//Sigmoid function is the activation function
const double NeuralNetwork::sigmoid(const double &sum)
{
	return (SIGMOID_STRETCHY_FACTOR * ((1.0 / (1.0 + exp(SIGMOID_STRETCHX_FACTOR * sum))) - 0.5));
}


//Random engine call
double NeuralNetwork::randomReal(const double lowerBoundary, const double upperBoundary)
{
	uniform_real_distribution<double> distribution_real(lowerBoundary, upperBoundary);
	return distribution_real(mersenne_generator);
}

int NeuralNetwork::randomInt(const int lowerBoundary, const int upperBoundary)
{
	uniform_int_distribution<int> distribution_int(lowerBoundary, upperBoundary);
	return distribution_int(mersenne_generator);
}

//Random engine initialisation
random_device NeuralNetwork::seed_generator;
unsigned NeuralNetwork::seed = seed_generator();
mt19937 NeuralNetwork::mersenne_generator(NeuralNetwork::seed);