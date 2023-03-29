#include "simulator/Simulation.hpp"

#include "algorithm/GeneticAlgorithm.hpp"
#include "algorithm/GeneticAlgorithmFactory.hpp"
#include "model/LinearGeneticModel.hpp"
#include "GeneticTypes.hpp"

#include <iostream>
#include <cassert>

using namespace PCAGenetic;
using namespace GeneticModels;
using namespace GeneticSimulator;

int main()
{
	GeneticAlgorithm alg = makeBasicAlgorithm();
	std::unique_ptr<GeneticModel> modelTemplate(new LinearGeneticModel(3));
	std::vector<trainingItem> trainingData;
	
	Simulation sim("Test Sim", alg, std::move(modelTemplate), std::move(trainingData), 10);
	
	JSONObject simJSON = sim.toJSON();
	std::cout << simJSON.asJSON() << '\n';
	
	return 0;
}