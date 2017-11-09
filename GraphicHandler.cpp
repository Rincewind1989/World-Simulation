#include "GraphicHandler.h"

#include <iostream>
#include <math.h>
#include <iterator>

GraphicHandler::GraphicHandler(
	vector<double> heightMaxMin)
{
	//Parameter settings
	m_heightMax = heightMaxMin[0];
	m_heightMin = heightMaxMin[1];

	//Sets the window size and title
	m_gameWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simulation");
	m_informationWindow.create(sf::VideoMode(WINDOW_INFORMATION_WIDTH, WINDOW_INFORMATION_HEIGHT), "Information");

	//Clear the information screen
	m_informationWindow.clear(m_color);
	m_informationWindow.display();

	//Load all the textures
	m_grassTexture.loadFromFile("Textures/grass.jpg");
	m_waterTexture.loadFromFile("Textures/water.jpg");
	m_snowTexture.loadFromFile("Textures/snow.jpg");
	m_stoneTexture.loadFromFile("Textures/stone.jpg");

	//Draws the textures in sprites that are later usable
	//Grass
	m_grassSprite.setTexture(m_grassTexture);
	m_grassSprite.setScale(sf::Vector2f(1.0 * 100 / m_zPosition / (m_grassTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / m_zPosition / (m_grassTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));


	//Water
	m_waterSprite.setTexture(m_waterTexture); 
	m_waterSprite.setScale(sf::Vector2f(1.0 * 100 / m_zPosition / (m_waterTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / m_zPosition / (m_waterTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));


	//Snow
	m_snowSprite.setTexture(m_snowTexture);
	m_snowSprite.setScale(sf::Vector2f(1.0 * 100 / m_zPosition / (m_snowTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / m_zPosition / (m_snowTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));


	//Stone
	m_stoneSprite.setTexture(m_stoneTexture);
	m_stoneSprite.setScale(sf::Vector2f(1.0 * 100 / m_zPosition / (m_stoneTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / m_zPosition / (m_stoneTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));

	//Loads the font from a file
	sf::Font font;
	if (!font.loadFromFile("Mermaid1001.ttf"))
	{
		perror("Font file couldnt be loaded.");
	}
	m_font = font;
}


GraphicHandler::~GraphicHandler()
{
}


//Prints the game entites to the window
void GraphicHandler::printWorld(
	vector<vector<Tile>> &tiles)
{
	//Clear the screen
	m_gameWindow.clear(m_color);

	//Draws the tiles
	//The x and yPosition are sprite positions in the window
	int xPosition = 0;
	int yPosition = 0;

	//Sets the loop intervall for x and y based on the z-axes and the position of the camera
	int y;
	int x;

	//This if clause calculates the loop interval for y (which tiles are visible with the momentarily camera settings)
	if ((int)((m_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y - m_zPosition / (2.0 * 100.0) * (float)SIMULATION_Y) < 0)
	{
		y = 0;
		yPosition = abs((int)((m_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y - m_zPosition / (2.0 * 100.0) * (float)SIMULATION_Y));
	}
	else
	{
		y = (int)((m_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y - m_zPosition / (2.0 * 100.0) * (float)SIMULATION_Y);
		yPosition = 0;
	}

	//Loop for the y-tile-axis
	for (y; y < ((int)((m_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y + m_zPosition / (2.0 * 100.0) * (float)SIMULATION_Y)) && y < SIMULATION_Y; y++)
	{

		//This if clause calculates the loop interval for x (which tiles are visible with the momentarily camera settings)
		if ((int)((m_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X - m_zPosition / (2.0 * 100.0) * (float)SIMULATION_X) < 0)
		{
			x = 0;
			xPosition = abs((int)((m_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X - (m_zPosition / (2.0 * 100.0)) * (float)SIMULATION_X));
		}
		else
		{
			xPosition = 0;
			x = (int)((m_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X - (m_zPosition / (2.0 * 100.0)) * (float)SIMULATION_X);
		}

		//Loop for the x-tile-axis
		for (x; x < ((int)((m_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X + (m_zPosition / (2.0 * 100.0)) * (float)SIMULATION_X)) && x < SIMULATION_X; x++)
		{
			if (tiles[y][x].getHeight() <= m_heightMax * WATER_LEVEL)
			{
				m_waterSprite.setPosition(xPosition * m_WidnowWidth / m_Simulationx * 100 / m_zPosition, yPosition * m_WindowHeight / m_Simulationy * 100 / m_zPosition);
				m_waterSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs(tiles[y][x].getHeight()))) * 255));
				m_gameWindow.draw(m_waterSprite);
			}
			if (tiles[y][x].getHeight() > m_heightMax * WATER_LEVEL && tiles[y][x].getHeight() < m_heightMax * GRASS_LEVEL)
			{
				m_grassSprite.setPosition(xPosition * m_WidnowWidth / m_Simulationx * 100 / m_zPosition, yPosition * m_WindowHeight / m_Simulationy * 100 / m_zPosition);
				m_grassSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs(tiles[y][x].getHeight())) ) * 255));
				m_gameWindow.draw(m_grassSprite);
			}

			if (tiles[y][x].getHeight() > m_heightMax * GRASS_LEVEL && tiles[y][x].getHeight() < m_heightMax * STONE_LEVEL)
			{
				m_stoneSprite.setPosition(xPosition * m_WidnowWidth / m_Simulationx * 100 / m_zPosition, yPosition * m_WindowHeight / m_Simulationy * 100 / m_zPosition);
				m_stoneSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs(tiles[y][x].getHeight()))) * 255));
				m_gameWindow.draw(m_stoneSprite);
			}
			if (tiles[y][x].getHeight() > m_heightMax * STONE_LEVEL)
			{
				m_snowSprite.setPosition(xPosition * m_WidnowWidth / m_Simulationx * 100 / m_zPosition, yPosition * m_WindowHeight / m_Simulationy * 100 / m_zPosition);
				m_snowSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs(tiles[y][x].getHeight()))) * 255));
				m_gameWindow.draw(m_snowSprite);
			}
			xPosition++;
		}
		yPosition++;
	}
}


