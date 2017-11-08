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
	m_height = height;
}


//Returns the height of the tile by index
double Tile::getHeight()
{
	return m_height;
}


//Sets the temperature of the tile
void Tile::setTemperature(
	double temperature)
{
	m_temperature = temperature;
}


//Adds the float value to the temperature of the tile
void Tile::addTemperature(
	double Temperature)
{
	m_temperature += Temperature;
}


//Returns the temperature of the tile
double Tile::getTemperature()
{
	return m_temperature;
}