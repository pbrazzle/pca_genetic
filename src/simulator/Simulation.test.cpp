#include "Simulation.hpp"

#include "algorithm/GeneticAlgorithm.hpp"
#include "algorithm/GeneticAlgorithmFactory.hpp"
#include "model/LinearGeneticModel.hpp"
#include "model/NeuralModel.hpp"
#include "model/ModelInputDataVector.hpp"
#include "model/ModelOutputDataVector.hpp"
#include "GeneticTypes.hpp"

#include <iostream>
#include <cassert>

#include <catch2/catch_test_macros.hpp>

using namespace PCAGenetic;
using namespace GeneticModels;
using namespace GeneticSimulator;

TEST_CASE("Simulate LinearGeneticModel Identity", "[Simulation]")
{
	srand(time(NULL));

	GeneticAlgorithm alg = makeBasicAlgorithm();
	alg.setParamRange(0.05);
	std::unique_ptr<GeneticModel> modelTemplate(new LinearGeneticModel(3, { 1, 0, 0, 0, 1, 0, 0, 0, 1 }));
	std::vector<trainingItem> trainingData;

	std::unique_ptr<ModelInputData> inData = std::make_unique<ModelInputDataVector>(ModelInputDataVector({ 1, 1, 1 }));
	std::unique_ptr<ModelOutputData> outData = std::make_unique<ModelOutputDataVector>(ModelOutputDataVector({ 2, 2, 2 }));
	trainingData.push_back({ std::move(inData), std::move(outData) });

	Simulation sim("Test Sim", alg, std::move(modelTemplate), std::move(trainingData), 10);

	JSONObject simJSON = sim.toJSON();
	std::cout << simJSON.asJSON() << '\n';

	Simulation readSim;
	readSim.fromJSON(simJSON);

	readSim.run();

	double startBestFitness = readSim.getBestFitnesses().front();
	double endBestFitness = readSim.getBestFitnesses().back();

	REQUIRE(endBestFitness >= startBestFitness);
}

TEST_CASE("Simulate NeuralModel Identity", "[Simulation]")
{
	srand(time(NULL));

	GeneticAlgorithm alg = makeBasicAlgorithm();
	alg.setParamRange(0.05);
	std::unique_ptr<GeneticModel> modelTemplate(new NeuralModel({ 3, 5, 3}));
	std::vector<trainingItem> trainingData;

	std::unique_ptr<ModelInputData> inData = std::make_unique<ModelInputDataVector>(ModelInputDataVector({ 1, 1, 1 }));
	std::unique_ptr<ModelOutputData> outData = std::make_unique<ModelOutputDataVector>(ModelOutputDataVector({ 1, 1, 1 }));
	trainingData.push_back({ std::move(inData), std::move(outData) });

	Simulation sim("Test Sim", alg, std::move(modelTemplate), std::move(trainingData), 10);

	JSONObject simJSON = sim.toJSON();
	std::cout << simJSON.asJSON() << '\n';

	Simulation readSim;
	readSim.fromJSON(simJSON);

	readSim.run();

	double startBestFitness = readSim.getBestFitnesses().front();
	double endBestFitness = readSim.getBestFitnesses().back();

	REQUIRE(endBestFitness >= startBestFitness);
}