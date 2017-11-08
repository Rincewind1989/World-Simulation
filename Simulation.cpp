#include "Simulation.h"



Simulation::Simulation()
{
	for (int i = 0; i < STARTING_NUMBER_ORGANISM; i++)
	{
		Organism tmp;
		m_organisms.push_back(tmp);
	}

}


Simulation::~Simulation()
{
}


//Getters/Setters
Landscape &Simulation::getLandscape()
{
	return m_landscape;
}


Organism &Simulation::getOrganismByIndex(int index)
{
	return m_organisms[index];
}


vector<Organism> &Simulation::getOrganisms()
{
	return m_organisms;
}
