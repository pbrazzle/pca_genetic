#include "simulator/SimulationFileReader.hpp"
#include "simulator/Simulation.hpp"

#include <time.h>

using GeneticSimulator::SimulationFileReader;

int main(int argc, char* argv[])
{
	srand((unsigned int) time(NULL));
	SimulationFileReader simReader;

	std::string filename(argv[1]);
	auto simulations = simReader.readSimulations(filename);
	
	for (auto sim : simulations) sim.run();
	
	return 0;
}
