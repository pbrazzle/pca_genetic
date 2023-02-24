#include "Simulation.hpp"
#include <memory>
#include <iostream>
#include <fstream>
#include <algorithm>

using PCAGenetic::Simulation;

Simulation::Simulation(std::string n, GeneticAlgorithm a, std::unique_ptr<GeneticModel> m, std::vector<trainingItem> td, int g) : name(n), alg(a), generations(g)
{
	modelTemplate = std::move(m);
	trainingData = std::move(td);
}

Simulation::Simulation(const Simulation& other)
{
	alg = other.alg;
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
	alg.train(*modelTemplate, trainingData, generations);
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
}
