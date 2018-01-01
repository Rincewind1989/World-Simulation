#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <fstream>
#include <iostream>
#include "INIReader.h"
#include "SimulationData.h"
#include "GraphicHandler.h"
#include "Simulation.h"

using namespace std;

void readIni();

int main()
{
	cout << "Reading Constants.ini...\n";
	readIni();
	cout << "\nCreating simulation...\n";
	Simulation simulation;
	cout << "\nCreating graphichandler...\n";
	GraphicHandler graphicHandler(simulation);


	cout << "\nRunning simulation...\n";
	while (true)
	{
		//Update Graphics
		graphicHandler.clear();
		if (GRAPHICS_ON)
		{
			graphicHandler.printWorld();
			graphicHandler.printEntities();
		}
		graphicHandler.printInformation();
		graphicHandler.display();
		graphicHandler.getEvents();

		//Update Simulationtime
		simulation.deltaTime();

		//Checks for slow motion
		if (!simulation.timelapseCheck() && TIME_LAPSE > 0)
		{
			continue;
		}
		
		//Update Simulation
		simulation.updateSimulation();
	}
}

//Reads in the Given Constants from the Constants file
void readIni()
{
	INIReader reader("Constants.ini");

	if (reader.ParseError() < 0) {
		cout << "Can't load 'Constants.ini'\n";
	}
	cout << "Config loaded from 'Constants.ini'\n";
	cout << "\nLoading World Properties.\n\n";
	cout << "random seed=" << reader.GetInteger("World properties", "random seed", -1) << "\n";
	RANDOM_SEED = reader.GetInteger("World properties", "random seed", -1);

	cout << "Frequency=" << reader.GetInteger("World properties", "Frequency", -1) << "\n";
	FREQUENCY = reader.GetInteger("World properties", "Frequency", -1);

	cout << "Octaves=" << reader.GetInteger("World properties", "Octaves", -1) << "\n";
	OCTAVES = reader.GetInteger("World properties", "Octaves", -1);

	cout << "Simulation_x=" << reader.GetInteger("World properties", "Simulation_x" , -1) << "\n";
	SIMULATION_X = reader.GetInteger("World properties", "Simulation_x", -1);

	cout << "Simulation_y=" << reader.GetInteger("World properties", "Simulation_y", -1) << "\n";
	SIMULATION_Y = reader.GetInteger("World properties", "Simulation_y", -1);

	cout << "Water_level=" << reader.GetReal("World properties", "Water_level", -1) << "\n";
	WATER_LEVEL = reader.GetReal("World properties", "Water_level", -1);

	cout << "Grass_level=" << reader.GetReal("World properties", "Grass_level", -1) << "\n";
	GRASS_LEVEL = reader.GetReal("World properties", "Grass_level", -1);

	cout << "Stone_level=" << reader.GetReal("World properties", "Stone_level", -1) << "\n";
	STONE_LEVEL = reader.GetReal("World properties", "Stone_level", -1);

	cout << "Opt_temperature=" << reader.GetReal("World properties", "Opt_temperature", -1) << "\n";
	OPT_TEMPERATURE = reader.GetReal("World properties", "Opt_temperature", -1);

	cout << "Low_temperature=" << reader.GetReal("World properties", "Low_temperature", -1) << "\n";
	LOW_TEMPERATURE = reader.GetReal("World properties", "Low_temperature", -1);

	cout << "Temperature_fluctuation_factor=" << reader.GetReal("World properties", "Temperature_fluctuation_factor", -1) << "\n";
	TEMPERATURE_AIR_FLUX_FACTOR = reader.GetReal("World properties", "Temperature_fluctuation_factor", -1);

	cout << "Food_temperature_factor=" << reader.GetReal("World properties", "Food_temperature_factor", -1) << "\n";
	FOOD_TEMPERATURE_FACTOR = reader.GetReal("World properties", "Food_temperature_factor", -1);

	cout << "Food_height_factor=" << reader.GetReal("World properties", "Food_height_factor", -1) << "\n";
	FOOD_HEIGHT_FACTOR = reader.GetReal("World properties", "Food_height_factor", -1);

	cout << "Food_noise_factor=" << reader.GetReal("World properties", "Food_noise_factor", -1) << "\n";
	FOOD_NOISE_FACTOR = reader.GetReal("World properties", "Food_noise_factor", -1);

	cout << "Max_food_on_tile =" << reader.GetReal("World properties", "Max_food_on_tile", -1) << "\n";
	MAX_FOOD_ON_TILE = reader.GetReal("World properties", "Max_food_on_tile", -1);

	cout << "Food_growth_factor=" << reader.GetReal("World properties", "Food_growth_factor", -1) << "\n";
	FOOD_GROWTH_FACTOR = reader.GetReal("World properties", "Food_growth_factor", -1);

	cout << "Chance_food_growth=" << reader.GetReal("World properties", "Chance_food_growth", -1) << "\n";
	CHANCE_FOOD_GROWTH = reader.GetReal("World properties", "Chance_food_growth", -1);

	cout << "Chance_big_food_growth=" << reader.GetReal("World properties", "Chance_big_food_growth", -1) << "\n";
	CHANCE_BIG_FOOD_GROWTH = reader.GetReal("World properties", "Chance_big_food_growth", -1);

	cout << "Temperature_air_flux_factor=" << reader.GetReal("World properties", "Temperature_air_flux_factor", -1) << "\n";
	TEMPERATURE_AIR_FLUX_FACTOR = reader.GetReal("World properties", "Temperature_air_flux_factor", -1);

	cout << "\nLoading Life Properties.\n\n";

	cout << "Starting_number_organisms=" << reader.GetInteger("Life properties", "Starting_number_organisms", -1) << "\n";
	STARTING_NUMBER_ORGANISM = reader.GetInteger("Life properties", "Starting_number_organisms", -1);

	cout << "Min_number_organisms=" << reader.GetInteger("Life properties", "Min_number_organisms", -1) << "\n";
	MIN_NUMBER_ORGANISM = reader.GetInteger("Life properties", "Min_number_organisms", -1);

	cout << "Starting_energy=" << reader.GetReal("Life properties", "Starting_energy", -1) << "\n";
	STARTING_ENERGY = reader.GetReal("Life properties", "Starting_energy", -1);

	cout << "Starting_temperature=" << reader.GetReal("Life properties", "Starting_temperature", -1) << "\n";
	STARTING_TEMPERATURE = reader.GetReal("Life properties", "Starting_temperature", -1);

	cout << "Energy_heat_production=" << reader.GetReal("Life properties", "Energy_heat_production", -1) << "\n";
	ENERGY_HEAT_PRODUCTION = reader.GetReal("Life properties", "Energy_heat_production", -1);

	cout << "Lowest_energy_heat_production=" << reader.GetReal("Life properties", "Lowest_energy_heat_production", -1) << "\n";
	LOWEST_ENERGY_HEAT_PRODUCTION = reader.GetReal("Life properties", "Lowest_energy_heat_production", -1);

	cout << "Highest_energy_heat_production=" << reader.GetReal("Life properties", "Highest_energy_heat_production", -1) << "\n";
	HIGHEST_ENERGY_HEAT_PRODUCTION = reader.GetReal("Life properties", "Highest_energy_heat_production", -1);

	cout << "Heat_loss_factor=" << reader.GetReal("Life properties", "Heat_loss_factor", -1) << "\n";
	HEAT_LOSS_FACTOR = reader.GetReal("Life properties", "Heat_loss_factor", -1);

	cout << "Lowest_heat_loss_factor =" << reader.GetReal("Life properties", "Lowest_heat_loss_factor", -1) << "\n";
	LOWEST_HEAT_LOSS_VALUE = reader.GetReal("Life properties", "Lowest_heat_loss_factor", -1);

	cout << "Higehst_heat_loss_factor=" << reader.GetReal("Life properties", "Higehst_heat_loss_factor", -1) << "\n";
	HIGHEST_HEAT_LOSS_VALUE = reader.GetReal("Life properties", "Higehst_heat_loss_factor", -1);

	cout << "Movement_speed=" << reader.GetReal("Life properties", "Movement_speed", -1) << "\n";
	MOVEMENT_SPEED = reader.GetReal("Life properties", "Movement_speed", -1);

	cout << "Movement_energy_loss=" << reader.GetReal("Life properties", "Movement_energy_loss", -1) << "\n";
	MOVEMENT_ENERGY_LOST = reader.GetReal("Life properties", "Movement_energy_loss", -1);

	cout << "Consumption_food_factor=" << reader.GetReal("Life properties", "Consumption_food_factor", -1) << "\n";
	CONSUMPTION_FACTOR = reader.GetReal("Life properties", "Consumption_food_factor", -1);

	cout << "Food_energy_factor=" << reader.GetReal("Life properties", "Food_energy_factor", -1) << "\n";
	FOOD_ENERGY_FACTOR = reader.GetReal("Life properties", "Food_energy_factor", -1);

	cout << "Newlife_energy_constant=" << reader.GetInteger("Life properties", "Newlife_energy_constant", -1) << "\n";
	NEWLIFE_ENERGY_CONSUMPTION = reader.GetInteger("Life properties", "Newlife_energy_constant", -1);

	cout << "Cold_temp_death=" << reader.GetReal("Life properties", "Cold_temp_death", -1) << "\n";
	COLD_TEMP_DEATH = reader.GetReal("Life properties", "Cold_temp_death", -1);

	cout << "Heat_temp_death=" << reader.GetReal("Life properties", "Heat_temp_death", -1) << "\n";
	HEAT_TEMP_DEATH = reader.GetReal("Life properties", "Heat_temp_death", -1);

	cout << "Size_organism=" << reader.GetReal("Life properties", "Size_organism", -1) << "\n";
	SIZE_ORGANISM = reader.GetReal("Life properties", "Size_organism", -1);

	cout << "Attack_damage=" << reader.GetReal("Life properties", "Attack_damage", -1) << "\n";
	ATTACK_DAMAGE = reader.GetReal("Life properties", "Attack_damage", -1);

	cout << "Size_energy_loss_factor=" << reader.GetReal("Life properties", "Size_energy_loss_factor", -1) << "\n";
	SIZE_ENERGY_LOSS_FACTOR = reader.GetReal("Life properties", "Size_energy_loss_factor", -1);

	cout << "Optim_temperature=" << reader.GetReal("Life properties", "Optim_temperature", -1) << "\n";
	OPTIM_TEMPERATURE = reader.GetReal("Life properties", "Optim_temperature", -1);

	cout << "Mutate_stat=" << reader.GetReal("Life properties", "Mutate_stat", -1) << "\n";
	MUTATE_STAT = reader.GetReal("Life properties", "Mutate_stat", -1);

	cout << "Movement_energy_factor_water=" << reader.GetReal("Life properties", "Movement_energy_factor_water", -1) << "\n";
	MOVEMENT_ENERGY_FACTOR_IN_WATER = reader.GetReal("Life properties", "Movement_energy_factor_water", -1);

	cout << "Movement_reduction_in_water=" << reader.GetReal("Life properties", "Movement_reduction_in_water", -1) << "\n";
	MOVEMENT_REDUCTION_IN_WATER = reader.GetReal("Life properties", "Movement_reduction_in_water", -1);

	cout << "\nLoading properties of the neural network\n";

	cout << "Adjacent_tiles_radius=" << reader.GetInteger("Network properties", "Adjacent_tiles_radius", -1) << "\n";
	ADJACENT_TILES_RADIUS = reader.GetInteger("Network properties", "Adjacent_tiles_radius", -1);

	cout << "Number_next_entities=" << reader.GetInteger("Network properties", "Number_next_entities", -1) << "\n";
	NUMBER_NEXT_ENTITES = reader.GetInteger("Network properties", "Number_next_entities", -1);

	cout << "Radius_next_entities=" << reader.GetInteger("Network properties", "Radius_next_entities", -1) << "\n";
	RADIUS_NEXT_ENTITIES = reader.GetInteger("Network properties", "Radius_next_entities", -1);

	cout << "Num_layers=" << reader.GetInteger("Network properties", "Num_layers", -1) << "\n";
	NUM_LAYERS = reader.GetInteger("Network properties", "Num_layers", -1);

	INPUT_NEURONS = 3 * (2 * ADJACENT_TILES_RADIUS + 1) * (2 * ADJACENT_TILES_RADIUS + 1)				//Adjecent tile properties (Like Temperature,Food,Number of entites on tile...)
		+ INPUTS_FOR_BODY_PROPERTIES + NUMBER_NEXT_ENTITES * 7											//Number of input properties and properties of N-next entites (Like, size, relative position, color, etc...)
		+ 1;
	HIDDEN_NEURONS = INPUT_NEURONS / 2;
}