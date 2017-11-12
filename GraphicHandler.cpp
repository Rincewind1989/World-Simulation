#include "GraphicHandler.h"

#include <iostream>
#include <math.h>
#include <iterator>

GraphicHandler::GraphicHandler(
	Simulation &simulation)
{
	//Set the simulation pointer for the graphic handler
	_simulation = &simulation;

	//Parameter settings
	_heightMax = _simulation->getLandscape().getHeightMaxMin()[0];
	_heightMin = _simulation->getLandscape().getHeightMaxMin()[1];

	//Sets the window size and title
	_gameWindow.create(sf::VideoMode(WINDOW_WIDTH + WINDOW_INFORMATION_WIDTH, WINDOW_HEIGHT), "Simulation");

	//Load all the textures
	_grassTexture.loadFromFile("Textures/grass.jpg");
	_waterTexture.loadFromFile("Textures/water.jpg");
	_snowTexture.loadFromFile("Textures/snow.jpg");
	_stoneTexture.loadFromFile("Textures/stone.jpg");

	//Draws the textures in sprites that are later usable
	//Grass
	_grassSprite.setTexture(_grassTexture);
	_grassSprite.setScale(sf::Vector2f(1.0 * 100 / _zPosition / (_grassTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / _zPosition / (_grassTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));


	//Water
	_waterSprite.setTexture(_waterTexture); 
	_waterSprite.setScale(sf::Vector2f(1.0 * 100 / _zPosition / (_waterTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / _zPosition / (_waterTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));


	//Snow
	_snowSprite.setTexture(_snowTexture);
	_snowSprite.setScale(sf::Vector2f(1.0 * 100 / _zPosition / (_snowTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / _zPosition / (_snowTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));


	//Stone
	_stoneSprite.setTexture(_stoneTexture);
	_stoneSprite.setScale(sf::Vector2f(1.0 * 100 / _zPosition / (_stoneTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / _zPosition / (_stoneTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));

	//The sprite for the information window
	_tileSprite.setScale(sf::Vector2f(INFORMATION_WINDOW_SPRITE_SIZE, INFORMATION_WINDOW_SPRITE_SIZE));

	//Loads the font from a file
	sf::Font font;
	if (!font.loadFromFile("Mermaid1001.ttf"))
	{
		perror("Font file couldnt be loaded.");
	}
	_font = font;

}


GraphicHandler::~GraphicHandler()
{
}


//Prints the game entites to the window
void GraphicHandler::printWorld()
{
	//Gets a reference to the tiles
	vector<vector<Tile>> *tiles = &_simulation->getLandscape().getTiles();

	//Draws the tiles
	//The x and yPosition are sprite positions in the window
	int xPosition = 0;
	int yPosition = 0;

	//Sets the loop intervall for x and y based on the z-axes and the position of the camera
	int y;
	int x;

	//This if clause calculates the loop interval for y (which tiles are visible with the momentarily camera settings)
	if ((int)((_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y - _zPosition / (2.0 * 100.0) * (float)SIMULATION_Y) < 0)
	{
		y = 0;
		yPosition = abs((int)((_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y - _zPosition / (2.0 * 100.0) * (float)SIMULATION_Y));
	}
	else
	{
		y = (int)((_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y - _zPosition / (2.0 * 100.0) * (float)SIMULATION_Y);
		yPosition = 0;
	}

	//Loop for the y-tile-axis
	for (y; y < ((int)((_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y + _zPosition / (2.0 * 100.0) * (float)SIMULATION_Y)) && y < SIMULATION_Y; y++)
	{

		//This if clause calculates the loop interval for x (which tiles are visible with the momentarily camera settings)
		if ((int)((_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X - _zPosition / (2.0 * 100.0) * (float)SIMULATION_X) < 0)
		{
			x = 0;
			xPosition = abs((int)((_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X - (_zPosition / (2.0 * 100.0)) * (float)SIMULATION_X));
		}
		else
		{
			xPosition = 0;
			x = (int)((_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X - (_zPosition / (2.0 * 100.0)) * (float)SIMULATION_X);
		}

		//Loop for the x-tile-axis
		for (x; x < ((int)((_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X + (_zPosition / (2.0 * 100.0)) * (float)SIMULATION_X)) && x < SIMULATION_X; x++)
		{
			if ((*tiles)[y][x].getHeight() <= _heightMax * WATER_LEVEL)
			{
				_waterSprite.setPosition(xPosition * _WidnowWidth / _Simulationx * 100 / _zPosition, yPosition * _WindowHeight / _Simulationy * 100 / _zPosition);
				_waterSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs((*tiles)[y][x].getHeight()) / HEIGHT_MULITPLICATOR)) * 255));
				_gameWindow.draw(_waterSprite);
			}
			if ((*tiles)[y][x].getHeight() > _heightMax * WATER_LEVEL && (*tiles)[y][x].getHeight() < _heightMax * GRASS_LEVEL)
			{
				_grassSprite.setPosition(xPosition * _WidnowWidth / _Simulationx * 100 / _zPosition, yPosition * _WindowHeight / _Simulationy * 100 / _zPosition);
				_grassSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs((*tiles)[y][x].getHeight()) / HEIGHT_MULITPLICATOR) ) * 255));
				_gameWindow.draw(_grassSprite);
			}

			if ((*tiles)[y][x].getHeight() > _heightMax * GRASS_LEVEL && (*tiles)[y][x].getHeight() < _heightMax * STONE_LEVEL)
			{
				_stoneSprite.setPosition(xPosition * _WidnowWidth / _Simulationx * 100 / _zPosition, yPosition * _WindowHeight / _Simulationy * 100 / _zPosition);
				_stoneSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs((*tiles)[y][x].getHeight()) / HEIGHT_MULITPLICATOR)) * 255));
				_gameWindow.draw(_stoneSprite);
			}
			if ((*tiles)[y][x].getHeight() > _heightMax * STONE_LEVEL)
			{
				_snowSprite.setPosition(xPosition * _WidnowWidth / _Simulationx * 100 / _zPosition, yPosition * _WindowHeight / _Simulationy * 100 / _zPosition);
				_snowSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs((*tiles)[y][x].getHeight()) / HEIGHT_MULITPLICATOR)) * 255));
				_gameWindow.draw(_snowSprite);
			}
			xPosition++;
		}
		yPosition++;
	}
}


