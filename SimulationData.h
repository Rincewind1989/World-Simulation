#pragma once

//UI variables
extern bool TIME_LAPSE;
extern bool GRAPHICS_ON;

//World properties
//Perlin Noise Properties
extern const double FREQUENCY;	//Frequency in which the perlin noise works, highest frequency results in more bumpy terrain
extern const int OCTAVES;			//Octaves are the number of reshaping, highest octaves result in a more natural terrain

//World size
extern const int SIMULATION_X;
extern const int SIMULATION_Y;

//World height terrain type
extern const double WATER_LEVEL;	//Highets level Water occurs
extern const double GRASS_LEVEL;		//Highets level Grass occurs
extern const double STONE_LEVEL;		//Highets level Stone occurs

//Environment properties
extern const double HEIGHT_MULITPLICATOR;	//Height factor which is multiplies on the height to get a more realistic height
extern const double OPT_TEMPERATURE;			//The optimum temperature that can occur naturally
extern const double LOW_TEMPERATURE;		//The lowest temperature that can occur
extern const double TEMPERATURE_FLUCTUATION_FACTOR;	//Factor for the fluctation of the temperaturemap with perlin noise

//Food distribution and growth factor
extern const double FOOD_TEMPERATURE_FACTOR;	//Multiplyfactor for the food growth depending on the temperature
extern const double FOOD_HEIGHT_FACTOR;		//Multiplyfactor for the food growth depending on the height
extern const double FOOD_NOISE_FACTOR;		//Factor for the fluctuation of the food for the perlin noise
extern const double MAX_FOOD_ON_TILE;			//Maximum food that can be on a tile
extern const double FOOD_GROWTH_FACTOR;		//Factor with which the food growths
extern const double CHANCE_FOOD_GROWTH;		//Chance that food growth on a tile per tick
extern const double CHANCE_BIG_FOOD_GROWTH;	//Chance that a big food growth happens on a tile per tick

//Body heat flux towards environment temperature
extern const double TEMPERATURE_AIR_FLUX_FACTOR;

//Graphic properties
//World Simulation Window properties
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const int CAMERA_Z_DISTANCE;
extern const double SIZE_ORGANISMS;
extern const double ALPHA_MIN;

//Information window properties
extern const int WINDOW_INFORMATION_WIDTH;
extern const int WINDOW_INFORMATION_HEIGHT;
extern const double INFORMATION_WINDOW_SPRITE_SIZE;

//Network graphics
extern const double RADIUS_NEURON;	//Radius of a drawn neuron on the information window

//Life properties
//Organism properties
extern const int STARTING_NUMBER_ORGANISM;
extern const double ENERGY_CONSUMPTION_FACTOR;	//Consumption factor for every organism to produce heat
extern const double STARTING_ENERGY;			//Starting energy for a organism
extern const double STARTING_TEMPERATURE;		//Starting temperature for a organism
extern const double ENERGY_HEAT_PRODUCTION;		//Factor in which energy is changed into temperature
extern const double HEAT_LOSS_FACTOR;				//Loss of the body temperature towards the environment
extern const double MOVEMENT_SPEED;				//Movementspeed of the organisms
extern const double MOVEMENT_ENERGY_LOST;			//Loss of energy based on the movementspeed
extern const double CONSUMPTION_FACTOR;			//Factor with which the organisms consume food from tile
extern const double FOOD_ENERGY_FACTOR;			//Factor with which food is conversed into energy
extern const double LOWEST_HEAT_LOSS_VALUE;
extern const double HIGHEST_HEAT_LOSS_VALUE;
extern const double NEWLIFE_ENERGY_CONSUMPTION;	//Energy needed to breed a new offspring
extern const double COLD_TEMP_DEATH;
extern const double HEAT_TEMP_DEATH;

extern const double SIZE_ORGANISM;				//Size of the organisms

extern const double ATTACK_DAMAGE;				//Attack damage of an organism

extern const double SIZE_ENERGY_LOSS_FACTOR;	//Loss of energy based on the size factor

extern const double OPTIM_TEMPERATURE;			//Optim temperature the organism needs to work at 100% (Like eating,moving,etc.)

extern const double MUTATE_COLOR;				//Chance that a color mutates

//Network properties
extern const double MIN_RANDOM_WEIGHT;
extern const double MAX_RANDOM_WEIGHT;

extern const int ADJACENT_TILES_RADIUS;			//Radius of the organism's sight
extern const int INPUTS_FOR_BODY_PROPERTIES;	//Inputs of the body properties for the neural network(Like bodytemperature,bodyenergy,etc.)
extern const int NUMBER_NEXT_ENTITES;			//Number of next entities that can be identified

/*Reminder! What can the organisms detect.
-Adjacent tiles radius - temperature, food, number entities
-1 Bias
-Inputs from the body - temperature, energy
-x next entities and their colours


What can the organisms output
-Move x-y axes (2 Outputs)
-Give birth by asexuall

*/
extern const int NUM_LAYERS;	//Number of layers (This includes input and output layer)
extern const int INPUT_NEURONS; //Number of need inputneurons to cover all inputs
extern const int OUTPUT_NEURONS;	//Number of output Neurons to cover all outputs needed
extern const int HIDDEN_NEURONS; //Hidden neurons

extern const double CHANCE_MUTATE;	//Chance that a mutation of a weight occurs
extern const double MUTATION_PERTUBATE_PROCENT;	//Procentage with which a muation pertubates a weight
extern const double MUTATION_PERTUBATE_ADD;	//Absolute value with which a mutation pertubates a weight

extern const double SIGMOID_STRETCHX_FACTOR;	//Stretch factor for the sigmoid func on the x-axes
extern const double SIGMOID_STRETCHY_FACTOR;	//Stretch factor for the sigmoid func on the y-axes

extern const double RADIUS_NEXT_ENTITIES;	//Radius in which the next entities are recognized