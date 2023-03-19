#include "GeneticAlgorithm.hpp"

#include <cstdlib>
#include <numeric>
#include <algorithm>
#include <vector>
#include <iostream>

using PCAGenetic::GeneticAlgorithm;
using PCAGenetic::GeneticModel;
using PCAGenetic::trainingItem;

const bool DEBUG = false;

template <class T>
void LOG(T message)
{
	if (DEBUG)
		std::cout << message;
}

GeneticAlgorithm::GeneticAlgorithm()
{ 
	generationSize = 100;
	mutationChance = 0.1;
	mutationSize = 0.01;
	paramRange = 1;
	elitism = 0.50;
}

GeneticAlgorithm::GeneticAlgorithm(std::unique_ptr<FitnessCalculator> fc, std::unique_ptr<ParentSelector> ps, std::unique_ptr<ParentCombiner> pc) : GeneticAlgorithm()
{ 
	fitnessCalc = std::move(fc);
	parentSelect = std::move(ps);
	parentComb = std::move(pc);
}

GeneticAlgorithm::GeneticAlgorithm(GeneticAlgorithm& alg)
{
	if (alg.fitnessCalc)
		fitnessCalc = std::move(alg.fitnessCalc->clone());
	if (alg.parentSelect)
		parentSelect = std::move(alg.parentSelect->clone());
	if (alg.parentComb)
		parentComb = std::move(alg.parentComb->clone());
	
	for (int i = 0; i < alg.models.size(); i++)
	{
		std::unique_ptr<GeneticModel> copy = alg.models[i]->clone();
		models.emplace_back(std::move(copy));
		fitnesses.push_back(alg.fitnesses[i]);
	}
	
	for (int i = 0; i < alg.trainingData.size(); i++)
	{
		trainingItem item(alg.trainingData[i].first->clone(), alg.trainingData[i].second->clone());
		trainingData.emplace_back(std::move(item));
	}
	
	generationSize = alg.generationSize;
	mutationChance = alg.mutationChance;
	mutationSize = alg.mutationSize;
	paramRange = alg.paramRange;
	
	avgFitnesses = alg.avgFitnesses;
	bestFitnesses = alg.bestFitnesses;
	elitism = alg.elitism;
}

GeneticAlgorithm& GeneticAlgorithm::operator=(const GeneticAlgorithm& alg)
{
	fitnessCalc = std::move(alg.fitnessCalc->clone());
	parentComb = std::move(alg.parentComb->clone());
	parentSelect = std::move(alg.parentSelect->clone());
	
	models.clear();
	fitnesses.clear();
	for (int i = 0; i < alg.models.size(); i++)
	{
		std::unique_ptr<GeneticModel> copy = alg.models[i]->clone();
		models.emplace_back(std::move(copy));
		fitnesses.push_back(alg.fitnesses[i]);
	}
	
	trainingData.clear();
	for (int i = 0; i < alg.trainingData.size(); i++)
	{
		trainingItem item(alg.trainingData[i].first->clone(), alg.trainingData[i].second->clone());
		trainingData.emplace_back(std::move(item));
	}
	
	generationSize = alg.generationSize;
	mutationChance = alg.mutationChance;
	mutationSize = alg.mutationSize;
	paramRange = alg.paramRange;
	
	avgFitnesses = alg.avgFitnesses;
	bestFitnesses = alg.bestFitnesses;
	elitism = alg.elitism;
	return *this;
}

void GeneticAlgorithm::train(const GeneticModel& modelTemplate, std::vector<trainingItem>& td, int generations)
{
	trainingData = std::move(td);
	models.clear();
	models.reserve(generationSize);

	for (int i =0; i < generationSize; i++)
	{
		std::vector<double> params = modelTemplate.getParameters();
		for (int j = 0; j < params.size(); j++)
		{
			params[j] += 2*paramRange*((double) rand() / RAND_MAX) - paramRange;
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

	modelVector sortedModels;
	sortedModels.reserve(models.size());
	for (size_t i : sortedIndices) sortedModels.emplace_back(models[i]->clone());
	models = std::move(sortedModels);
}

std::vector<double> GeneticAlgorithm::mutateParams(const std::vector<double>& params)
{
	std::vector<double> mutated = params;
	for (int i = 0; i < params.size(); i++)
	{
		if (((double) rand() / RAND_MAX) < mutationChance)
			mutated[i] += mutated[i]*mutationSize*((rand() % 3) - 1);
	}
	return mutated;
}

void GeneticAlgorithm::runGeneration()
{
	modelVector newModels;

	int numEliteModels = elitism*generationSize;
	LOG("Saving best "); LOG(numEliteModels); LOG(" models\n");
	for (int i = 0; i < numEliteModels; i++)
	{
		newModels.emplace_back(models[generationSize-1-i]->clone());
	}

	for (int i = 0; i < generationSize-numEliteModels; i++)
	{
		parentPair parents = parentSelect->selectParents(models, fitnesses);
		std::vector<double> combined = parentComb->combineParameters(parents.first->getParameters(), parents.second->getParameters());
		combined = mutateParams(combined);

		std::unique_ptr<GeneticModel> child = models[0]->clone();
		child->setParameters(combined);
		newModels.emplace_back(std::move(child));
	}

	models = std::move(newModels);
	calculateFitnesses();

	double avg_fitness = std::accumulate(fitnesses.begin(), fitnesses.end(), 0.0) / generationSize;
	avgFitnesses.push_back(avg_fitness);
	bestFitnesses.push_back(fitnesses.back());
	LOG("Best fitness: "); LOG(fitnesses.back()); LOG('\n');
}

std::vector<double> GeneticAlgorithm::getAvgFitnesses() const { return avgFitnesses; }

std::unique_ptr<GeneticModel> GeneticAlgorithm::getBestModel()
{
	return models.back()->clone();
}

void GeneticAlgorithm::setGenerationSize(const int& g) { generationSize = g; }
void GeneticAlgorithm::setMutationChance(const double& m) { mutationChance = m; }
void GeneticAlgorithm::setMutationSize(const double& s) { mutationSize = s; }
void GeneticAlgorithm::setParamRange(const double& p) { paramRange = p; }

void GeneticAlgorithm::setEilitism(const double& e) 
{ 
	elitism = e; 
	if (elitism > 1) elitism = 1;
	else if (elitism < 0) elitism = 0;
}

std::vector<double> GeneticAlgorithm::getBestFitnesses() const { return bestFitnesses; }