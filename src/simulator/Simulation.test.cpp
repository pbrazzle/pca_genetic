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

#include "model/ConvolutionModel.hpp"
#include "model/InterconnectedGeneticModel.hpp"

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

TEST_CASE("Simulate Convolution Identity", "[Simulation]")
{
	srand(time(NULL));

	GeneticAlgorithm alg = makeBasicAlgorithm();
	alg.setParamRange(0.05);
	std::unique_ptr<GeneticModel> modelTemplate(new ConvolutionModel(5, 5, 3, 3, { 1, 1, 1, 1, 1, 1, 1, 1, 1 }));
	std::vector<trainingItem> trainingData;

	std::unique_ptr<ModelInputData> inData = std::make_unique<ModelInputDataVector>(ModelInputDataVector(std::vector<double>(25, 1.0)));
	std::unique_ptr<ModelOutputData> outData = std::make_unique<ModelOutputDataVector>(ModelOutputDataVector(std::vector<double>(9, 1.0)));
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

TEST_CASE("Simulate InterconnectedGeneticModel Identity", "[Simulation]")
{
	srand(time(NULL));

	GeneticAlgorithm alg = makeBasicAlgorithm();
	alg.setParamRange(0.05);
	
	std::vector<trainingItem> trainingData;

	std::vector<std::vector<std::unique_ptr<GeneticModel>>> layers;
	std::vector<std::unique_ptr<GeneticModel>> layer1;
	layer1.emplace_back(std::make_unique<LinearGeneticModel>(3, std::vector<double>({ 1, 1, 1, 1, 1, 1, 1, 1, 1 })));
	std::vector<std::unique_ptr<GeneticModel>> layer2;
	layer2.emplace_back(std::make_unique<LinearGeneticModel>(3, std::vector<double>({ 1, 1, 1, 1, 1, 1, 1, 1, 1 })));
	layers.emplace_back(std::move(layer1));
	layers.emplace_back(std::move(layer2));
	std::unique_ptr<GeneticModel> modelTemplate = std::make_unique<InterconnectedGeneticModel>(std::move(layers));

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