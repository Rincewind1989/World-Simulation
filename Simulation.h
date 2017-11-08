#pragma once

#include <vector>
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

private:
	Landscape m_landscape;
	vector<Organism> m_organisms;
};

