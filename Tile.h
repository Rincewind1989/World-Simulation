#pragma once

using namespace std;

class Tile
{
public:
	Tile();
	~Tile();
	//----------------------------------------------------------------------
	//Setters/Getters
	void setHeight(double height);
	double &getHeight();
	//----------------------------------------------------------------------
	void setTemperature(double temperature);
	void addTemperature(double Temperature);
	double &getTemperature();
	void setOrignTemperature(double Temperature);
	double &getOrignTemperature();
	//----------------------------------------------------------------------
	void setFood(double food);
	void addFood(double food);
	double &getFood();

private:
	double _height = 0.0;
	double _temperature = 25.0;
	double _originalTemperature = 25.0;
	double _food = 0.0;
};

