#pragma once

#include <string>

using namespace std;

class Tile
{
public:
	Tile();
	~Tile();

	//Setters/Getters
	void setHeight(double height);
	double getHeight();

	void setTemperature(double temperature);
	void addTemperature(double deltaTemperature);
	double getTemperature();

	void setGroundTextureString(string groundTextureString);
	string getGroundTextureString();

private:
	double m_height = 0.0;
	double m_temperature = 25.0;
	string m_groundTextureString;
};

