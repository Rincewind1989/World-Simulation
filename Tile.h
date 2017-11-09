#pragma once

#include <string>

using namespace std;

class Tile
{
public:
	Tile();
	~Tile();

	//Setters/Getters
	void setHeight(
		double height);

	double getHeight();

	void setTemperature(
		double temperature);

	void addTemperature(
		double Temperature);

	double getTemperature();

	void setFood(
		double food);

	void addFood(
		double food);

	double getFood();

private:
	double m_height = 0.0;
	double m_temperature = 25.0;
	double m_food = 0.0;
};

