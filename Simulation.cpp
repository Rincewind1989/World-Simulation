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


//Updates all organisms by time
void Simulation::updateOrganisms()
{
	updateHeatEnergy();

}


//Update the energy of all organisms based on body properties and enviromnent
void Simulation::updateHeatEnergy()
{
	double energy;
	double deltaTimeDouble = deltaTime();
	double temperature;
	vector<Organism>::iterator it = m_organisms.begin();
	while (it != m_organisms.end())
	{
		energy = -1 * deltaTimeDouble * it->getHeatEnergyProduction() * ENERGY_CONSUMPTION_FACTOR;
		temperature = deltaTimeDouble * it->getHeatEnergyProduction() - deltaTimeDouble * HEAT_LOSS_FACTOR * (it->getTemperature() - m_landscape.getTiles()[(int)it->getPositionY()][(int)it->getPositionX()].getTemperature());
		it->addEnergy(energy);
		it->addTemperature(temperature);
		if (it->getEnergy() <= 0.0 || it->getTemperature() <= 20.0)
		{
			it = m_organisms.erase(it);
		}
		else ++it;
	}
}


double Simulation::deltaTime()
{
	const sf::Time delta = m_clock.restart();
	return (delta.asSeconds());
}