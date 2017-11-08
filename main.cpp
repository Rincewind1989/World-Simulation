#include <iostream>

#include "GraphicHandler.h"
#include "Landscape.h"


using namespace std;

int main()
{
	cout << "Creating graphichandler...\n";
	GraphicHandler graphicHandler;
	cout << "Creating landscape...\n";
	Landscape landscape;
	cout << "Running simulation...\n";

	while (true)
	{
		graphicHandler.printGame(landscape.getTiles());
		graphicHandler.getEvents();
	}

}