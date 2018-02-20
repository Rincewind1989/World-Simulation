#pragma once

//Save values
extern int NUMBER_FRAMES_TO_SAVE;
extern bool SAVE_FITNESS;
extern bool SAVE_SIZE;
extern bool SAVE_POPULATION;

//Debug variables
extern int DEATH_BY_ENERGY;
extern int DEATH_BY_TEMP;
extern int DEATH_BY_AGE;
extern int DEATHS;
extern int SEED;

//UI variables
extern int TIME_LAPSE;
extern bool GRAPHICS_ON;
extern bool EXIT;
//----------------------------------------------------------------------
//World properties
//Perlin Noise Properties
extern int RANDOM_SEED;		//The random seed for the world generation. (0 means a random seed)
extern double FREQUENCY;		//Frequency in which the perlin noise works, highest frequency results in more bumpy terrain
extern int OCTAVES;			//Octaves are the number of reshaping, highest octaves result in a more natural terrain
//----------------------------------------------------------------------
//World size
extern int SIMULATION_X;
extern int SIMULATION_Y;
//----------------------------------------------------------------------
//World height terrain type
extern double WATER_LEVEL;		//Highest level Water occurs
extern double GRASS_LEVEL;		//Highest level Grass occurs
extern double STONE_LEVEL;		//Highest level Stone occurs
//----------------------------------------------------------------------
//Environment properties
extern double HEIGHT_MULITPLICATOR;	//Height factor which is multiplies on the height to get a more realistic height
extern double OPT_TEMPERATURE;			//The optimum temperature that can occur naturally
extern double LOW_TEMPERATURE;		//The lowest temperature that can occur
extern double TEMPERATURE_FLUCTUATION_FACTOR;	//Factor for the fluctation of the temperaturemap with perlin noise
extern double TEMPERATURE_WATER;			//Temperature of the water
//----------------------------------------------------------------------
//Food distribution and growth factor
extern double FOOD_TEMPERATURE_FACTOR;	//Multiplyfactor for the food growth depending on the temperature
extern double FOOD_HEIGHT_FACTOR;		//Multiplyfactor for the food growth depending on the height
extern double FOOD_NOISE_FACTOR;		//Factor for the fluctuation of the food for the perlin noise
extern double MAX_FOOD_ON_TILE;			//Maximum food that can be on a tile
extern double FOOD_GROWTH_FACTOR;		//Factor with which the food growths
extern double CHANCE_FOOD_GROWTH;		//Chance that food growth on a tile per tick
extern double CHANCE_BIG_FOOD_GROWTH;	//Chance that a big food growth happens on a tile per tick
extern double CHANCE_FOR_DISCRETE_FOOD_SPAWN;	//Chance that food spawns in the discrete mode
//----------------------------------------------------------------------
//Body heat flux towards environment temperature
extern double TEMPERATURE_AIR_FLUX_FACTOR;
//----------------------------------------------------------------------
//Graphic properties
//World Simulation Window properties
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern int CAMERA_Z_DISTANCE;
extern double SIZE_ORGANISMS;
extern double ALPHA_MIN;
//----------------------------------------------------------------------
//Information window properties
extern int WINDOW_INFORMATION_WIDTH;
extern int WINDOW_INFORMATION_HEIGHT;
extern double INFORMATION_WINDOW_SPRITE_SIZE;
extern int INFORMATION_TEXT_SIZE;
extern double RADIUS_NEURON;	//Radius of a drawn neuron on the information window
extern double DISTANCE_Y_NEURON_FACTOR;
extern double DISTANCE_INPUT_NEURON_FACTOR;
extern double DISTANCE_HIDDEN_NEURON_FACTOR;
extern double DISTANCE_OUTPUT_NEURON_FACTOR;
//----------------------------------------------------------------------
//Life properties
//Organism properties
extern int STARTING_NUMBER_ORGANISM;
extern int MIN_NUMBER_ORGANISM;			//If number of organisms get below this value, random created organisms appear in the simulation
extern double STARTING_ENERGY;			//Starting energy for am organism  (The maximum energy an organism can have depends on its size)
extern double MAX_ENERGY_FACTOR;		//Maximum Energy Factor(The maximum energy an organism can have depends on its size and this factor)
extern double AVG_AGE_DEATH;	//The age increases by 0.01 per frame
extern double STARTING_TEMPERATURE;		//Starting temperature for a organism
extern double ENERGY_HEAT_PRODUCTION;		//Factor in which energy is changed into temperature
extern double LOWEST_ENERGY_HEAT_PRODUCTION;
extern double HIGHEST_ENERGY_HEAT_PRODUCTION;
extern double HEAT_LOSS_FACTOR;			//Loss of the body temperature towards the environment which can be changed by evolution
extern double LOWEST_HEAT_LOSS_VALUE;
extern double HIGHEST_HEAT_LOSS_VALUE;
extern double MOVEMENT_SPEED;				//Movementspeed of the organisms
extern double MOVEMENT_ENERGY_LOST;		//Loss of energy based on the movementspeed
extern double CONSUMPTION_FACTOR;			//Factor with which the organisms consume food from tile
extern double FOOD_ENERGY_FACTOR;			//Factor with which food is conversed into energy
extern double NEWLIFE_ENERGY_CONSUMPTION;	//Energy needed to breed a new offspring
extern double COLD_TEMP_DEATH;
extern double HEAT_TEMP_DEATH;
extern double SIZE_ORGANISM;				//Size of the organisms
extern double ATTACK_DAMAGE;				//Attack damage of an organism
extern double SIZE_ENERGY_LOSS_FACTOR;	//Loss of energy based on the size factor
extern double OPTIM_TEMPERATURE;			//Optim temperature the organism needs to work at 100% (Like eating,moving,etc.)
extern double MUTATE_STAT;				//Chance that a color mutates
extern double MOVEMENT_ENERGY_FACTOR_IN_WATER;	//Factor for movement penalty in water
extern double MOVEMENT_REDUCTION_IN_WATER;
extern double TIME_FOR_FITNESS_REPRODUCTION;
//----------------------------------------------------------------------
//Network properties
extern double MIN_RANDOM_WEIGHT;
extern double MAX_RANDOM_WEIGHT;
extern int ADJACENT_TILES_RADIUS;			//Radius of the organism's sight
extern int INPUTS_FOR_BODY_PROPERTIES;	//Inputs of the body properties for the neural network(Like bodytemperature,bodyenergy,etc.)
extern int NUMBER_NEXT_ENTITES;			//Number of next entities that can be identified
//----------------------------------------------------------------------
/*Reminder! What can the organisms detect.
-Adjacent tiles radius - temperature, food, number entities
-1 Bias
-Inputs from the body - temperature, energy
-x next entities and their colours


What can the organisms output
-Move x-y axes (2 Outputs)
-Give birth by asexuall

*/
//----------------------------------------------------------------------
extern int NUM_LAYERS;	//Number of layers (This includes input and output layer)
extern int INPUT_NEURONS; //Number of need inputneurons to cover all inputs
extern int OUTPUT_NEURONS;	//Number of output Neurons to cover all outputs needed
extern int HIDDEN_NEURONS; //Hidden neurons
extern double CHANCE_MUTATE;	//Chance that a mutation of a weight occurs
extern double MUTATION_PERTUBATE_PROCENT;	//Procentage with which a muation pertubates a weight
extern double MUTATION_PERTUBATE_ADD;	//Absolute value with which a mutation pertubates a weight
extern double SIGMOID_STRETCHX_FACTOR;	//Stretch factor for the sigmoid func on the x-axes
extern double SIGMOID_STRETCHY_FACTOR;	//Stretch factor for the sigmoid func on the y-axes
extern int RADIUS_NEXT_ENTITIES;	//Radius in which the next entities are recognized in pixels