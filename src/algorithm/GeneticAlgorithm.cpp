#include "GeneticAlgorithm.hpp"

#include <cstdlib>
#include <numeric>
#include <algorithm>
#include <vector>
#include <iterator>
#include <omp.h>

#include "algorithm/GeneticAlgorithmFactory.hpp"
#include "json/JSONFile.hpp"

using namespace GeneticModels;
using namespace PCAGenetic;

unsigned int GeneticAlgorithm::numThreads = 1;

void GeneticAlgorithm::copyStrategies(const GeneticAlgorithm& alg)
{
	if (alg.fitnessCalc)
		fitnessCalc = std::move(alg.fitnessCalc->clone());
	if (alg.parentSelect)
		parentSelect = std::move(alg.parentSelect->clone());
	if (alg.parentComb)
		parentComb = std::move(alg.parentComb->clone());
}

void GeneticAlgorithm::copyData(const GeneticAlgorithm& alg)
{
	population = alg.population;
	fitnesses = alg.fitnesses;

	for (int i = 0; i < alg.trainingData.size(); i++)
	{
		trainingItem item(alg.trainingData[i].first->clone(), alg.trainingData[i].second->clone());
		trainingData.emplace_back(std::move(item));
	}
}

void GeneticAlgorithm::copySettings(const GeneticAlgorithm& alg)
{
	mutationChance = alg.mutationChance;
	mutationSize = alg.mutationSize;

	generationSize = alg.generationSize;
	offsetSize = alg.offsetSize;

	avgFitnesses = alg.avgFitnesses;
	bestFitnesses = alg.bestFitnesses;
	elitism = alg.elitism;
}

void GeneticAlgorithm::copy(const GeneticAlgorithm& alg)
{
	copyStrategies(alg);
	copyData(alg);
	copySettings(alg);
}

GeneticAlgorithm::GeneticAlgorithm(std::unique_ptr<FitnessCalculator> fc, std::unique_ptr<ParentSelector> ps,
                                   std::unique_ptr<ParentCombiner> pc) : GeneticAlgorithm()
{
	generationSize = 100;
	offsetSize = 1;
	mutationChance = 0.1;
	mutationSize = 0.01;
	elitism = 0.50;

	fitnessCalc = std::move(fc);
	parentSelect = std::move(ps);
	parentComb = std::move(pc);
}

GeneticAlgorithm::GeneticAlgorithm(const GeneticAlgorithm& alg) : GeneticAlgorithm()
{
	copy(alg);
}

GeneticAlgorithm& GeneticAlgorithm::operator=(const GeneticAlgorithm& alg)
{
	copy(alg);
	return *this;
}

void GeneticAlgorithm::initializeGeneration(const GeneticModel& modelTemplate)
{
	population = Population(generationSize, modelTemplate, offsetSize);
}

void GeneticAlgorithm::train(const GeneticModel& modelTemplate, std::vector<trainingItem>& td, int generations)
{
	bestFitnesses.clear();
	avgFitnesses.clear();
	initializeGeneration(modelTemplate);
	trainingData = std::move(td);
	continueTraining(generations);
}

void GeneticAlgorithm::continueTraining(int generations)
{
	for (int i = 0; i < generations; i++) runGeneration();
}

std::vector<size_t> GeneticAlgorithm::getSortedFitnessIndices()
{
	std::vector<size_t> sortedIndices(fitnesses.size(), 0);
	std::iota(sortedIndices.begin(), sortedIndices.end(), 0);

	std::sort(sortedIndices.begin(), sortedIndices.end(),
	          [&](size_t i1, size_t i2) { return fitnesses[i1] < fitnesses[i2]; });
	std::sort(fitnesses.begin(), fitnesses.end());
	return sortedIndices;
}

void GeneticAlgorithm::reorderModels(std::vector<size_t> indices)
{
	population.reorder(indices);
}

void GeneticAlgorithm::calculateFitnesses()
{
	fitnesses.clear();

	auto fitnessArr = new double[population.size()];
	#pragma omp parallel for num_threads(numThreads)
	for (int i = 0; i < population.size(); i++)
	{
		double fitness = 0;
		for (int j = 0; j < trainingData.size(); j++)
		{
			fitness += fitnessCalc->calculateFitness(trainingData[j], population[i]);
		}
		fitnessArr[i] = fitness / trainingData.size();
	}

	fitnesses.insert(fitnesses.end(), &fitnessArr[0], &fitnessArr[population.size()]);
	auto sortedIndices = getSortedFitnessIndices();
	reorderModels(sortedIndices);
}

