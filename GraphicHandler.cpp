#include "GraphicHandler.h"

#include <math.h>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))

GraphicHandler::GraphicHandler(Simulation &simulation)
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

	//Calculates the vertecies for the neural network lines
	int edges = 0;
	edges = INPUT_NEURONS * HIDDEN_NEURONS + (NUM_LAYERS - 3) * HIDDEN_NEURONS * HIDDEN_NEURONS + HIDDEN_NEURONS * OUTPUT_NEURONS;
	if (NUM_LAYERS == 2)
		edges = INPUT_NEURONS * OUTPUT_NEURONS;

	_lines = new sf::Vertex*[edges];
	for (int i = 0; i < edges; i++)
		_lines[i] = new sf::Vertex[2];

	if (NUM_LAYERS == 2)
	{
		for (int i = 0; i < INPUT_NEURONS; i++)
		{
			for (int j = 0; j < OUTPUT_NEURONS; j++)
			{
				_lines[i + j * INPUT_NEURONS][0] = sf::Vertex(sf::Vector2f(WINDOW_WIDTH + (i + 1.5) * DISTANCE_INPUT_NEURON_FACTOR * RADIUS_NEURON,
					WINDOW_INFORMATION_HEIGHT + RADIUS_NEURON));
				_lines[i + j * INPUT_NEURONS][1] = sf::Vertex(sf::Vector2f(WINDOW_WIDTH + (j + 0.5) * DISTANCE_OUTPUT_NEURON_FACTOR * RADIUS_NEURON,
					WINDOW_INFORMATION_HEIGHT + DISTANCE_Y_NEURON_FACTOR * RADIUS_NEURON + RADIUS_NEURON));
			}
		}
	}

	else
	{
		for (int i = 0; i < INPUT_NEURONS; i++)
		{
			for (int j = 0; j < HIDDEN_NEURONS; j++)
			{
				_lines[i + j * INPUT_NEURONS][0] = sf::Vertex(sf::Vector2f(WINDOW_WIDTH + (i + 1.5) * DISTANCE_INPUT_NEURON_FACTOR * RADIUS_NEURON,
					WINDOW_INFORMATION_HEIGHT + RADIUS_NEURON));
				_lines[i + j * INPUT_NEURONS][1] = sf::Vertex(sf::Vector2f(WINDOW_WIDTH + (j + 0.5) * DISTANCE_HIDDEN_NEURON_FACTOR * RADIUS_NEURON,
					WINDOW_INFORMATION_HEIGHT + DISTANCE_Y_NEURON_FACTOR * RADIUS_NEURON + RADIUS_NEURON));
			}
		}

		for (int numLayer = 0; numLayer < NUM_LAYERS - 3; numLayer++)
		{
			for (int i = 0; i < HIDDEN_NEURONS; i++)
			{
				for (int j = 0; j < HIDDEN_NEURONS; j++)
				{
					_lines[INPUT_NEURONS * HIDDEN_NEURONS + numLayer * HIDDEN_NEURONS * HIDDEN_NEURONS + i + j * HIDDEN_NEURONS][0] = sf::Vertex(sf::Vector2f(WINDOW_WIDTH + (i + 0.5) * DISTANCE_HIDDEN_NEURON_FACTOR * RADIUS_NEURON,
						WINDOW_INFORMATION_HEIGHT + (numLayer + 1) * DISTANCE_Y_NEURON_FACTOR * RADIUS_NEURON + RADIUS_NEURON));
					_lines[INPUT_NEURONS * HIDDEN_NEURONS + numLayer * HIDDEN_NEURONS * HIDDEN_NEURONS + i + j * HIDDEN_NEURONS][1] = sf::Vertex(sf::Vector2f(WINDOW_WIDTH + (j + 0.5) * DISTANCE_HIDDEN_NEURON_FACTOR * RADIUS_NEURON,
						WINDOW_INFORMATION_HEIGHT + (numLayer + 2) * DISTANCE_Y_NEURON_FACTOR * RADIUS_NEURON + RADIUS_NEURON));
				}
			}
		}

		for (int i = 0; i < HIDDEN_NEURONS; i++)
		{
			for (int j = 0; j < OUTPUT_NEURONS; j++)
			{
				_lines[INPUT_NEURONS * HIDDEN_NEURONS + (NUM_LAYERS - 3) * HIDDEN_NEURONS * HIDDEN_NEURONS + i + j * HIDDEN_NEURONS][0] = sf::Vertex(sf::Vector2f(WINDOW_WIDTH + (i + 0.5) * DISTANCE_HIDDEN_NEURON_FACTOR * RADIUS_NEURON,
					WINDOW_INFORMATION_HEIGHT + (NUM_LAYERS - 2) * DISTANCE_Y_NEURON_FACTOR * RADIUS_NEURON + RADIUS_NEURON));
				_lines[INPUT_NEURONS * HIDDEN_NEURONS + (NUM_LAYERS - 3) * HIDDEN_NEURONS * HIDDEN_NEURONS + i + j * HIDDEN_NEURONS][1] = sf::Vertex(sf::Vector2f(WINDOW_WIDTH + (j + 0.5) * DISTANCE_OUTPUT_NEURON_FACTOR * RADIUS_NEURON,
					WINDOW_INFORMATION_HEIGHT + (NUM_LAYERS - 1) * DISTANCE_Y_NEURON_FACTOR * RADIUS_NEURON + RADIUS_NEURON));
			}
		}
	}
	
}

