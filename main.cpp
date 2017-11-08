#include <iostream>

#include "GraphicHandler.h"
#include "Simulation.h"


using namespace std;

int main()
{
	cout << "Creating simulation...\n";
	Simulation simulation;
	cout << "Creating graphichandler...\n";
	GraphicHandler graphicHandler(simulation.getLandscape().getHeightMaxMin());

	cout << "Running simulation...\n";
	while (true)
	{
		graphicHandler.printWorld(simulation.getLandscape().getTiles());
		graphicHandler.printEntities(simulation.getOrganisms());
		graphicHandler.getEvents(simulation.getLandscape().getTiles());
	}

}