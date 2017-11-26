#include "SimulationData.h"

//UI variables
bool TIME_LAPSE = false;
bool GRAPHICS_ON = true;

//World properties
//Perlin Noise Properties
const double FREQUENCY = 2.0;	//Frequency in which the perlin noise works, highest frequency results in more bumpy terrain
const int OCTAVES = 7;			//Octaves are the number of reshaping, highest octaves result in a more natural terrain

//World size
const int SIMULATION_X = 256;
const int SIMULATION_Y = 256;

//World height terrain type
const double WATER_LEVEL = -0.15;	//Highets level Water occurs
const double GRASS_LEVEL = 0.45;		//Highets level Grass occurs
const double STONE_LEVEL = 0.75;		//Highets level Stone occurs

											//Environment properties
const double HEIGHT_MULITPLICATOR = 50.0;	//Height factor which is multiplies on the height to get a more realistic height
const double OPT_TEMPERATURE = 35.0;			//The optimum temperature that can occur naturally
const double LOW_TEMPERATURE = -20.0;		//The lowest temperature that can occur
const double TEMPERATURE_FLUCTUATION_FACTOR = 10.0;	//Factor for the fluctation of the temperaturemap with perlin noise

															//Food distribution and growth factor
const double FOOD_TEMPERATURE_FACTOR = 1.0;	//Multiplyfactor for the food growth depending on the temperature
const double FOOD_HEIGHT_FACTOR = 1.0;		//Multiplyfactor for the food growth depending on the height
const double FOOD_NOISE_FACTOR = 5.0;		//Factor for the fluctuation of the food for the perlin noise
const double MAX_FOOD_ON_TILE = 7.0;			//Maximum food that can be on a tile
const double FOOD_GROWTH_FACTOR = 0.02;		//Factor with which the food growths
const double CHANCE_FOOD_GROWTH = 0.2;		//Chance that food growth on a tile per tick
const double CHANCE_BIG_FOOD_GROWTH = 0.01;	//Chance that a big food growth happens on a tile per tick

													//Body heat flux towards environment temperature
const double TEMPERATURE_AIR_FLUX_FACTOR = 0.08;

//Graphic properties
//World Simulation Window properties
const int WINDOW_WIDTH = SIMULATION_X * 4;
const int WINDOW_HEIGHT = SIMULATION_Y * 3;
const int CAMERA_Z_DISTANCE = 100;
const double SIZE_ORGANISMS = 1.0;
extern const double ALPHA_MIN = 200.0;

//Information window properties
const int WINDOW_INFORMATION_WIDTH = 500;
const int WINDOW_INFORMATION_HEIGHT = 500;
const double INFORMATION_WINDOW_SPRITE_SIZE = .1;

//Network graphics
const double RADIUS_NEURON = 2.0;	//Radius of a drawn neuron on the information window

//Life properties
//Organism properties
const int STARTING_NUMBER_ORGANISM = 100;
const double ENERGY_CONSUMPTION_FACTOR = 0.3;	//Consumption factor for every organism to produce heat
const double STARTING_ENERGY = 200.0;			//Starting energy for a organism
const double STARTING_TEMPERATURE = 37.0;		//Starting temperature for a organism
const double ENERGY_HEAT_PRODUCTION = 5.0;		//Factor in which energy is changed into temperature
const double HEAT_LOSS_FACTOR = 0.7;			//Loss of the body temperature towards the environment
const double MOVEMENT_SPEED = 2.0;				//Movementspeed of the organisms
const double MOVEMENT_ENERGY_LOST = 1.2;		//Loss of energy based on the movementspeed
const double CONSUMPTION_FACTOR = 9.0;			//Factor with which the organisms consume food from tile
const double FOOD_ENERGY_FACTOR = 1.5;			//Factor with which food is conversed into energy
const double LOWEST_HEAT_LOSS_VALUE = 0.5;
const double HIGHEST_HEAT_LOSS_VALUE = 1.25;
const double NEWLIFE_ENERGY_CONSUMPTION = STARTING_ENERGY * 1.25;	//Energy needed to breed a new offspring
const double COLD_TEMP_DEATH = 20.0;
const double HEAT_TEMP_DEATH = 42.0;

const double SIZE_ORGANISM = 1.0;				//Size of the organisms

const double ATTACK_DAMAGE = 10.0;				//Attack damage of an organism

extern const double SIZE_ENERGY_LOSS_FACTOR = 0.5;	//Loss of energy based on the size factor

const double OPTIM_TEMPERATURE = 32.0;			//Optim temperature the organism needs to work at 100% (Like eating,moving,etc.)

const double MUTATE_COLOR = 0.07;				//Chance that a color mutates


																									
//Network properties
const double MIN_RANDOM_WEIGHT = -10.0;
const double MAX_RANDOM_WEIGHT = 10.0;

const int ADJACENT_TILES_RADIUS = 1;			//Radius of the organism's sight
const int INPUTS_FOR_BODY_PROPERTIES = 2;	//Inputs of the body properties for the neural network(Like bodytemperature,bodyenergy,etc.)
const int NUMBER_NEXT_ENTITES = 4;			//Number of next entities that can be identified

const int NUM_LAYERS = 3;	//Number of layers (This includes input and output layer)
const int INPUT_NEURONS = 3 * (2 * ADJACENT_TILES_RADIUS + 1) * (2 * ADJACENT_TILES_RADIUS + 1) + 1 + INPUTS_FOR_BODY_PROPERTIES + NUMBER_NEXT_ENTITES * 5; //Number of need inputneurons to cover all inputs
const int OUTPUT_NEURONS = 5;	//Number of output Neurons to cover all outputs needed
const int HIDDEN_NEURONS = INPUT_NEURONS / 2; //Hidden neurons

const double CHANCE_MUTATE = 0.07;	//Chance that a mutation of a weight occurs
const double MUTATION_PERTUBATE_PROCENT = 0.1;	//Procentage with which a muation pertubates a weight
const double MUTATION_PERTUBATE_ADD = 1.0;	//Absolute value with which a mutation pertubates a weight

const double SIGMOID_STRETCHX_FACTOR = 0.5;	//Stretch factor for the sigmoid func on the x-axes
const double SIGMOID_STRETCHY_FACTOR = 1.5;	//Stretch factor for the sigmoid func on the y-axes

const double RADIUS_NEXT_ENTITIES = 3;	//Radius in which the next entities are recognized