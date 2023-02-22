#include "GeneticAlgorithm.hpp"
#include "LinearGeneticModel.hpp"

#include <cstdlib>
#include <numeric>
#include <algorithm>

using PCAGenetic::GeneticAlgorithm;
using PCAGenetic::GeneticModel;
using PCAGenetic::trainingItem;

const unsigned int GENERATION_SIZE = 100;

GeneticAlgorithm::GeneticAlgorithm() { }

GeneticAlgorithm::GeneticAlgorithm(std::unique_ptr<FitnessCalculator> fc, std::unique_ptr<ParentSelector> ps, std::unique_ptr<ParentCombiner> pc)
{ 
	fitnessCalc = std::move(fc);
	parentSelect = std::move(ps);
	parentComb = std::move(pc);
}

GeneticAlgorithm::GeneticAlgorithm(GeneticAlgorithm& alg)
{
	fitnessCalc = std::move(alg.fitnessCalc->clone());
	parentSelect = std::move(alg.parentSelect->clone());
	parentComb = std::move(alg.parentComb->clone());
}

GeneticAlgorithm& GeneticAlgorithm::operator=(const GeneticAlgorithm& other)
{
	fitnessCalc = std::move(other.fitnessCalc->clone());
	parentComb = std::move(other.parentComb->clone());
	parentSelect = std::move(other.parentSelect->clone());
	return *this;
}

void GeneticAlgorithm::train(const GeneticModel& modelTemplate, std::vector<trainingItem> td, int generations)
{
	trainingData = std::move(td);
	models.clear();
	models.reserve(GENERATION_SIZE);

	for (int i =0; i < GENERATION_SIZE; i++)
	{
		std::vector<double> params = modelTemplate.getParameters();
		for (int j = 0; j < params.size(); j++)
		{
			params[j] = 2000*((double) rand() / RAND_MAX) - 1000;
		}
		std::unique_ptr<GeneticModel> model = modelTemplate.clone();
		model->setParameters(params);
		models.emplace_back(std::move(model));
	}

	calculateFitnesses();
	continueTraining(generations);
}

void GeneticAlgorithm::continueTraining(int generations)
{
	for (int i = 0; i < generations; i++) runGeneration();
}

void GeneticAlgorithm::calculateFitnesses()
{
	fitnesses = fitnessCalc->calculateFitnesses(trainingData, models);

	std::vector<size_t> sortedIndices(fitnesses.size(), 0);
	std::iota(sortedIndices.begin(), sortedIndices.end(), 0);

	std::sort(sortedIndices.begin(), sortedIndices.end(), 
			[&](size_t i1, size_t i2) { return fitnesses[i1] < fitnesses[i2]; });
	std::sort(fitnesses.begin(), fitnesses.end());
	
	modelVector sortedModels(models.size());
	for (size_t i : sortedIndices) sortedModels.emplace_back(models[i]->clone());
	models = std::move(models);
}

void GeneticAlgorithm::runGeneration()
{
	modelVector newModels;

	for (int i = 0; i < GENERATION_SIZE; i++)
	{
		parentPair parents = parentSelect->selectParents(models, fitnesses);
		std::vector<double> combined = parentComb->combineParameters(parents.first->getParameters(), parents.second->getParameters());

		std::unique_ptr<GeneticModel> child = models[0]->clone();
		child->setParameters(combined);
		newModels.emplace_back(std::move(child));
	}

	models = std::move(newModels);
	calculateFitnesses();
}

std::unique_ptr<GeneticModel> GeneticAlgorithm::getBestModel()
{
	return models.back()->clone();
}