void GeneticAlgorithm::recordFitness()
{
	double avg_fitness = std::accumulate(fitnesses.begin(), fitnesses.end(), 0.0) / population.size();
	avgFitnesses.push_back(avg_fitness);
	bestFitnesses.push_back(fitnesses.back());
}

ModelHandle GeneticAlgorithm::createChildModel()
{
	std::pair<ModelHandle, ModelHandle> parents = parentSelect->selectParents(population.asHandleVector(), fitnesses);

	ModelHandle child(*(parents.first->combine(*parents.second, *parentComb)));
	if ((((double) rand()) / RAND_MAX) < 0.05)
		child->mutate(mutationChance, mutationSize);
	return child;
}

GeneticAlgorithm::GeneticAlgorithm()
{
	readThreadFile();
}

void GeneticAlgorithm::readThreadFile()
{
	JSONFileReader threadFileReader("config.json");
	auto threadObj = threadFileReader.read();
	if (!threadObj) return;
	numThreads = threadObj["numThreads"].asInt();
}

void GeneticAlgorithm::runGeneration()
{
	calculateFitnesses();

	bestFitnesses.push_back(fitnesses.back());
	avgFitnesses.push_back(std::accumulate(fitnesses.begin(), fitnesses.end(), 0.0) / fitnesses.size());

	const auto numEliteModels = static_cast<int>(population.size() * elitism);
	const auto numNewModels = generationSize - numEliteModels;
	const auto newModelArr = new ModelHandle[numNewModels];

#pragma omp parallel for num_threads(numThreads)
	for (int i = 0; i < numNewModels; i++)
	{
		newModelArr[i] = createChildModel();
	}

	population.cullWithElitism(elitism);
	for (int i = 0; i < numNewModels; i++)
	{
		population.append(newModelArr[i]);
	}
	delete[] newModelArr;
}

std::vector<double> GeneticAlgorithm::getAvgFitnesses() const { return avgFitnesses; }

std::unique_ptr<GeneticModel> GeneticAlgorithm::getBestModel()
{
	return population.back().clone();
}

void GeneticAlgorithm::setGenerationSize(const int& g) { generationSize = g; }
void GeneticAlgorithm::setMutationChance(const double& m) { mutationChance = m; }
void GeneticAlgorithm::setMutationSize(const double& s) { mutationSize = s; }
void GeneticAlgorithm::setParamRange(const double& p) { offsetSize = p; }

void GeneticAlgorithm::setEilitism(const double& e)
{
	elitism = e;
	if (elitism > 1) elitism = 1;
	else if (elitism < 0) elitism = 0;
}

std::vector<double> GeneticAlgorithm::getBestFitnesses() const { return bestFitnesses; }

JSONObject GeneticAlgorithm::toJSON() const
{
	JSONObject obj;

	//Add settings
	obj.addInt("generationSize", generationSize);
	obj.addFloat("offsetSize", offsetSize);
	obj.addFloat("mutationSize", mutationSize);
	obj.addFloat("mutationChance", mutationChance);
	obj.addFloat("elitism", elitism);

	//Add strategies
	if (fitnessCalc)
		obj.addObject("FitnessCalculator", fitnessCalc->toJSON());
	else
		obj.addObject("FitnessCalculator", JSONObject());
	if (parentSelect)
		obj.addObject("ParentSelector", parentSelect->toJSON());
	else
		obj.addObject("ParentSelector", JSONObject());
	if (parentComb)
		obj.addObject("ParentCombiner", parentComb->toJSON());
	else
		obj.addObject("ParentCombiner", JSONObject());

	return obj;
}

void GeneticAlgorithm::fromJSON(const JSONObject& obj)
{
	generationSize = obj["generationSize"].asInt();
	offsetSize = obj["offsetSize"].asFloat();
	mutationChance = obj["mutationChance"].asFloat();
	mutationSize = obj["mutationSize"].asFloat();
	elitism = obj["elitism"].asFloat();

	fitnessCalc = FitCalcFromJSON(obj["FitnessCalculator"]);
	parentSelect = ParentSelectFromJSON(obj["ParentSelector"]);
	parentComb = ParentCombFromJSON(obj["ParentCombiner"]);
}
