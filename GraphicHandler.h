#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Simulation.h"
#include "Tile.h"
#include "Organism.h"
#include "SimulationData.h"

using namespace std;

class GraphicHandler
{
public:
	GraphicHandler(Simulation &simulation);
	~GraphicHandler();
	//----------------------------------------------------------------------
	//Prints the game
	void printWorld();
	//----------------------------------------------------------------------
	//Prints the entities of the game
	void printEntities();
	//----------------------------------------------------------------------
	//Print information window
	void printInformation();
	//----------------------------------------------------------------------
	//Prints a text at a certain location in the information window
	void printText(string text, double x, double y);
	//----------------------------------------------------------------------
	//Print neural network
	void printNeuralNetwork();
	//----------------------------------------------------------------------
	//Prints a layer of the neural network
	void printLayer(int numNodes, double x, double y);
	//----------------------------------------------------------------------
	//Prints the edges between two layers
	void printEdges();
	//----------------------------------------------------------------------
	//Clear the display
	void clear();
	//----------------------------------------------------------------------
	//Draws the display
	void display();
	//----------------------------------------------------------------------
	//Grabs the events on both windows
	void getEvents();
	//----------------------------------------------------------------------
	//Returns the x position of the mouse
	int GraphicHandler::getMousePositionX();
	//----------------------------------------------------------------------
	//Returns the y position of the mouse
	int GraphicHandler::getMousePositionY();
private:
	//Columns and rows for graphics
	int _Simulationx = SIMULATION_X;
	int _Simulationy = SIMULATION_Y;
	int _WindowHeight = WINDOW_HEIGHT;
	int _WidnowWidth = WINDOW_WIDTH;
	//----------------------------------------------------------------------
	//The Font of the text
	sf::Font _font;
	//----------------------------------------------------------------------
	//Color for clearing screen
	sf::Color _color = sf::Color(100,100,100);
	//----------------------------------------------------------------------
	//The Windows for the neural network and the game
	sf::RenderWindow _gameWindow;
	//----------------------------------------------------------------------
	//Pointer to the simulation
	Simulation* _simulation;
	//----------------------------------------------------------------------
	//Saved objects that are printed on the information screen
	Tile* _tileP = new Tile;
	sf::Sprite _tileSprite;
	double _tilePositionX;
	double _tilePositionY;
	double _fitness;
	double _highestFitness;
	//----------------------------------------------------------------------
	//The textures need for drawing
	sf::Texture _grassTexture;
	sf::Texture _waterTexture;
	sf::Texture _snowTexture;
	sf::Texture _stoneTexture;
	//----------------------------------------------------------------------
	//Sprite variable to draw to the window
	sf::Sprite _grassSprite;
	sf::Sprite _waterSprite;
	sf::Sprite _snowSprite;
	sf::Sprite _stoneSprite;
	//----------------------------------------------------------------------
	//Camera viewer position
	double _zPosition = CAMERA_Z_DISTANCE;
	int _xPosition = WINDOW_WIDTH / 2.0;
	int _yPosition = WINDOW_HEIGHT / 2.0;
	//----------------------------------------------------------------------
	//Height map properties
	double _heightMax;
	double _heightMin;
	//----------------------------------------------------------------------
	//Mouse properties
	double _mousePositionX;
	double _mousePositionY;
	//----------------------------------------------------------------------
	//Lines for neural network drawing
	sf::Vertex** _lines;

};

