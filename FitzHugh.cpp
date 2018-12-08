#include "FitzHugh.h"



FitzHugh::FitzHugh()
{
	_a = randomReal(0.2, 0.7);
	_b = randomReal(0.2, 0.8);
	_tau = randomReal(9.0, 14.0);
	
}


FitzHugh::~FitzHugh()
{
}


//Euler integration
void FitzHugh::calcSlope()
{
	double sum = 0.0;
	for (vector<double>::iterator i = _inputs.begin(); i != _inputs.end(); ++i)
	{
		sum += *i;
	}
	_dx = _x - 1.0 / 3.0 * _x * _x * _x - _y + sum;
	_dy = (_x - _a - _b*_y) / _tau;
}

void FitzHugh::eulerStep()
{
	_x += _dx * _stepSize;
	_y += _dy * _stepSize;
}


//----------------------------------------------------------------------
//Random engine call
double FitzHugh::randomReal(const double lowerBoundary, const double upperBoundary)
{
	uniform_real_distribution<double> distribution_real(lowerBoundary, upperBoundary);
	return distribution_real(mersenne_generator);
}

int FitzHugh::randomInt(const int lowerBoundary, const int upperBoundary)
{
	uniform_int_distribution<int> distribution_int(lowerBoundary, upperBoundary);
	return distribution_int(mersenne_generator);
}

//Random engine initialisation
random_device FitzHugh::seed_generator;
unsigned FitzHugh::seed = seed_generator();
mt19937 FitzHugh::mersenne_generator(FitzHugh::seed);