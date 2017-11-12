#include <iostream>

#include "GraphicHandler.h"
#include "Simulation.h"


using namespace std;

int main()
{
	cout << "Creating simulation...\n";
	Simulation simulation;
	cout << "Creating graphichandler...\n";
	GraphicHandler graphicHandler(simulation);

	cout << "Running simulation...\n";
	while (true)
	{
		
		//Update Simulation
		simulation.deltaTime();
		simulation.updateSimulation();

		//Update Graphics
		graphicHandler.clear();
		graphicHandler.printWorld();
		graphicHandler.printEntities();
		graphicHandler.printInformation();
		graphicHandler.display();
		graphicHandler.getEvents();

	}

}