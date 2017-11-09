#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Landscape.h"
#include "Organism.h"

using namespace std;

class Simulation
{
public:
	Simulation();
	~Simulation();

	//Getters/Setters
	Landscape &getLandscape();

	Organism &getOrganismByIndex(int index);

	vector<Organism> &getOrganisms();

	double deltaTime();

	//Updates all organisms by time
	void updateOrganisms();

	//Update the energy of all organisms
	void updateHeatEnergy();

private:
	Landscape m_landscape;
	vector<Organism> m_organisms;
	sf::Clock m_clock;
};