//Prints the entities of the game
void GraphicHandler::printEntities()
{
	//Get the reference to the organism
	vector<Organism>* organisms = &_simulation->getOrganisms();

	//The x and yPosition are entity positions in the window
	int xPosition = 0;
	int yPosition = 0;

	//Shape for the organism
	sf::CircleShape tmpShape(100.0 / _zPosition * 1.0);

	//loops through all organism and checks if they are visible
	for (vector<Organism>::iterator it = (*organisms).begin(); it != (*organisms).end(); ++it)
	{
		if (it->getPositionX() < (_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X - (_zPosition / (2.0 * 100.0)) * (float)SIMULATION_X 
			|| it->getPositionX() > (_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X + (_zPosition / (2.0 * 100.0)) * (float)SIMULATION_X 
			|| it->getPositionY() < (_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y - (_zPosition / (2.0 * 100.0)) * (float)SIMULATION_Y
			|| it->getPositionY() > (_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y + (_zPosition / (2.0 * 100.0)) * (float)SIMULATION_Y)
		{
			continue;
		}

		else
		{
			//resizes proportional to the size of the organism
			tmpShape.setRadius(100.0 / _zPosition * it->getSize());
			sf::Color color(it->getRed(), it->getGreen(), it->getBlue(), it->getAlpha());
			tmpShape.setFillColor(color);
			//calculates the xPosition for the entity on the screen
			xPosition = (int)((_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X - _zPosition / (2.0 * 100.0) * (float)SIMULATION_X);
			//calculates the yPosition for the entity on the screen
			yPosition = (int)((_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y - _zPosition / (2.0 * 100.0) * (float)SIMULATION_Y);				
			tmpShape.setPosition((it->getPositionX() - xPosition) * _WidnowWidth / _Simulationx * 100 / _zPosition, (it->getPositionY() - yPosition) * _WindowHeight / _Simulationy * 100 / _zPosition);

			_gameWindow.draw(tmpShape);
		}
	}
}


//Print information window
void GraphicHandler::printInformation()
{
	//Define importan variables
	sf::Vector2f pos;
	string string;

	// left mouse button is pressed: get information from the tile the mouse is hovering above
	sf::Text text;
	text.setFont(_font);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::Black);

	//Draw the selected tile in the information window	
	_gameWindow.draw(_tileSprite);

	//Add the different information lines for the tile
	string = "Position X: " + to_string(_tilePositionX) + "\tPosition Y: " + to_string(_tilePositionY);
	text.setString(string);
	pos = sf::Vector2f(WINDOW_WIDTH, INFORMATION_WINDOW_SPRITE_SIZE * _tileSprite.getTextureRect().height);
	text.setPosition(pos);
	_gameWindow.draw(text);

	string = "Height: " + to_string(_tileP->getHeight());
	text.setString(string);
	pos = sf::Vector2f(WINDOW_WIDTH, text.getCharacterSize() + INFORMATION_WINDOW_SPRITE_SIZE * _grassSprite.getTextureRect().height);
	text.setPosition(pos);
	_gameWindow.draw(text);

	string = "Temperature: " + to_string(_tileP->getTemperature());
	text.setString(string);
	pos = sf::Vector2f(WINDOW_WIDTH, 2.0 * text.getCharacterSize() + INFORMATION_WINDOW_SPRITE_SIZE * _grassSprite.getTextureRect().height);
	text.setPosition(pos);
	_gameWindow.draw(text);

	string = "Food: " + to_string(_tileP->getFood());
	text.setString(string);
	pos = sf::Vector2f(WINDOW_WIDTH, 3.0 * text.getCharacterSize() + INFORMATION_WINDOW_SPRITE_SIZE * _grassSprite.getTextureRect().height);
	text.setPosition(pos);
	_gameWindow.draw(text);

	//Shape for the organism
	sf::CircleShape tmpShape(100.0 / _zPosition * 1.0);

	if (_nearestOrganism != NULL)
	{
		//resizes proportional to the size of the organism
		tmpShape.setRadius(10.0 * _nearestOrganism->getSize());
		tmpShape.setPosition(WINDOW_WIDTH, WINDOW_INFORMATION_HEIGHT / 2.0);
		sf::Color color(_nearestOrganism->getRed(), _nearestOrganism->getGreen(), _nearestOrganism->getBlue(), _nearestOrganism->getAlpha());
		tmpShape.setFillColor(color);
		_gameWindow.draw(tmpShape);

		//Add the different information lines for the entity
		string = "Highest Fitness so far: " + to_string(_simulation->getHighestFitness());
		text.setString(string);
		pos = sf::Vector2f(WINDOW_WIDTH, WINDOW_INFORMATION_HEIGHT / 2.0 + 2.0 * 10.0 * _nearestOrganism->getSize());
		text.setPosition(pos);
		_gameWindow.draw(text);

		string = "Organism on PositionX: " + to_string(_nearestOrganism->getPositionX()) + "\tY: " + to_string(_nearestOrganism->getPositionY());
		text.setString(string);
		pos = sf::Vector2f(WINDOW_WIDTH, WINDOW_INFORMATION_HEIGHT / 2.0 + text.getCharacterSize() + 2.0 * 10.0 * _nearestOrganism->getSize());
		text.setPosition(pos);
		_gameWindow.draw(text);

		string = "Energy: " + to_string(_nearestOrganism->getEnergy());
		text.setString(string);
		pos = sf::Vector2f(WINDOW_WIDTH, WINDOW_INFORMATION_HEIGHT / 2.0 + 2.0 *text.getCharacterSize() + 2.0 * 10.0 * _nearestOrganism->getSize());
		text.setPosition(pos);
		_gameWindow.draw(text);

		string = "Temperature: " + to_string(_nearestOrganism->getTemperature());
		text.setString(string);
		pos = sf::Vector2f(WINDOW_WIDTH, WINDOW_INFORMATION_HEIGHT / 2.0 + 3.0 * text.getCharacterSize() + 2.0 * 10.0 * _nearestOrganism->getSize());
		text.setPosition(pos);
		_gameWindow.draw(text);

		string = "Fitness: " + to_string(_nearestOrganism->getFitness());
		text.setString(string);
		pos = sf::Vector2f(WINDOW_WIDTH, WINDOW_INFORMATION_HEIGHT / 2.0 + 4.0 * text.getCharacterSize() + 2.0 * 10.0 * _nearestOrganism->getSize());
		text.setPosition(pos);
		_gameWindow.draw(text);

		//Draw the neural network
		//Draw the input nodes
		for (int i = 0; i < INPUT_NEURONS; i++)
		{
			tmpShape.setRadius(RADIUS_NEURON);
			tmpShape.setPosition(WINDOW_WIDTH + WINDOW_INFORMATION_WIDTH / 20.0, WINDOW_INFORMATION_HEIGHT + i*2.5*RADIUS_NEURON);
			sf::Color color(0,0,0,255);
			tmpShape.setFillColor(color);
			_gameWindow.draw(tmpShape);
		}

		//Draw the hidden nodes
		for (int hiddenLayers = 0; hiddenLayers < NUM_LAYERS - 2; hiddenLayers++)
		{
			for (int i = 0; i < HIDDEN_NEURONS; i++)
			{
				tmpShape.setRadius(RADIUS_NEURON);
				tmpShape.setPosition(WINDOW_WIDTH + WINDOW_INFORMATION_WIDTH / 20.0 + (hiddenLayers + 1) * 5.0 * RADIUS_NEURON, WINDOW_INFORMATION_HEIGHT + i*2.5*RADIUS_NEURON);
				sf::Color color(0, 0, 0, 255);
				tmpShape.setFillColor(color);
				_gameWindow.draw(tmpShape);
			}
		}		

		//Draw the output nodes
		for (int i = 0; i < OUTPUT_NEURONS; i++)
		{
			tmpShape.setRadius(RADIUS_NEURON);
			tmpShape.setPosition(WINDOW_WIDTH + WINDOW_INFORMATION_WIDTH / 20.0 + 10.0 * RADIUS_NEURON, WINDOW_INFORMATION_HEIGHT + i*2.5*RADIUS_NEURON);
			sf::Color color(0, 0, 0, 255);
			tmpShape.setFillColor(color);
			_gameWindow.draw(tmpShape);
		}
	}
}


//Clear the display
void GraphicHandler::clear()
{
	_gameWindow.clear(_color);
}


//Draws the display
void GraphicHandler::display()
{
	_gameWindow.display();
}


//Grabs the events on both windows
void GraphicHandler::getEvents()
{
	//Get reference to the tiles and organisms
	vector<vector<Tile>>* tiles = &_simulation->getLandscape().getTiles();
	vector<Organism>* organisms = &_simulation->getOrganisms();

	sf::Event event;
	while (_gameWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			_gameWindow.close();
		}

		//Mouse wheel event regulates the distance to the map
		if (event.type == sf::Event::MouseWheelMoved)
		{
			_zPosition -= event.mouseWheel.delta;
			if (_zPosition > CAMERA_Z_DISTANCE)
			{
				_zPosition = CAMERA_Z_DISTANCE;
			}
			if (_zPosition < 10)
			{
				_zPosition = 10;
			}

			//Rescales the sprites to the new distance view
			_grassSprite.setScale(sf::Vector2f(1.0 * 100 / _zPosition / (_grassTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / _zPosition / (_grassTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));
			_waterSprite.setScale(sf::Vector2f(1.0 * 100 / _zPosition / (_waterTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / _zPosition / (_waterTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));
			_stoneSprite.setScale(sf::Vector2f(1.0 * 100 / _zPosition / (_stoneTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / _zPosition / (_stoneTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));
			_snowSprite.setScale(sf::Vector2f(1.0 * 100 / _zPosition / (_snowTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 1.0 * 100 / _zPosition / (_snowTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));

		}

		//Arrow keys controle position on map
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Right)
			{
				_xPosition -= WINDOW_WIDTH / 15.0;
				if (_xPosition < 0)
				{
					_xPosition = 0;
				}
			}
			if (event.key.code == sf::Keyboard::Left)
			{
				_xPosition += WINDOW_WIDTH / 15.0;
				if (_xPosition > WINDOW_WIDTH)
				{
					_xPosition = WINDOW_WIDTH;
				}
			}
			if (event.key.code == sf::Keyboard::Up)
			{
				_yPosition += WINDOW_HEIGHT / 15.0;
				if (_yPosition > WINDOW_HEIGHT)
				{
					_yPosition = WINDOW_HEIGHT;
				}
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				_yPosition -= WINDOW_HEIGHT / 15.0;

				if (_yPosition < 0)
				{
					_yPosition = 0;
				}
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//Gets the mouse positon and updates it
			_mousePositionX = sf::Mouse::getPosition(_gameWindow).x;
			_mousePositionY = sf::Mouse::getPosition(_gameWindow).y;

			if (getMousePositionX() < SIMULATION_X && getMousePositionX() > 0 && getMousePositionY() > 0 && getMousePositionY() < SIMULATION_Y)
			//Save the objects that were selected
			if ((*tiles)[getMousePositionY()][getMousePositionX()].getHeight() <= _heightMax * WATER_LEVEL)
			{
				_tileSprite.setTexture(_waterTexture);
				_tileSprite.setPosition(WINDOW_WIDTH, 0);
				_tileSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs((*tiles)[getMousePositionY()][getMousePositionX()].getHeight()))) * 255));
			}
			if ((*tiles)[getMousePositionY()][getMousePositionX()].getHeight() > _heightMax * WATER_LEVEL && (*tiles)[getMousePositionY()][getMousePositionX()].getHeight() < _heightMax * GRASS_LEVEL)
			{
				_tileSprite.setTexture(_grassTexture);
				_tileSprite.setPosition(WINDOW_WIDTH, 0);
				_tileSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs((*tiles)[getMousePositionY()][getMousePositionX()].getHeight()))) * 255));
			}

			if ((*tiles)[getMousePositionY()][getMousePositionX()].getHeight() > _heightMax * GRASS_LEVEL && (*tiles)[getMousePositionY()][getMousePositionX()].getHeight() < _heightMax * STONE_LEVEL)
			{
				_tileSprite.setTexture(_stoneTexture);
				_tileSprite.setPosition(WINDOW_WIDTH, 0);
				_tileSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs((*tiles)[getMousePositionY()][getMousePositionX()].getHeight()))) * 255));
			}
			if ((*tiles)[getMousePositionY()][getMousePositionX()].getHeight() > _heightMax * STONE_LEVEL)
			{
				_tileSprite.setTexture(_snowTexture);
				_tileSprite.setPosition(WINDOW_WIDTH, 0);
				_tileSprite.setColor(sf::Color(255, 255, 255, (sqrt(fabs((*tiles)[getMousePositionY()][getMousePositionX()].getHeight()))) * 255));
			}

			_tileP = &(*tiles)[getMousePositionY()][getMousePositionX()];
			_tilePositionX = getMousePositionX();
			_tilePositionY = getMousePositionY();

			if ((*organisms).size() > 0)
			{
				Organism* nearstOrganism = &(*organisms)[0];
				for (vector<Organism>::iterator it = (*organisms).begin(); it != (*organisms).end(); ++it)
				{
					if (fabs(it->getPositionX() - getMousePositionX())*fabs(it->getPositionX() - getMousePositionX()) + fabs(it->getPositionY() - getMousePositionY())*fabs(it->getPositionY() - getMousePositionY())
						< fabs(nearstOrganism->getPositionX() - getMousePositionX())*fabs(nearstOrganism->getPositionX() - getMousePositionX()) + fabs(nearstOrganism->getPositionY() - getMousePositionY())*fabs(nearstOrganism->getPositionY() - getMousePositionY()))
					{
						nearstOrganism = &(*it);
					}
				}
				_nearestOrganism = nearstOrganism;
			}
			else
			{
				_nearestOrganism = NULL;
			}
		}
	}
}


