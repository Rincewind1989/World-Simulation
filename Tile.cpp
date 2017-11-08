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
void Tile::setTemperature(double temperature)
{
	m_temperature = temperature;
}


//Adds the float value to the temperature of the tile
void Tile::addTemperature(double deltaTemperature)
{
	m_temperature += deltaTemperature;
}


//Returns the temperature of the tile
double Tile::getTemperature()
{
	return m_temperature;
}


//Sets the string of the ground texture for this tile
void Tile::setGroundTextureString(string groundTextureString)
{
	m_groundTextureString = groundTextureString;
}


//Returns the ground texture string of this tile
string Tile::getGroundTextureString()
{
	return m_groundTextureString;
}
