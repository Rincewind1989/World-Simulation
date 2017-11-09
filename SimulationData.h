#pragma once

//Graphic properties
static const int WINDOW_WIDTH = 1024;
static const int WINDOW_HEIGHT = 1024;
static const int CAMERA_Z_DISTANCE = 60;

static const int WINDOW_INFORMATION_WIDTH = 500;
static const int WINDOW_INFORMATION_HEIGHT = 500;

static const double INFORMATION_WINDOW_SPRITE_SIZE = .1;

//World properties
static const int SIMULATION_X = 256;
static const int SIMULATION_Y = 256;

static const double WATER_LEVEL = 0.3;
static const double GRASS_LEVEL = 0.7;
static const double STONE_LEVEL = 0.9;

//Life properties
static const int STARTING_NUMBER_ORGANISM = 100;
static const double SIZE_ORGANISMS = 1.0;
static const double ENERGY_CONSUMPTION_FACTOR = 1.0;
static const double STARTING_ENERGY = 100.0;
static const double STARTING_TEMPERATURE = 37.0;
static const double ENERGY_HEAT_PRODUCTION = 5.0;
static const double HEAT_LOSS_FACTOR = 1.0;