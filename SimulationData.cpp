#include "SimulationData.h"

//Save variables
int NUMBER_FRAMES_TO_SAVE = 100;
bool SAVE_FITNESS = true;
bool SAVE_SIZE = true;
bool SAVE_POPULATION = true;

//Debug variables
int DEATH_BY_ENERGY = 0;
int DEATH_BY_TEMP = 0;
int DEATH_BY_AGE = 0;
int DEATHS = 0;
int SEED = 0;

//UI variables
int TIME_LAPSE = 0;
bool GRAPHICS_ON = true;
bool EXIT = false;

//World properties
//Perlin Noise Properties
int RANDOM_SEED = 0;		//The random seed for the world generation. (0 means a random seed)
double FREQUENCY = 2.0;	//Frequency in which the perlin noise works, highest frequency results in more bumpy terrain
int OCTAVES = 7;			//Octaves are the number of reshaping, highest octaves result in a more natural terrain
//----------------------------------------------------------------------								
//World size
int SIMULATION_X = 256;
int SIMULATION_Y = 256;
//----------------------------------------------------------------------
//World height terrain type
double WATER_LEVEL = -0.35;		//Highest level Water occurs
double GRASS_LEVEL = 0.45;		//Highest level Grass occurs
double STONE_LEVEL = 0.75;		//Highest level Stone occurs
//----------------------------------------------------------------------
//Environment properties
double HEIGHT_MULITPLICATOR = 50.0;		//Height factor which is multiplied on the perlin noise height to get a more realistic height
double OPT_TEMPERATURE = 35.0;			//The optimum temperature that can occur naturally
double LOW_TEMPERATURE = -20.0;			//The lowest temperature that can occur
double TEMPERATURE_FLUCTUATION_FACTOR = 10.0;	//Factor for the fluctation of the temperaturemap with perlin noise
double TEMPERATURE_WATER = 3.0;				//Temperature of the water
//----------------------------------------------------------------------
//Food distribution and growth factor
double FOOD_TEMPERATURE_FACTOR = 0.75;	//Multiplyfactor for the food growth depending on the temperature
double FOOD_HEIGHT_FACTOR = 0.5;		//Multiplyfactor for the food growth depending on the height
double FOOD_NOISE_FACTOR = 5.0;		//Factor for the fluctuation of the food for the perlin noise
double MAX_FOOD_ON_TILE = 10.0;			//Maximum food that can be on a tile (Because it is a ODE, there can temporarily be more food on a tile, but it will desolve)
double FOOD_GROWTH_FACTOR = 0.01;		//Factor with which the food growths
double CHANCE_FOOD_GROWTH = 0.2;		//Chance that food growth on a tile per tick
double CHANCE_BIG_FOOD_GROWTH = 0.005;	//Chance that a big food growth happens on a tile per tick
double CHANCE_FOR_DISCRETE_FOOD_SPAWN = 0.001;	//Chance that food spawns in the discrete mode
//----------------------------------------------------------------------
//Body heat flux towards environment temperature
double TEMPERATURE_AIR_FLUX_FACTOR = 0.08;

