#pragma once

//World properties
static const double FREQUENCY = 2.0;
static const int OCTAVES = 7;

static const int SIMULATION_X = 256;
static const int SIMULATION_Y = 256;

static const double WATER_LEVEL = 0.0;		//Water level is at sign changing
static const double GRASS_LEVEL = 0.45;
static const double STONE_LEVEL = 0.75;

static const double HEIGHT_MULITPLICATOR = 50.0;
static const double OPT_TEMPERATURE = 25.0;
static const double LOW_TEMPERATURE = -20.0;
static const double TEMPERATURE_FLUCTUATION_FACTOR = 10.0;

static const double FOOD_TEMPERATURE_FACTOR = 1.0;
static const double FOOD_HEIGHT_FACTOR = 1.0;
static const double FOOD_NOISE_FACTOR = 5.0;

static const double MAX_FOOD_ON_TILE = 7.0;
static const double FOOD_GROWTH_FACTOR = 0.05;
static const double CHANCE_FOOD_GROWTH = 1.0;
static const double CHANCE_BIG_FOOD_GROWTH = 0.01;

//Graphic properties
static const int WINDOW_WIDTH = SIMULATION_X * 4;
static const int WINDOW_HEIGHT = SIMULATION_Y * 3;
static const int CAMERA_Z_DISTANCE = 60;

static const int WINDOW_INFORMATION_WIDTH = 500;
static const int WINDOW_INFORMATION_HEIGHT = 500;

static const double INFORMATION_WINDOW_SPRITE_SIZE = .1;

//Life properties
static const int STARTING_NUMBER_ORGANISM = 100;
static const double SIZE_ORGANISMS = 1.0;
static const double ENERGY_CONSUMPTION_FACTOR = 1.0;
static const double STARTING_ENERGY = 200.0;
static const double STARTING_TEMPERATURE = 37.0;
static const double ENERGY_HEAT_PRODUCTION = 5.0;
static const double HEAT_LOSS_FACTOR = 0.7;

static const double MOVEMENT_SPEED = 1.0;
static const double MOVEMENT_ENERGY_LOST = 5.0;
static const double CONSUMPTION_FACTOR = 5.0;
static const double FOOD_ENERGY_FACTOR = 1.5;

//Network properties
static const double MIN_RANDOM_WEIGHT = -5.0;
static const double MAX_RANDOM_WEIGHT = 5.0;

static const int ADJACENT_TILES_RADIUS = 0;
static const int INPUTS_FOR_BODY_PROPERTIES = 2;

static const int NUM_LAYERS = 3;
static const int INPUT_NEURONS = 2 * (2 * ADJACENT_TILES_RADIUS + 1) * (2 * ADJACENT_TILES_RADIUS + 1) + INPUTS_FOR_BODY_PROPERTIES;
static const int OUTPUT_NEURONS = 2;
static const int HIDDEN_NEURONS = INPUT_NEURONS / 2;

static const double CHANCE_MUTATE = 0.07;
static const double MUTATION_PERTUBATE_PROCENT = 0.1;
static const double MUTATION_PERTUBATE_ADD = 1.0;

static const double SIGMOID_STRETCHX_FACTOR = 0.0005;
static const double SIGMOID_STRETCHY_FACTOR = 1.5;

//Network graphics
static const double RADIUS_NEURON = 3.0;