GraphicHandler::~GraphicHandler()
{
}

//----------------------------------------------------------------------

//Prints the game entites to the window
void GraphicHandler::printWorld()
{
	//Gets a reference to the tiles
	vector<vector<Tile>> *tiles = &_simulation->getLandscape().getTiles();

	//Draws the tiles
	//The x and yPosition are sprite positions in the window
	int xPosition = 0;
	int yPosition = 0;

	//Sets the loop intervall for x and y based on the distance and the position of the camera
	int y;
	int x;

	int yPositionBool = (int)((_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y - _zPosition / (2.0 * 100) * (float)SIMULATION_Y);
	int xPositionBool = (int)((_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X - _zPosition / (2.0 * 100) * (float)SIMULATION_X);

	int yPositionLoop = ((int)((_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y + _zPosition / (2.0 * 100) * (float)SIMULATION_Y));
	int xPositionLoop = ((int)((_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X + (_zPosition / (2.0 * 100)) * (float)SIMULATION_X));

	//This if clause calculates the loop interval for y (which tiles are visible with the momentarily camera settings)
	if (yPositionBool < 0)
	{
		y = 0;
		yPosition = abs(yPositionBool);
	}
	else
	{
		y = yPositionBool;
		yPosition = 0;
	}

	//Loop for the y-tile-axis
	for (y; y < yPositionLoop  && y < SIMULATION_Y; y++)
	{

		//This if clause calculates the loop interval for x (which tiles are visible with the momentarily camera settings)
		if (xPositionBool < 0)
		{
			x = 0;
			xPosition = abs(xPositionBool);
		}
		else
		{
			xPosition = 0;
			x = xPositionBool;
		}

		//Loop for the x-tile-axis
		for (x; x < xPositionLoop && x < SIMULATION_X; x++)
		{
			if ((*tiles)[y][x].getHeight() <= _heightMax * WATER_LEVEL)
			{
				_waterSprite.setPosition(xPosition * _WidnowWidth / _Simulationx * 100 / _zPosition, yPosition * _WindowHeight / _Simulationy * 100 / _zPosition);
				_waterSprite.setColor(sf::Color(255, 255, 255, 80 + (*tiles)[y][x].getFood() / MAX_FOOD_ON_TILE * 175)); //(sqrt(fabs((*tiles)[y][x].getHeight()) / HEIGHT_MULITPLICATOR)) * 255)
				_gameWindow.draw(_waterSprite);
			}
			if ((*tiles)[y][x].getHeight() > _heightMax * WATER_LEVEL && (*tiles)[y][x].getHeight() < _heightMax * GRASS_LEVEL)
			{
				_grassSprite.setPosition(xPosition * _WidnowWidth / _Simulationx * 100 / _zPosition, yPosition * _WindowHeight / _Simulationy * 100 / _zPosition);
				_grassSprite.setColor(sf::Color(255, 255, 255, 80 + (*tiles)[y][x].getFood() / MAX_FOOD_ON_TILE * 175)); //(sqrt(fabs((*tiles)[y][x].getHeight()) / HEIGHT_MULITPLICATOR) ) * 255)
				_gameWindow.draw(_grassSprite);
			}

			if ((*tiles)[y][x].getHeight() > _heightMax * GRASS_LEVEL && (*tiles)[y][x].getHeight() < _heightMax * STONE_LEVEL)
			{
				_stoneSprite.setPosition(xPosition * _WidnowWidth / _Simulationx * 100 / _zPosition, yPosition * _WindowHeight / _Simulationy * 100 / _zPosition);
				_stoneSprite.setColor(sf::Color(255, 255, 255, 80 + (*tiles)[y][x].getFood() / MAX_FOOD_ON_TILE * 175)); // (sqrt(fabs((*tiles)[y][x].getHeight()) / HEIGHT_MULITPLICATOR)) * 255)
				_gameWindow.draw(_stoneSprite);
			}
			if ((*tiles)[y][x].getHeight() > _heightMax * STONE_LEVEL)
			{
				_snowSprite.setPosition(xPosition * _WidnowWidth / _Simulationx * 100 / _zPosition, yPosition * _WindowHeight / _Simulationy * 100 / _zPosition);
				_snowSprite.setColor(sf::Color(255, 255, 255, 80 + (*tiles)[y][x].getFood() / MAX_FOOD_ON_TILE * 175)); // (sqrt(fabs((*tiles)[y][x].getHeight()) / HEIGHT_MULITPLICATOR)) * 255)
				_gameWindow.draw(_snowSprite);
			}
			xPosition++;
		}
		yPosition++;
	}
}

//----------------------------------------------------------------------

//Prints the entities of the game
void GraphicHandler::printEntities()
{
	//Get the reference to the organism
	vector<Organism>* organisms = &_simulation->getOrganisms();

	//The x and yPosition are entity positions in the window
	int xPosition = 0;
	int yPosition = 0;

	//Shape for the organism
	sf::CircleShape tmpShape(100 / _zPosition * 1.0);

	//loops through all organism and checks if they are visible
	for (vector<Organism>::iterator it = (*organisms).begin(); it != (*organisms).end(); ++it)
	{
		tmpShape.setOutlineThickness(0.0);
		if (it->getPositionX() < (_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X - (_zPosition / (2.0 * 100)) * (float)SIMULATION_X
			|| it->getPositionX() > (_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X + (_zPosition / (2.0 * 100)) * (float)SIMULATION_X
			|| it->getPositionY() < (_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y - (_zPosition / (2.0 * 100)) * (float)SIMULATION_Y
			|| it->getPositionY() > (_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y + (_zPosition / (2.0 * 100)) * (float)SIMULATION_Y)
		{
			continue;
		}

		else
		{
			//resizes proportional to the size of the organism
			tmpShape.setRadius(100.0 / _zPosition * WINDOW_WIDTH / SIMULATION_X / 2.0 * it->getSize());
			sf::Color color(it->getRed(), it->getGreen(), it->getBlue(), it->getAlpha());
			if (it->getWasHit())
			{
				color.r = 255;
				color.g = 0;
				color.b = 0;
				color.a = 255;
			}	
			if (&(*it) == &(*_simulation->getInformationOrganism()))
			{
				sf::Color outlineColor(0, 0, 0);
				tmpShape.setOutlineColor(outlineColor);
				tmpShape.setOutlineThickness(2.0);
			}
			tmpShape.setFillColor(color);
			//calculates the xPosition for the entity on the screen
			xPosition = (int)((_xPosition / (float)WINDOW_WIDTH) * (float)SIMULATION_X - _zPosition / (2.0 * 100) * (float)SIMULATION_X);
			//calculates the yPosition for the entity on the screen
			yPosition = (int)((_yPosition / (float)WINDOW_HEIGHT) * (float)SIMULATION_Y - _zPosition / (2.0 * 100) * (float)SIMULATION_Y);
			tmpShape.setPosition((it->getPositionX() - xPosition) * _WidnowWidth / _Simulationx * 100 / _zPosition, (it->getPositionY() - yPosition) * _WindowHeight / _Simulationy * 100 / _zPosition);

			//Draw line for the rotation of the organism
			sf::RectangleShape line(sf::Vector2f(5, 100.0 / _zPosition * WINDOW_WIDTH / SIMULATION_X / 2.0 * it->getSize()));
			line.setPosition((it->getPositionX() - xPosition) * _WidnowWidth / _Simulationx * 100 / _zPosition + tmpShape.getRadius() - 2.5, (it->getPositionY() - yPosition) * _WindowHeight / _Simulationy * 100 / _zPosition + tmpShape.getRadius() - 2.5);
			color.r = 0;
			color.g = 0;
			color.b = 0;
			color.a = 255;
			line.setFillColor(color);
			line.setRotation(it->getRotation() * 180.0/3.14159 - 90.0);

			_gameWindow.draw(tmpShape);
			_gameWindow.draw(line);
		}
	}
}

//----------------------------------------------------------------------

//Print information window
void GraphicHandler::printInformation()
{
	//Textarray to be printed
	ostringstream str;
	str << setprecision(3) << _tileP->getHeight();
	_informationString[0] = str.str();

	str.str("");
	str.clear();
	str << setprecision(3) << _tileP->getTemperature();
	_informationString[1] = str.str();

	str.str("");
	str.clear();
	str << setprecision(4) << _tileP->getFood();
	_informationString[2] = str.str();

	str.str("");
	str.clear();
	str << setprecision(5) << _simulation->getOrganisms().size();
	_informationString[3] = str.str();

	str.str("");
	str.clear();
	str << setprecision(8) << _simulation->getHighestFitness();
	_informationString[4] = str.str();

	str.str("");
	str.clear();
	str << setprecision(6) << _simulation->getAvgFitness();
	_informationString[5] = str.str();

	str.str("");
	str.clear();
	str << setprecision(4) << _simulation->getAvgSize();
	_informationString[6] = str.str();

	str.str("");
	str.clear();
	str << setprecision(4) << _simulation->getSmallSize();
	_informationString[7] = str.str();

	str.str("");
	str.clear();
	str << setprecision(4) << _simulation->getBiggestSize();
	_informationString[8] = str.str();

	str.str("");
	str.clear();
	str << setprecision(3) << float(DEATH_BY_TEMP) / float(DEATHS) * 100;
	_informationString[9] = str.str();

	str.str("");
	str.clear();
	str << setprecision(3) << float(DEATH_BY_ENERGY) / float(DEATHS) * 100;
	_informationString[10] = str.str();

	str.str("");
	str.clear();
	str << setprecision(3) << float(DEATH_BY_AGE) / float(DEATHS) * 100;
	_informationString[11] = str.str();

	str.str("");
	str.clear();
	str << setprecision(3) << _simulation->getAvgAge();
	_informationString[22] = str.str();

	str.str("");
	str.clear();
	str << setprecision(3) << _simulation->getHighestAge();
	_informationString[23] = str.str();

	string informationText[] = { "Position X: " + to_string(_tilePositionX) + "\tPosition Y: " + to_string(_tilePositionY) ,
		"Height: " + _informationString[0],
		"Temperature: " + _informationString[1],
		"Food: " + _informationString[2],
		"\n",
		"Number organisms: " + _informationString[3],
		"Highest Fitness so far: " + _informationString[4],
		"Avg. Fitness: " + _informationString[5],
		"Avg. Size/Smallest Size/Biggest Size: " + _informationString[6] + "/" + _informationString[7] + "/" + _informationString[8],
		"Avg. Age/Highest Age: " + _informationString[22] + "/" + _informationString[23],
		"Death by Temperature in %: " + _informationString[9],
		"Death by Energy loss in %: " + _informationString[10],
		"Death by Age in %: " + _informationString[11],
		"World-Seed: " + to_string(SEED)
	};

	//Draw the selected tile in the information window	
	_gameWindow.draw(_tileSprite);

	//Add the different information lines for the tile
	for (int i = 0; i < sizeof(informationText) / sizeof(informationText[0]); i++)
	{
		printText(informationText[i], WINDOW_WIDTH, i * INFORMATION_TEXT_SIZE + INFORMATION_WINDOW_SPRITE_SIZE * _tileSprite.getTextureRect().height);
	}

	//Shape for the organism
	sf::CircleShape tmpShape(100.0 / _zPosition * 1.0);

	if (_simulation->getInformationOrganism() != NULL)
	{

		str.str("");
		str.clear();
		str << setprecision(4) << _simulation->getInformationOrganism()->getPositionX();
		_informationString[12] = str.str();

		str.str("");
		str.clear();
		str << setprecision(4) << _simulation->getInformationOrganism()->getPositionY();
		_informationString[13] = str.str();

		str.str("");
		str.clear();
		str << setprecision(4) << _simulation->getInformationOrganism()->getAge();
		_informationString[14] = str.str();

		str.str("");
		str.clear();
		str << setprecision(5) << _simulation->getInformationOrganism()->getEnergy();
		_informationString[15] = str.str();

		str.str("");
		str.clear();
		str << setprecision(3) << _simulation->getInformationOrganism()->getEnergy() / _simulation->getInformationOrganism()->getMaxEnergy() * 100;
		_informationString[16] = str.str();

		str.str("");
		str.clear();
		str << setprecision(4) << _simulation->getInformationOrganism()->getTemperature();
		_informationString[17] = str.str();

		str.str("");
		str.clear();
		str << setprecision(4) << _simulation->getInformationOrganism()->getHeatLossFactor();
		_informationString[18] = str.str();

		str.str("");
		str.clear();
		str << setprecision(4) << _simulation->getInformationOrganism()->getHeatEnergyProduction();
		_informationString[19] = str.str();

		str.str("");
		str.clear();
		str << setprecision(6) << _simulation->getInformationOrganism()->getFitness();
		_informationString[20] = str.str();

		str.str("");
		str.clear();
		str << setprecision(3) << _simulation->getInformationOrganism()->getSize();
		_informationString[21] = str.str();

		str.str("");
		str.clear();
		str << setprecision(3) << _simulation->getInformationOrganism()->getGeneration();
		_informationString[22] = str.str();

		//Textarray to be printed
		string informationText2[] = { "\n", 
			"Organism on PositionX: " + _informationString[12] + "\tY: " + _informationString[13],
			"Age: " + _informationString[14],
			"Energy: " + _informationString[15],
			"Energy/Max Energy in %: " + _informationString[16],
			"Temperature: " + _informationString[17],
			"HeatLoss: " + _informationString[18],
			"Energy-Heat-Production: " + _informationString[19],
			"Fitness: " + _informationString[20],
			"Size: " + _informationString[21],
			"Generation: " + _informationString[22]
		};

		//resizes proportional to the size of the organism
		tmpShape.setRadius(10.0 * _simulation->getInformationOrganism()->getSize());
		tmpShape.setPosition(WINDOW_WIDTH, WINDOW_INFORMATION_HEIGHT / 1.55);
		sf::Color color(_simulation->getInformationOrganism()->getRed(), _simulation->getInformationOrganism()->getGreen(), _simulation->getInformationOrganism()->getBlue(), _simulation->getInformationOrganism()->getAlpha());
		tmpShape.setFillColor(color);
		_gameWindow.draw(tmpShape);

		//Add the different information lines for the entity
		for (int i = 0; i < sizeof(informationText2) / sizeof(informationText2[0]); i++)
		{
			printText(informationText2[i], WINDOW_WIDTH, WINDOW_INFORMATION_HEIGHT / 1.65 + i * INFORMATION_TEXT_SIZE + 2.0 * 10.0 * _simulation->getInformationOrganism()->getSize());
		}

		//Print the neural network of this organism
		printNeuralNetwork();
	}

	//Print Frame- and Time mode
	printText("(Push G)Time Mode: " + to_string(TIME_LAPSE), WINDOW_WIDTH + WINDOW_INFORMATION_WIDTH - 161.0, 0.0);
	printText("(Push H)Graphic Mode: " + to_string(GRAPHICS_ON), WINDOW_WIDTH + WINDOW_INFORMATION_WIDTH - 180.0, 15.0);
	printText("(Push S)Save World", WINDOW_WIDTH + WINDOW_INFORMATION_WIDTH - 180.0, 30.0);

}

//----------------------------------------------------------------------

//Prints a text at a certain location in the information window
void GraphicHandler::printText(string text, double x, double y)
{
	//Define important variables
	sf::Vector2f pos;
	string string;

	// left mouse button is pressed: get information from the tile the mouse is hovering above
	sf::Text textObj;
	textObj.setFont(_font);
	textObj.setCharacterSize(INFORMATION_TEXT_SIZE);
	textObj.setFillColor(sf::Color::Black);
	textObj.setOutlineColor(sf::Color::Black);

	//Draw the text at a position
	textObj.setString(text);
	pos = sf::Vector2f(x, y);
	textObj.setPosition(pos);
	_gameWindow.draw(textObj);
}

//----------------------------------------------------------------------

//Print neural network
void GraphicHandler::printNeuralNetwork()
{
	//Draw the neural network
	//Draw the input nodes
	printLayer(INPUT_NEURONS, DISTANCE_INPUT_NEURON_FACTOR, WINDOW_INFORMATION_HEIGHT);

	//Draw the hidden nodes	
	for (int hiddenLayers = 0; hiddenLayers < NUM_LAYERS - 2; hiddenLayers++)
	{
		printLayer(HIDDEN_NEURONS, DISTANCE_HIDDEN_NEURON_FACTOR, WINDOW_INFORMATION_HEIGHT + (hiddenLayers + 1) * DISTANCE_Y_NEURON_FACTOR * RADIUS_NEURON);
	}

	//Draw the output nodes
	printLayer(OUTPUT_NEURONS, DISTANCE_OUTPUT_NEURON_FACTOR, WINDOW_INFORMATION_HEIGHT + (NUM_LAYERS - 1) * DISTANCE_Y_NEURON_FACTOR * RADIUS_NEURON);

	//Draw the edges
	printEdges();
}

//----------------------------------------------------------------------

//Prints a layer of the neural network
void GraphicHandler::printLayer(int numNodes, double x, double y)
{
	//Shape for the organism
	sf::CircleShape tmpShape(RADIUS_NEURON);

	for (int i = 0; i < numNodes; i++)
	{
		tmpShape.setPosition(WINDOW_WIDTH + RADIUS_NEURON * 2 + i * x * RADIUS_NEURON, y);
		sf::Color color(0, 0, 0, 255);
		tmpShape.setFillColor(color);
		_gameWindow.draw(tmpShape);
	}
}

//----------------------------------------------------------------------

//Prints the edges between two layers
void GraphicHandler::printEdges()
{	
	int edges = 0;
	edges = INPUT_NEURONS * HIDDEN_NEURONS + (NUM_LAYERS - 3) * HIDDEN_NEURONS * HIDDEN_NEURONS + HIDDEN_NEURONS * OUTPUT_NEURONS;
	if (NUM_LAYERS == 2)
		edges = INPUT_NEURONS * OUTPUT_NEURONS;
	for (int i = 0; i < edges; i++)
	{	
		if (_simulation->getInformationOrganism()->getNeuralNetwork().getWeights()[i] < 0.0)
		{
			_lines[i][0].color = sf::Color::Red;
			_lines[i][1].color = sf::Color::Red;
		}
		else
		{
			_lines[i][0].color = sf::Color::Black;
			_lines[i][1].color = sf::Color::Black;
		}
		_gameWindow.draw(_lines[i], 2, sf::Lines);
	}
}

//----------------------------------------------------------------------

//Clear the display
void GraphicHandler::clear()
{
	_gameWindow.clear(_color);
}

//----------------------------------------------------------------------

//Draws the display
void GraphicHandler::display()
{
	_gameWindow.display();
}

//----------------------------------------------------------------------

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
			_zPosition -= event.mouseWheel.delta * 3.0;
			if (_zPosition > CAMERA_Z_DISTANCE)
			{
				_zPosition = CAMERA_Z_DISTANCE;
			}
			if (_zPosition < 10)
			{
				_zPosition = 10;
			}

			//Rescales the sprites to the new distance view
			_grassSprite.setScale(sf::Vector2f(100.0 / _zPosition / (_grassTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 100.0 / _zPosition / (_grassTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));
			_waterSprite.setScale(sf::Vector2f(100.0 / _zPosition / (_waterTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 100.0 / _zPosition / (_waterTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));
			_stoneSprite.setScale(sf::Vector2f(100.0 / _zPosition / (_stoneTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 100.0 / _zPosition / (_stoneTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));
			_snowSprite.setScale(sf::Vector2f(100.0 / _zPosition / (_snowTexture.getSize().x * SIMULATION_X / WINDOW_WIDTH), 100.0 / _zPosition / (_snowTexture.getSize().y * SIMULATION_Y / WINDOW_HEIGHT)));

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
		
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				_posBefore = sf::Mouse::getPosition();
			}
		}

		double diffx = 0;
		double diffy = 0;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			diffx = (sf::Mouse::getPosition() - _posBefore).x / 20.0;
			diffy = (sf::Mouse::getPosition() - _posBefore).y / 20.0;

			_xPosition += diffx;
			_yPosition += diffy;

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
				_simulation->setInformationOrganism(nearstOrganism);
			}
			else
			{
				_simulation->setInformationOrganism(NULL);
			}
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::G)
			{
				TIME_LAPSE += 1;
				if (TIME_LAPSE == 6)
				{
					TIME_LAPSE = 0;
				}
			}
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::H)
			{
				GRAPHICS_ON = !GRAPHICS_ON;
			}
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::S)
			{
				_simulation->saveData();
			}
		}
	}
}

//----------------------------------------------------------------------

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
	if (xPosition + (int)(intervall * ((float)_mousePositionX / (float)WINDOW_WIDTH)) >= SIMULATION_X)
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
	if (yPosition + (int)(intervall * ((float)_mousePositionY / (float)WINDOW_HEIGHT)) >= SIMULATION_Y)
	{
		returnValue = SIMULATION_Y - 1;
	}
	return returnValue;
}