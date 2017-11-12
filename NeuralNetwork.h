#pragma once

#include <vector>
#include <random>
#include "SimulationData.h"

using namespace std;

class NeuralNetwork
{
public:
	NeuralNetwork();
	~NeuralNetwork();

	//Getters/Setters
	vector<double> &getOutputs();

	void printInfo();

	//Feeds the momentarily saved input forward through the network
	void feedForward(
		const vector<double> &inputs);

	//Sigmoid functionas the activation function
	double sigmoid(
		const double &sum);

	//Getters/Setters
	vector<double> &getWeights();

	void setWeights(vector<double> &weights);
	
	//Adds random mutations to the weights
	void processMutations();

	//Random generator 
	double randomReal(
		const double lowerBoundary,
		const double upperBoundary);

	int randomInt(
		const int lowerBoundary,
		const int upperBoundary);

	static random_device seed_generator;
	static unsigned seed;
	static mt19937 mersenne_generator;

private:
	vector<int> _numNeuronsInLayer;
	vector<double> _weights = vector<double>(INPUT_NEURONS*HIDDEN_NEURONS + (NUM_LAYERS - 3)*HIDDEN_NEURONS + HIDDEN_NEURONS*OUTPUT_NEURONS);
	vector<double> _outputs = vector<double>(OUTPUT_NEURONS);
};