//Returns the x position of the tile the mouse is hovering above
int GraphicHandler::getMousePositionX()
{
	int xPosition = 0;
	xPosition = (int)((_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X - (_zPosition / (2.0 * 100.0)) * (float)SIMULATION_X);
	int intervall = abs(xPosition - (int)((_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X + (_zPosition / (2.0 * 100.0)) * (float)SIMULATION_X));
	int returnValue = xPosition + (int)(intervall * ((float)_mousePositionX / (float)WINDOW_WIDTH));
	if (xPosition + (int)(intervall * ((float)_mousePositionX / (float)WINDOW_WIDTH)) < 0)
	{
		returnValue = 0;
	}
	if (xPosition + (int)(intervall * ((float)_mousePositionX / (float)WINDOW_WIDTH)) > SIMULATION_X)
	{
		returnValue = SIMULATION_X - 1;
	}
	return returnValue;
}


//Returns the y position of the tile the mouse is hovering above
int GraphicHandler::getMousePositionY()
{
	int yPosition = 0;
	yPosition = (int)((_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y - _zPosition / (2.0 * 100.0) * (float)SIMULATION_Y);
	int intervall = abs(yPosition - (int)((_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y + (_zPosition / (2.0 * 100.0)) * (float)SIMULATION_Y));
	int returnValue = yPosition + (int)(intervall * ((float)_mousePositionY / (float)WINDOW_HEIGHT));
	if (yPosition + (int)(intervall * ((float)_mousePositionY / (float)WINDOW_HEIGHT)) < 0)
	{
		returnValue = 0;
	}
	if (yPosition + (int)(intervall * ((float)_mousePositionY / (float)WINDOW_HEIGHT)) > SIMULATION_Y)
	{
		returnValue = SIMULATION_Y - 1;
	}
	return returnValue;
}