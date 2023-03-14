#include "algorithm/GeneticAlgorithmParameters.hpp"

#include <iostream>

using namespace PCAGenetic;
using namespace GeneticJSON;

int main()
{
	GeneticAlgorithmParameters params;
	params.generationSize = 100;
	params.mutationChance = 0.01;
	params.mutationSize = 0.01;
	params.paramRange = 1;
	params.elitism = 0.1;
	
	auto paramJSON = params.toJSON();
	std::cout << "Blank params as JSON: " << paramJSON.asJSON() << '\n';
}