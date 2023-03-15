#ifndef SIMULATION_FILE_READER
#define SIMULATION_FILE_READER

#include "simulator/Simulation.hpp"

#include <vector>
#include <string>

namespace GeneticSimulator
{
	//Parses Simulation objects from .gen file
	//TODO switch to reading JSON files
	class SimulationFileReader
	{
		public:
			SimulationFileReader();

			std::vector<Simulation> readSimulations(std::string);
	};
}

#endif
