#include "BasicGeneticAlgorithm.hpp"

#include <memory>
#include <utility>

#include "LinearGeneticModel.hpp"

using PCAGenetic::BasicGeneticAlgorithm;
using PCAGenetic::GeneticModel;

const unsigned int GENERATION_SIZE = 100;

BasicGeneticAlgorithm::BasicGeneticAlgorithm() { }

void BasicGeneticAlgorithm::calculateFitnesses()
{
	fitnesses.clear();
	for (int i = 0; i < GENERATION_SIZE; i++)
	{
		std::unique_ptr<GeneticModel> model = models[i]->clone();
		double fitness = 0;
		for (int j = 0; j < trainingData.size(); j++)
		{
			std::unique_ptr<ModelOutputData> modelResult = model->evaluate(*trainingData[j].first);
			fitness += trainingData[j].second->distance(*modelResult);
		}
		fitnesses.push_back(fitness);
	}
}

//TODO Implement single crossing combination
std::vector<double> BasicGeneticAlgorithm::combineParameters(std::vector<double> p1, std::vector<double> p2)
{
	return p1;
}

//TODO Select parents based on fitness scores
std::pair<std::unique_ptr<GeneticModel>, std::unique_ptr<GeneticModel>> BasicGeneticAlgorithm::selectParents()
{
	std::pair<std::unique_ptr<GeneticModel>, std::unique_ptr<GeneticModel>> parents;

	parents.first = models[0]->clone();
	parents.second = models[0]->clone();

	return std::move(parents);
}

void BasicGeneticAlgorithm::runGeneration()
{
	calculateFitnesses();

	std::vector<std::unique_ptr<GeneticModel>> newGeneration;

	for (int i = 0; i < GENERATION_SIZE; i++)
	{
		std::unique_ptr<GeneticModel> child = models[0]->clone();

		std::pair<std::unique_ptr<GeneticModel>, std::unique_ptr<GeneticModel>> parents = selectParents();
		std::vector<double> newParams = combineParameters(parents.first->getParameters(), parents.second->getParameters());
		child->setParameters(newParams);

		newGeneration.push_back(std::move(child));
	}

	models = std::move(newGeneration);
}

void BasicGeneticAlgorithm::train(std::unique_ptr<GeneticModel> modelTemplate, std::vector<trainingItem> tData, int generations)
{
	trainingData = std::move(tData);

	models.clear();
	for (int i = 0; i < GENERATION_SIZE; i++)
	{
		//TODO give each clone random parameters
		models.push_back(modelTemplate->clone());
	}

	continueTraining(generations);
}

void BasicGeneticAlgorithm::continueTraining(int generations)
{
	for (int i = 0; i < generations; i++) runGeneration();
}

std::unique_ptr<GeneticModel> BasicGeneticAlgorithm::getBestModel()
{
	return std::make_unique<LinearGeneticModel>(0);
}
