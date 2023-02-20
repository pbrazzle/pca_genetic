#include "BasicGeneticAlgorithm.hpp"

#include <memory>
#include <utility>
#include <cstdlib>
#include <time.h>
#include <numeric>
#include <algorithm>
#include <iostream>

#include "LinearGeneticModel.hpp"

using PCAGenetic::BasicGeneticAlgorithm;
using PCAGenetic::GeneticModel;

const unsigned int GENERATION_SIZE = 100;
const double MUTATION_CHANCE = 0.01;

template <typename T>
std::vector<size_t> getSortedIndices(const std::vector<T>&);

template <typename T>
std::vector<std::reference_wrapper<const T>> applyPermutation(const std::vector<T>&, const std::vector<size_t>&);

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

	//This way better models have higher fitness scores
	for (int i = 0; i < fitnesses.size(); i++)
	{
		fitnesses[i] = 1 / fitnesses[i];	
	}

	std::vector<size_t> fitnessIndices = getSortedIndices(fitnesses);

	//Sorting by fitness for easier parent selection
	std::sort(fitnesses.begin(), fitnesses.end());
	auto sortedModels = applyPermutation(models, fitnessIndices);
	std::vector<std::unique_ptr<GeneticModel>> newModels;
	for (auto model : sortedModels)
	{
		newModels.push_back(model.get()->clone());
	}
	models = std::move(newModels);
}

std::vector<double> BasicGeneticAlgorithm::combineParameters(std::vector<double> p1, std::vector<double> p2)
{
	int crossingPos = rand() % p1.size();

	std::vector<double> newParams;
	newParams.reserve(p1.size());

	newParams.insert(newParams.end(), p1.begin(), p1.begin() + crossingPos);
	newParams.insert(newParams.end(), p2.begin() + crossingPos, p2.end());

	for (int i = 0; i < newParams.size(); i++)
	{
		if ((double) rand() / RAND_MAX < MUTATION_CHANCE)
		{
			newParams[i] += 20*((double) rand() / RAND_MAX) - 10;
		}
	}

	return newParams;
}

template <typename T>
std::vector<size_t> getSortedIndices(const std::vector<T>& v)
{
	std::vector<size_t> indices(v.size());
	std::iota(indices.begin(), indices.end(), 0);

	std::sort(indices.begin(), indices.end(),
		[&v](size_t p1, size_t p2) {return v[p1] < v[p2];});

	return indices;	
}

template <typename T>
std::vector<std::reference_wrapper<const T>> applyPermutation(const std::vector<T>& v, const std::vector<size_t>& indices)
{
	std::vector<std::reference_wrapper<const T>> perm;
	perm.reserve(v.size());
	for (auto i : indices)
		perm.emplace_back(std::cref(v[i]));

	return perm;
}

size_t lowestFitnessSelect(std::vector<double> fitnesses)
{
	double sum = std::accumulate(fitnesses.begin(), fitnesses.end(), 0.0);
	std::vector<double> probDensity(fitnesses.size());
	double p = 0.0;
	std::transform(fitnesses.begin(), fitnesses.end(), probDensity.begin(),
		[&p, sum](double fitness){ p += fitness/sum; return p; });

	double selection = (double) rand() / RAND_MAX;
	size_t index = 0;
	while (selection > probDensity[index] && index < probDensity.size()-1) index++;
	return index;	
}

std::pair<std::unique_ptr<GeneticModel>, std::unique_ptr<GeneticModel>> BasicGeneticAlgorithm::selectParents()
{
	std::pair<std::unique_ptr<GeneticModel>, std::unique_ptr<GeneticModel>> parents;

	parents.first = models[lowestFitnessSelect(fitnesses)]->clone();
	parents.second = models[lowestFitnessSelect(fitnesses)]->clone();

	return parents;
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

void BasicGeneticAlgorithm::train(const GeneticModel& modelTemplate, std::vector<trainingItem> tData, int generations)
{
	srand(time(NULL));
	trainingData = std::move(tData);

	models.clear();
	for (int i = 0; i < GENERATION_SIZE; i++)
	{
		std::unique_ptr<GeneticModel> model = modelTemplate.clone();
		std::vector<double> params = model->getParameters();
		for (int j = 0; j < params.size(); j++) params[j] = 2000*((double) rand() / RAND_MAX) - 1000;
		model->setParameters(params);
		models.push_back(std::move(model));
	}

	continueTraining(generations);
}

void BasicGeneticAlgorithm::continueTraining(int generations)
{
	for (int i = 0; i < generations; i++) runGeneration();
}

std::unique_ptr<GeneticModel> BasicGeneticAlgorithm::getBestModel()
{
	return models[0]->clone();
}