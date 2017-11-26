#include "Tile.h"



Tile::Tile()
{
}


Tile::~Tile()
{
}


//Sets the height of the tile
void Tile::setHeight(double height)
{
	_height = height;
}


//Returns the height of the tile by index
double &Tile::getHeight()
{
	return _height;
}


//Sets the temperature of the tile
void Tile::setTemperature(
	double temperature)
{
	_temperature = temperature;
}


//Adds the float value to the temperature of the tile
void Tile::addTemperature(
	double Temperature)
{
	_temperature += Temperature;
}


//Returns the temperature of the tile
double &Tile::getTemperature()
{
	return _temperature;
}


void Tile::setOrignTemperature(
	double Temperature)
{
	_originalTemperature = Temperature;
}

double &Tile::getOrignTemperature()
{
	return _originalTemperature;
}


//Sets the food value for this tile
void Tile::setFood(
	double food)
{
	_food = food;
	if (_food < 0.0)
	{
		_food = 0.0;
	}
}


//Adds a food value to this tile
void Tile::addFood(
	double food)
{
	_food += food;
	if (_food < 0.0)
	{
		_food = 0.0;
	}
}


//Returns the food value of this tile
double &Tile::getFood()
{
	return _food;
}