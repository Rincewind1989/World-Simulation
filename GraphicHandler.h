#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
#include "Organism.h"
#include "SimulationData.h"

using namespace std;

class GraphicHandler
{
public:
	GraphicHandler(
		vector<double> heightMaxMin);
	~GraphicHandler();

	//Prints the game
	void printWorld(
		vector<vector<Tile>> &tiles);

	//Prints the entities of the game
	void printEntities(
		vector<Organism> &organisms);

	//Grabs the events on both windows
	void getEvents(
		vector<vector<Tile>> &tiles,
		vector<Organism> &organisms);

	//Returns the x position of the mouse
	int GraphicHandler::getMousePositionX();

	//Returns the y position of the mouse
	int GraphicHandler::getMousePositionY();

private:

	//Columns and rows for graphics
	int m_Simulationx = SIMULATION_X;
	int m_Simulationy = SIMULATION_Y;
	int m_WindowHeight = WINDOW_HEIGHT;
	int m_WidnowWidth = WINDOW_WIDTH;

	//The Font of the text
	sf::Font m_font;

	//Color for clearing screen
	sf::Color m_color = sf::Color(100,100,100);

	//The Windows for the neural network and the game
	sf::RenderWindow m_gameWindow;
	sf::RenderWindow m_informationWindow;

	//The textures need for drawing
	sf::Texture m_grassTexture;
	sf::Texture m_waterTexture;
	sf::Texture m_snowTexture;
	sf::Texture m_stoneTexture;

	//Sprite variable to draw to the window
	sf::Sprite m_grassSprite;
	sf::Sprite m_waterSprite;
	sf::Sprite m_snowSprite;
	sf::Sprite m_stoneSprite;

	//Camera viewer position
	double m_zPosition = CAMERA_Z_DISTANCE;
	int m_xPosition = WINDOW_WIDTH / 2.0;
	int m_yPosition = WINDOW_HEIGHT / 2.0;

	//Height map properties
	double m_heightMax;
	double m_heightMin;

	//Mouse properties
	double m_mousePositionX;
	double m_mousePositionY;

};