//Prints the entities of the game
void GraphicHandler::printEntities(
	vector<Organism> &organisms)
{
	//The x and yPosition are entity positions in the window
	int xPosition = 0;
	int yPosition = 0;

	//Shape for the organism
	sf::CircleShape tmpShape(100.0 / m_zPosition * 1.0);

	//loops through all organism and checks if they are visible
	for (vector<Organism>::iterator it = organisms.begin(); it != organisms.end(); ++it)
	{
		if (it->getPositionX() < (m_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X - (m_zPosition / (2.0 * 100.0)) * (float)SIMULATION_X 
			|| it->getPositionX() > (m_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X + (m_zPosition / (2.0 * 100.0)) * (float)SIMULATION_X 
			|| it->getPositionY() < (m_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y - (m_zPosition / (2.0 * 100.0)) * (float)SIMULATION_Y
			|| it->getPositionY() > (m_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y + (m_zPosition / (2.0 * 100.0)) * (float)SIMULATION_Y)
		{
			continue;
		}

		else
		{
			//resizes proportional to the size of the organism
			tmpShape.setRadius(100.0 / m_zPosition * it->getSize());
			sf::Color color(it->getRed(), it->getGreen(), it->getBlue(), it->getAlpha());
			tmpShape.setFillColor(color);
			//calculates the xPosition for the entity on the screen
			xPosition = (int)((m_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X - m_zPosition / (2.0 * 100.0) * (float)SIMULATION_X);
			//calculates the yPosition for the entity on the screen
			yPosition = (int)((m_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y - m_zPosition / (2.0 * 100.0) * (float)SIMULATION_Y);				
			tmpShape.setPosition((it->getPositionX() - xPosition) * m_WidnowWidth / m_Simulationx * 100 / m_zPosition, (it->getPositionY() - yPosition) * m_WindowHeight / m_Simulationy * 100 / m_zPosition);

			m_gameWindow.draw(tmpShape);
		}
	}

	m_gameWindow.display();
}


//Grabs the events on both windows
void GraphicHandler::getEvents(
	vector<vector<Tile>> &tiles,
	vector<Organism> &organisms)
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
			if (m_zPosition > CAMERA_Z_DISTANCE)
			{
				m_zPosition = CAMERA_Z_DISTANCE;
			}
			if (m_zPosition < 10)
			{
				m_zPosition = 10;
			}

			//Rescales the sprites to the new distance view
			m_grassSprite.setScale(sf::Vector2f(1.0 * 100 / m_zPosition / (m_grassTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / m_zPosition / (m_grassTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));
			m_waterSprite.setScale(sf::Vector2f(1.0 * 100 / m_zPosition / (m_waterTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / m_zPosition / (m_waterTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));
			m_stoneSprite.setScale(sf::Vector2f(1.0 * 100 / m_zPosition / (m_stoneTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / m_zPosition / (m_stoneTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));
			m_snowSprite.setScale(sf::Vector2f(1.0 * 100 / m_zPosition / (m_snowTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / m_zPosition / (m_snowTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));

		}

		//Arrow keys controle position on map
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Right)
			{
				m_xPosition -= WINDOW_WIDTH / 15.0;
				if (m_xPosition < 0)
				{
					m_xPosition = 0;
				}
			}
			if (event.key.code == sf::Keyboard::Left)
			{
				m_xPosition += WINDOW_WIDTH / 15.0;
				if (m_xPosition > WINDOW_WIDTH)
				{
					m_xPosition = WINDOW_WIDTH;
				}
			}
			if (event.key.code == sf::Keyboard::Up)
			{
				m_yPosition += WINDOW_HEIGHT / 15.0;
				if (m_yPosition > WINDOW_HEIGHT)
				{
					m_yPosition = WINDOW_HEIGHT;
				}
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				m_yPosition -= WINDOW_HEIGHT / 15.0;

				if (m_yPosition < 0)
				{
					m_yPosition = 0;
				}
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//Define importan variables
			sf::Vector2f pos;
			string string;

			//Clear the information screen
			m_informationWindow.clear(m_color);

			// left mouse button is pressed: get information from the tile the mouse is hovering above
			sf::Text text;
			text.setFont(m_font);
			text.setCharacterSize(16);
			text.setFillColor(sf::Color::Black);
			text.setOutlineColor(sf::Color::Black);

			//Rescales the sprites to the new distance view
			m_grassSprite.setScale(sf::Vector2f(INFORMATION_WINDOW_SPRITE_SIZE, INFORMATION_WINDOW_SPRITE_SIZE));
			m_waterSprite.setScale(sf::Vector2f(INFORMATION_WINDOW_SPRITE_SIZE, INFORMATION_WINDOW_SPRITE_SIZE));
			m_stoneSprite.setScale(sf::Vector2f(INFORMATION_WINDOW_SPRITE_SIZE, INFORMATION_WINDOW_SPRITE_SIZE));
			m_snowSprite.setScale(sf::Vector2f(INFORMATION_WINDOW_SPRITE_SIZE, INFORMATION_WINDOW_SPRITE_SIZE));


			//Draw the selected tile in the information window
			if (tiles[getMousePositionY()][getMousePositionX()].getHeight() <= m_heightMax * WATER_LEVEL)
			{
				m_waterSprite.setPosition(0, 0);
				m_waterSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs(tiles[getMousePositionY()][getMousePositionX()].getHeight()))) * 255));
				m_informationWindow.draw(m_waterSprite);
			}
			if (tiles[getMousePositionY()][getMousePositionX()].getHeight() > m_heightMax * WATER_LEVEL && tiles[getMousePositionY()][getMousePositionX()].getHeight() < m_heightMax * GRASS_LEVEL)
			{
				m_grassSprite.setPosition(0, 0);
				m_grassSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs(tiles[getMousePositionY()][getMousePositionX()].getHeight()))) * 255));
				m_informationWindow.draw(m_grassSprite);
			}

			if (tiles[getMousePositionY()][getMousePositionX()].getHeight() > m_heightMax * GRASS_LEVEL && tiles[getMousePositionY()][getMousePositionX()].getHeight() < m_heightMax * STONE_LEVEL)
			{
				m_stoneSprite.setPosition(0, 0);
				m_stoneSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs(tiles[getMousePositionY()][getMousePositionX()].getHeight()))) * 255));
				m_informationWindow.draw(m_stoneSprite);
			}
			if (tiles[getMousePositionY()][getMousePositionX()].getHeight() > m_heightMax * STONE_LEVEL)
			{
				m_snowSprite.setPosition(0, 0);
				m_snowSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs(tiles[getMousePositionY()][getMousePositionX()].getHeight()))) * 255));
				m_informationWindow.draw(m_snowSprite);
			}

			//Add the different information lines for the tile
			string = "Position X: " + to_string(getMousePositionX()) + "\tPosition Y: " + to_string(getMousePositionY());
			text.setString(string);
			pos = sf::Vector2f(0.0, INFORMATION_WINDOW_SPRITE_SIZE * m_grassSprite.getTextureRect().height);
			text.setPosition(pos);
			m_informationWindow.draw(text);

			string = "Height: " + to_string(tiles[getMousePositionY()][getMousePositionX()].getHeight());
			text.setString(string);
			pos = sf::Vector2f(0.0, text.getCharacterSize() + INFORMATION_WINDOW_SPRITE_SIZE * m_grassSprite.getTextureRect().height);
			text.setPosition(pos);
			m_informationWindow.draw(text);

			string = "Temperature: " + to_string(tiles[getMousePositionY()][getMousePositionX()].getTemperature());
			text.setString(string);
			pos = sf::Vector2f(0.0, 2.0 * text.getCharacterSize() + INFORMATION_WINDOW_SPRITE_SIZE * m_grassSprite.getTextureRect().height);
			text.setPosition(pos);
			m_informationWindow.draw(text);

			string =  "Food: " + to_string(tiles[getMousePositionY()][getMousePositionX()].getFood());
			text.setString(string);
			pos = sf::Vector2f(0.0, 3.0 * text.getCharacterSize() + INFORMATION_WINDOW_SPRITE_SIZE * m_grassSprite.getTextureRect().height);
			text.setPosition(pos);
			m_informationWindow.draw(text);

			//Also get information of the nearest organism
			if (organisms.size() > 0)
			{
				Organism* nearstOrganism = &organisms[0];
				for (vector<Organism>::iterator it = organisms.begin(); it != organisms.end(); ++it)
				{
					if (fabs(it->getPositionX() - getMousePositionX())*fabs(it->getPositionX() - getMousePositionX()) + fabs(it->getPositionY() - getMousePositionY())*fabs(it->getPositionY() - getMousePositionY())
						< fabs(nearstOrganism->getPositionX() - getMousePositionX())*fabs(nearstOrganism->getPositionX() - getMousePositionX()) + fabs(nearstOrganism->getPositionY() - getMousePositionY())*fabs(nearstOrganism->getPositionY() - getMousePositionY()))
					{
						nearstOrganism = &(*it);
					}
				}

				//Shape for the organism
				sf::CircleShape tmpShape(100.0 / m_zPosition * 1.0);

				//resizes proportional to the size of the organism
				tmpShape.setRadius(10.0 * nearstOrganism->getSize());
				tmpShape.setPosition(0.0, WINDOW_INFORMATION_HEIGHT / 2.0);
				sf::Color color(nearstOrganism->getRed(), nearstOrganism->getGreen(), nearstOrganism->getBlue(), nearstOrganism->getAlpha());
				tmpShape.setFillColor(color);
				m_informationWindow.draw(tmpShape);

				//Add the different information lines for the entity
				string = "Organism on PositionX: " + to_string(nearstOrganism->getPositionX()) + "\tY: " + to_string(nearstOrganism->getPositionY());
				text.setString(string);
				pos = sf::Vector2f(0.0, WINDOW_INFORMATION_HEIGHT / 2.0 + 2.0 * 10.0 * nearstOrganism->getSize());
				text.setPosition(pos);
				m_informationWindow.draw(text);

				string = "Energy: " + to_string(nearstOrganism->getEnergy());
				text.setString(string);
				pos = sf::Vector2f(0.0, WINDOW_INFORMATION_HEIGHT / 2.0 + text.getCharacterSize() + 2.0 * 10.0 * nearstOrganism->getSize());
				text.setPosition(pos);
				m_informationWindow.draw(text);

				string = "Temperature: " + to_string(nearstOrganism->getTemperature());
				text.setString(string);
				pos = sf::Vector2f(0.0, WINDOW_INFORMATION_HEIGHT / 2.0 + 2.0 * text.getCharacterSize() + 2.0 * 10.0 * nearstOrganism->getSize());
				text.setPosition(pos);
				m_informationWindow.draw(text);

			}
			m_informationWindow.display();

			//Rescales the sprites to the distance view back
			m_grassSprite.setScale(sf::Vector2f(1.0 * 100 / m_zPosition / (m_grassTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / m_zPosition / (m_grassTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));
			m_waterSprite.setScale(sf::Vector2f(1.0 * 100 / m_zPosition / (m_waterTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / m_zPosition / (m_waterTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));
			m_stoneSprite.setScale(sf::Vector2f(1.0 * 100 / m_zPosition / (m_stoneTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / m_zPosition / (m_stoneTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));
			m_snowSprite.setScale(sf::Vector2f(1.0 * 100 / m_zPosition / (m_snowTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / m_zPosition / (m_snowTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));

		}

		//Gets the mouse positon and updates it
		m_mousePositionX = sf::Mouse::getPosition(m_gameWindow).x;
		m_mousePositionY = sf::Mouse::getPosition(m_gameWindow).y;

	}
}


//Returns the x position of the tile the mouse is hovering above
int GraphicHandler::getMousePositionX()
{
	int xPosition = 0;
	xPosition = (int)((m_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X - (m_zPosition / (2.0 * 100.0)) * (float)SIMULATION_X);
	int intervall = abs(xPosition - (int)((m_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X + (m_zPosition / (2.0 * 100.0)) * (float)SIMULATION_X));
	int returnValue = xPosition + (int)(intervall * ((float)m_mousePositionX / (float)WINDOW_WIDTH));
	if (xPosition + (int)(intervall * ((float)m_mousePositionX / (float)WINDOW_WIDTH)) < 0)
	{
		returnValue = 0;
	}
	if (xPosition + (int)(intervall * ((float)m_mousePositionX / (float)WINDOW_WIDTH)) > SIMULATION_X)
	{
		returnValue = SIMULATION_X - 1;
	}
	return returnValue;
}


//Returns the y position of the tile the mouse is hovering above
int GraphicHandler::getMousePositionY()
{
	int yPosition = 0;
	yPosition = (int)((m_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y - m_zPosition / (2.0 * 100.0) * (float)SIMULATION_Y);
	int intervall = abs(yPosition - (int)((m_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y + (m_zPosition / (2.0 * 100.0)) * (float)SIMULATION_Y));
	int returnValue = yPosition + (int)(intervall * ((float)m_mousePositionY / (float)WINDOW_HEIGHT));
	if (yPosition + (int)(intervall * ((float)m_mousePositionY / (float)WINDOW_HEIGHT)) < 0)
	{
		returnValue = 0;
	}
	if (yPosition + (int)(intervall * ((float)m_mousePositionY / (float)WINDOW_HEIGHT)) > SIMULATION_Y)
	{
		returnValue = SIMULATION_Y - 1;
	}
	return returnValue;
}