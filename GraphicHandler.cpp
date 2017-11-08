#include "GraphicHandler.h"

#include <iostream>

GraphicHandler::GraphicHandler()
{
	//Sets the window size and title
	m_gameWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simulation");

	//Load all the textures
	m_grassTexture.loadFromFile("Textures/grass.jpg");
	m_waterTexture.loadFromFile("Textures/water.jpg");

	//Draws the textures in sprites that are later usable
	m_grassSprite.setTexture(m_grassTexture);
	m_grassSprite.setScale(sf::Vector2f(1.0 / (m_grassTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 / (m_grassTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));

	m_waterSprite.setTexture(m_waterTexture);
	m_waterSprite.setScale(sf::Vector2f(1.0 / (m_waterTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 / (m_waterTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));

	//Loads the font from a file
	sf::Font font;
	if (!font.loadFromFile("CurlyLou.ttf"))
	{
		perror("Font file couldnt be loaded.");
	}
	m_font = font;
}


GraphicHandler::~GraphicHandler()
{
}


//Prints the game entites to the window
void GraphicHandler::printGame(
	vector<vector<Tile>> &tiles)
{
	//Clear the screen
	m_gameWindow.clear(m_color);

	//Draws the tiles
	for (unsigned int y = m_yPosition / WINDOW_HEIGHT * tiles.size(); y < tiles.size() * m_zPosition / 100; y++)
	{
		for (unsigned int x = m_xPosition / WINDOW_WIDTH * tiles[0].size(); x < tiles[0].size() * m_zPosition / 100; x++)
		{
			if (tiles[y][x].getHeight() > -0.1)
			{
				m_grassSprite.setPosition(x * m_width / m_x * 100 / m_zPosition, y * m_height / m_y * 100 / m_zPosition);
				m_grassSprite.setColor(sf::Color(255, 255, 255, (2 * fabs(tiles[y][x].getHeight() + 0.1) ) * 255));
				m_gameWindow.draw(m_grassSprite);
			}
			else
			{
				m_waterSprite.setPosition(x * m_width / m_x * 100 / m_zPosition, y * m_height / m_y * 100 / m_zPosition);
				m_waterSprite.setColor(sf::Color(255, 255, 255, (2 * fabs(tiles[y][x].getHeight())) * 255));
				m_gameWindow.draw(m_waterSprite);
			}

		}
	}
	m_gameWindow.display();
}


//Grabs the events on both windows
void GraphicHandler::getEvents()
{
	sf::Event event;
	while (m_gameWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			m_gameWindow.close();
		}

		//Mouse wheel event regulates the distance to the map
		if (event.type == sf::Event::MouseWheelMoved)
		{
			m_zPosition -= event.mouseWheel.delta;
			if (m_zPosition > 100)
			{
				m_zPosition = 100;
			}
			if (m_zPosition < 10)
			{
				m_zPosition = 10;
			}

			//Rescales the sprites to the new distance view
			m_grassSprite.setScale(sf::Vector2f(1.0 * 100 / m_zPosition / (m_grassTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / m_zPosition / (m_grassTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));
			m_waterSprite.setScale(sf::Vector2f(1.0 * 100 / m_zPosition / (m_waterTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / m_zPosition / (m_waterTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));

		}

		//Arrow keys controle position on map
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Left)
			{
				m_xPosition -= 10;
				if (m_xPosition < 0)
				{
					m_xPosition = 0;
				}
				cout << m_xPosition << endl;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				m_xPosition += 10;
				if (m_xPosition > WINDOW_WIDTH)
				{
					m_xPosition = WINDOW_WIDTH;
				}
				cout << m_xPosition << endl;
			}
			if (event.key.code == sf::Keyboard::Up)
			{
				m_yPosition += 10;
				if (m_yPosition < 0)
				{
					m_yPosition = 0;
				}
				cout << m_yPosition << endl;
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				m_yPosition -= 10;
				if (m_yPosition > WINDOW_HEIGHT)
				{
					m_yPosition = WINDOW_HEIGHT;
				}
				cout << m_yPosition << endl;
			}
		}
	}
}