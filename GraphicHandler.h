#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
#include "SimulationData.h"

using namespace std;

class GraphicHandler
{
public:
	GraphicHandler();
	~GraphicHandler();


	//Prints the game
	void printGame(
		vector<vector<Tile>> &tiles);


	//Grabs the events on both windows
	void getEvents();

private:

	//Columns and rows for graphics
	int m_x = SIMULATION_X;
	int m_y = SIMULATION_Y;
	int m_height = WINDOW_HEIGHT;
	int m_width = WINDOW_WIDTH;

	//The Font of the text
	sf::Font m_font;

	//Color for clearing screen
	sf::Color m_color = sf::Color(100,100,100);

	//The Windows for the neural network and the game
	sf::RenderWindow m_gameWindow;

	//The textures need for drawing
	sf::Texture m_grassTexture;
	sf::Texture m_waterTexture;

	//Sprite variable to draw to the window
	sf::Sprite m_grassSprite;
	sf::Sprite m_waterSprite;

	//Camera viewer position
	double m_zPosition = 100.0;
	int m_xPosition = WINDOW_WIDTH / 2.0;
	int m_yPosition = WINDOW_HEIGHT / 2.0;

};

