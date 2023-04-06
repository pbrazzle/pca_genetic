#include "json/JSONFile.hpp"
#include "simulator/Simulation.hpp"

#include <time.h>

using JSON_IO::JSONFileReader;
using GeneticSimulator::Simulation;

int main(int argc, char* argv[])
{
	srand((unsigned int) time(NULL));

	std::string filename(argv[1]);
	JSONFileReader jsonReader(filename);
	auto obj = jsonReader.read();

	Simulation sim;
	sim.fromJSON(obj);
	sim.run();
	
	return 0;
}
