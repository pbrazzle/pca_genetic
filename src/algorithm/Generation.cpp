#include "algorithm/Generation.hpp"

#include <algorithm>
#include <omp.h>

using namespace PCAGenetic;

Generation::Generation(const int& generationSize, const double& offsetSize, const GeneticModel& modelTemplate) : population(generationSize, modelTemplate, offsetSize)
{
	scores.replace(std::vector<double>(population.size(), 0.0));
}

void PCAGenetic::Generation::score(const std::vector<trainingItem>& trainingData, const FitnessCalculator& fitCalc, const int& numThreads)
{
	std::vector<double> fitnessArr(population.size(), 0.0);

	#pragma omp parallel for num_threads(numThreads)
	for (int i = 0; i < population.size(); i++)
	{
		double fitness = 0.0;
		std::for_each(trainingData.begin(), trainingData.end(),
			[&](const auto& trainingItem) { fitness += fitCalc.calculateFitness(trainingItem, population[i]); });
		fitnessArr[i] = fitness / trainingData.size();
	}

	scores.replace(fitnessArr);
	population.reorder(scores.getSortedIndices());
	scores.sort();
}

PCAGenetic::ModelHandle createChildModel(const Population& pop, const FitnessScores& scores, ParentSelector& parentSelect, ParentCombiner& parentComb, 
										const double& mutationChance, const double& mutationSize)
{
	auto selection = parentSelect.selectParents(pop.asHandleVector(), scores.asVector());

	ModelHandle child(*(selection.first->combine(*selection.second, parentComb)));
	if ((((double)rand()) / RAND_MAX) < 0.05)
		child->mutate(mutationChance, mutationSize);
	return child;
}

void PCAGenetic::Generation::advance(const double& elitism, ParentSelector& parentSelect,
									ParentCombiner& parentComb, const int& numThreads, const double& mutationChance, const double& mutationSize)
{
	const auto numEliteModels = static_cast<int>(population.size() * elitism);
	const auto numNewModels = population.size() - numEliteModels;
	std::vector<ModelHandle> newModelArr(numNewModels);

	#pragma omp parallel for num_threads(numThreads)
	for (int i = 0; i < numNewModels; i++)
	{
		newModelArr[i] = createChildModel(population, scores, parentSelect, parentComb, mutationChance, mutationSize);
	}

	population.cullWithElitism(elitism);
	for (int i = 0; i < numNewModels; i++)
	{
		population.append(newModelArr[i]);
	}
}

double Generation::bestScore() const
{
	return scores.best();
}

double Generation::avgScore() const
{
	return scores.avg();
}

const GeneticModel& Generation::getBestModel() const
{
	return population.back();
}
