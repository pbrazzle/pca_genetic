#include "algorithm/GeneticAlgorithmParameters.hpp"

#include <iostream>
#include <cassert>

using namespace PCAGenetic;
using namespace GeneticJSON;

int main()
{
	GeneticAlgorithmParameters writeParams;
	writeParams.generationSize = 100;
	writeParams.mutationChance = 0.01;
	writeParams.mutationSize = 0.01;
	writeParams.paramRange = 1;
	writeParams.elitism = 0.1;
	
	auto paramJSON = writeParams.toJSON();
	std::cout << "Params as JSON: " << paramJSON.asJSON() << '\n';
	assert(paramJSON["generationSize"].asInt() == 100);
	assert(paramJSON["mutationChance"].asFloat() == 0.01);
	assert(paramJSON["mutationSize"].asFloat() == 0.01);
	assert(paramJSON["paramRange"].asFloat() == 1);
	assert(paramJSON["elitism"].asFloat() == 0.1);
	
	GeneticAlgorithmParameters readParams;
	readParams.fromJSON(paramJSON);
	
	assert(readParams.generationSize == 100);
	assert(readParams.mutationChance == 0.01);
	assert(readParams.mutationSize == 0.01);
	assert(readParams.paramRange == 1);
	assert(readParams.elitism == 0.1);
}