//----------------------------------------------------------------------
//Graphic properties
//World Simulation Window properties
int WINDOW_WIDTH = 1024;
int WINDOW_HEIGHT = 1024;
int CAMERA_Z_DISTANCE = 200;
double SIZE_ORGANISMS = 1.0;
double ALPHA_MIN = 200.0;
//----------------------------------------------------------------------
//Information window properties
int WINDOW_INFORMATION_WIDTH = 500;
int WINDOW_INFORMATION_HEIGHT = 475;
double INFORMATION_WINDOW_SPRITE_SIZE = .1;
int INFORMATION_TEXT_SIZE = 16;
double RADIUS_NEURON = 3.25;	//Radius of a drawn neuron on the information window
double DISTANCE_Y_NEURON_FACTOR = 25.0;
double DISTANCE_INPUT_NEURON_FACTOR = 2.25;;
double DISTANCE_HIDDEN_NEURON_FACTOR = 4.5;
double DISTANCE_OUTPUT_NEURON_FACTOR = 7.0;
//----------------------------------------------------------------------
//Life properties
//Organism properties
int STARTING_NUMBER_ORGANISM = 100;
int MIN_NUMBER_ORGANISM = STARTING_NUMBER_ORGANISM;			//If number of organisms get below this value, random created organisms appear in the simulation
double STARTING_ENERGY = 200.0;								//Starting energy for an organism (The maximum energy an organism can have depends on its size)
double MAX_ENERGY_FACTOR = STARTING_ENERGY * 2.5;			//Maximum Energy Factor(The maximum energy an organism can have depends on its size and this factor)
double AVG_AGE_DEATH = 100.0;								//The age increases by 0.01 per frame
double STARTING_TEMPERATURE = 37.0;							//Starting temperature for a organism
double ENERGY_HEAT_PRODUCTION = 1.5;						//Factor in which energy is changed into temperature that is mutatable by breeding new offsprings
double LOWEST_ENERGY_HEAT_PRODUCTION = 0.5;
double HIGHEST_ENERGY_HEAT_PRODUCTION = 2.5;
double HEAT_LOSS_FACTOR = 0.65;								//Loss of the body temperature towards the environment
double LOWEST_HEAT_LOSS_VALUE = 0.75;
double HIGHEST_HEAT_LOSS_VALUE = 1.5;
double MOVEMENT_SPEED = 2.0;								//Movementspeed of the organisms
double MOVEMENT_ENERGY_LOST = 1.05;							//Loss of energy based on the movementspeed
double CONSUMPTION_FACTOR = 9.0;							//Factor with which the organisms consume food from tile
double FOOD_ENERGY_FACTOR = 1.35;							//Factor with which food is transformed into energy
double NEWLIFE_ENERGY_CONSUMPTION = STARTING_ENERGY * 1.25;	//Energy needed to breed a new offspring
double COLD_TEMP_DEATH = 20.0;
double HEAT_TEMP_DEATH = 42.0;
double SIZE_ORGANISM = 1.0;									//Size of the organisms
double ATTACK_DAMAGE = 10.0;								//Attack damage of an organism
double SIZE_ENERGY_LOSS_FACTOR = 0.35;						//Loss of energy based on the size factor
double OPTIM_TEMPERATURE = 32.0;							//Optim temperature the organism needs to work at 100% (Like eating,moving,etc.)
double MUTATE_STAT = 0.07;									//Chance that a color mutates
double MOVEMENT_ENERGY_FACTOR_IN_WATER = 1.5;				//Factor for movement energy lost penalty in water
double MOVEMENT_REDUCTION_IN_WATER = 0.2;
double TIME_FOR_FITNESS_REPRODUCTION = 25.0;
//----------------------------------------------------------------------																								
//Network properties
double MIN_RANDOM_WEIGHT = -5.0;
double MAX_RANDOM_WEIGHT = 5.0;
int ADJACENT_TILES_RADIUS = 1;			//Radius of the organism's sight
int INPUTS_FOR_BODY_PROPERTIES = 7;	//Inputs of the body properties for the neural network(Like bodytemperature, bodyenergy,size, colors ,etc...)
int NUMBER_NEXT_ENTITES = 4;			//Number of next entities that can be identified
int NUM_LAYERS = 3;	//Number of layers (This includes input and output layer) MUST ALWAYS BE >= 2
//----------------------------------------------------------------------
//Number of need inputneurons to cover all inputs
int INPUT_NEURONS = 3 * (2 * ADJACENT_TILES_RADIUS + 1) * (2 * ADJACENT_TILES_RADIUS + 1) //Adjecent tile properties (Like Temperature,Food,Number of entites on tile...)
+ INPUTS_FOR_BODY_PROPERTIES + NUMBER_NEXT_ENTITES * 7											//Number of input properties and properties of N-next entites (Like, size, relative position, color, etc...)
+ 1;																							//Bias
int OUTPUT_NEURONS = 5;	//Number of output Neurons to cover all outputs needed
int HIDDEN_NEURONS = INPUT_NEURONS / 2; //Hidden neurons
double CHANCE_MUTATE = 1;	//Chance that a mutation of a weight occurs
double MUTATION_PERTUBATE_PROCENT = 0.15;	//Max and min pertubation in procent. A real number between this value is taken and added on the weight
double SIGMOID_STRETCHX_FACTOR = 0.5;	//Stretch factor for the sigmoid func on the x-axes
double SIGMOID_STRETCHY_FACTOR = 1;	//Stretch factor for the sigmoid func on the y-axes
int RADIUS_NEXT_ENTITIES = 200;	//Radius in which the next entities are recognized in pixels