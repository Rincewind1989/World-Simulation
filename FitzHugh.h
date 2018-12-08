#pragma once
#include <vector>
#include <random>

using namespace std;


class FitzHugh
{
public:
	FitzHugh();
	~FitzHugh();
	//----------------------------------------------------------------------
	//Getters
	const double &getX() { return _x; }; const
	const double &getDX() { return _dx; }; const
	const double &getY() { return _y; }; const
	const double &getDY() { return _dy; }; const
	const double &getA() { return _a; }; const
	const double &getB() { return _b; }; const
	const double &getTau() { return _tau; }; const
	const double &getStepSize() { return _stepSize; }; const
	const vector<double> &getInputs() { return _inputs; }; const

	//----------------------------------------------------------------------
	//Setters
	double setX(const double &x) { _x = x; }
	double setDX(const double &dx) { _dx = dx; }
	double setY(const double &y) { _y = y; }
	double setDY(const double &dy) { _y = dy; }
	double setA(const double &a) { _a = a; }
	double setB(const double &b) { _b = b; }
	double setTau(const double &tau) { _tau = tau; }
	double setStepSize(const double &stepSize) { _stepSize = stepSize; }
	double setInputs(const vector<double> &inputs) { _inputs = inputs; }

	//----------------------------------------------------------------------
	//Euler integration
	void calcSlope();
	void eulerStep();

	//----------------------------------------------------------------------
	//Random generator 
	double randomReal(const double lowerBoundary, const double upperBoundary);
	int randomInt(const int lowerBoundary, const int upperBoundary);
	static random_device seed_generator;
	static unsigned seed;
	static mt19937 mersenne_generator;
	//----------------------------------------------------------------------

private:
	double _x;
	double _dx;
	double _y;
	double _dy;
	double _a;
	double _b;
	double _tau;
	double _stepSize = 0.001;
	vector<double> _inputs;
};

