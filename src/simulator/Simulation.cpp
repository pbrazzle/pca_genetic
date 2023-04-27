#include "simulator/Simulation.hpp"
#include <memory>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <omp.h>

#include "model/GeneticModelFactory.hpp"

using GeneticSimulator::Simulation;
using namespace JSON_IO;
using namespace GeneticModels;

Simulation::Simulation(std::string n, GeneticAlgorithm a, std::unique_ptr<GeneticModel> m, std::vector<trainingItem> td, int g) : name(n), alg(a), generations(g)
{
	modelTemplate = std::move(m);
	trainingData = std::move(td);
}

Simulation::Simulation(const Simulation& other) : alg(other.alg)
{
	name = other.name;
	modelTemplate = other.modelTemplate->clone();
	generations = other.generations;

	for (int i = 0; i < other.trainingData.size(); i++)
	{
		trainingItem item(other.trainingData[i].first->clone(), other.trainingData[i].second->clone());
		trainingData.emplace_back(std::move(item));
	}
}

void Simulation::run()
{
	trainingItem sampleItem(trainingData[0].first->clone(), trainingData[0].second->clone());

	std::cout << "Running Simulation: " << name << '\n';
	alg.train(*modelTemplate, trainingData, 0);

	generationTimes.clear();
	for (int i = 1; i <= generations; i++)
	{
		double start_time = omp_get_wtime();
		alg.continueTraining(1);
		double gen_time = omp_get_wtime() - start_time;
		std::cout << "Finished generation " << i << '\n';
		std::cout << "Took " << gen_time << " seconds\n";
		generationTimes.push_back(gen_time);

		auto bestModel = alg.getBestModel();
		auto bestResult = bestModel->evaluate(*sampleItem.first);
		std::cout << "Best model output for sample: ";
		for (auto val : bestResult->getData()) std::cout << val << ", ";
		std::cout << '\n';
		
		std::cout << "Current best fitness: " << alg.getBestFitnesses().back() << '\n';
		std::cout << "Current avg fitness: " << alg.getAvgFitnesses().back() << '\n';
	}

	std::cout << "Finished running " << generations << " generations\n";

	std::unique_ptr<GeneticModel> bestModel = alg.getBestModel();

	std::cout << "First training item:\n";
	std::cout << "In: ";
	for (auto val : sampleItem.first->getData()) std::cout << val << ", ";
	std::cout << "\nOut: ";
	for (auto val : sampleItem.second->getData()) std::cout << val << ", ";
	std::cout << "\nBest Model Result:\n";

	std::unique_ptr<ModelOutputData> result = bestModel->evaluate(*sampleItem.first);
	std::cout << "Out: ";
	for (auto val : result->getData()) std::cout << val << ", ";
	std::cout << '\n';
	
	std::replace(name.begin(), name.end(), ' ', '_');
	std::cout << "Writing data to " << name << ".csv\n";
	
	std::ofstream outFile(name + ".csv");

	std::vector<double> avgFits = alg.getAvgFitnesses(), bestFits = alg.getBestFitnesses();
	for (int i = 0; i < avgFits.size(); i++)
	{
		outFile << avgFits[i] << ',' << bestFits[i] << '\n';
	}
	outFile.close();

	std::cout << "Writing timing data to " << name << "_timing.csv\n";
	std::ofstream timingFile(name + "_timing.csv");
	for (double time : generationTimes)
	{
		timingFile << std::to_string(time) << '\n';
	}
	timingFile.close();
}

JSONObject Simulation::toJSON() const
{
	JSONObject obj;
	obj.addString("name", name);
	obj.addInt("generations", generations);
	obj.addObject("algorithm", alg.toJSON());
	obj.addObject("model_template", modelTemplate->toJSON());
	
	std::vector<JSONObject> JSONtrainingData;
	for (int i = 0; i < trainingData.size(); i++)
	{
		JSONObject JSONitem;
		JSONitem.addObject("input", trainingData[i].first->toJSON());
		JSONitem.addObject("output", trainingData[i].second->toJSON());
		JSONtrainingData.push_back(JSONitem);
	}
	
	obj.addArray("training_data", JSONtrainingData);
	
	return obj;
}

void Simulation::fromJSON(const JSONObject& obj)
{
	name = obj["name"].asString();
	generations = obj["generations"].asInt();

	alg.fromJSON(obj["algorithm"]);
	modelTemplate = ModelFromJSON(obj["model_template"]);

	trainingData.clear();
	auto trainingArr = obj["training_data"].asArray();
	for (auto trainingObj : trainingArr)
	{
		auto input = InputDataFromJSON(trainingObj["input"]);
		auto output = OutputDataFromJSON(trainingObj["output"]);

		trainingData.emplace_back(trainingItem(std::move(input), std::move(output)));
	}
}

std::vector<double> Simulation::getBestFitnesses()
{
	return alg.getBestFitnesses();
}

std::vector<double> Simulation::getAvgFitnesses()
{
	return alg.getAvgFitnesses();
}
