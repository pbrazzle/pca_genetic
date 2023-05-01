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
	scores = alg.scores;

	std::for_each(alg.trainingData.begin(), alg.trainingData.end(), 
		[&](const auto& item) { trainingData.emplace_back(trainingItem(item.first->clone(), item.second->clone())); });
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

void GeneticAlgorithm::calculateFitnesses()
{
	std::vector<double> fitnessArr(population.size(), 0.0);
	#pragma omp parallel for num_threads(numThreads)
	for (int i = 0; i < population.size(); i++)
	{
		double fitness = 0.0;
		std::for_each(trainingData.begin(), trainingData.end(),
			[&](const auto& trainingItem) { fitness += fitnessCalc->calculateFitness(trainingItem, population[i]); });
		fitnessArr[i] = fitness / trainingData.size();
	}

	scores.replace(fitnessArr);
	population.reorder(scores.getSortedIndices());
	scores.sort();
}

ModelHandle GeneticAlgorithm::createChildModel()
{
	std::pair<ModelHandle, ModelHandle> parents = parentSelect->selectParents(population.asHandleVector(), scores.asVector());

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

	bestFitnesses.push_back(scores.best());
	avgFitnesses.push_back(scores.avg());

	const auto numEliteModels = static_cast<int>(population.size() * elitism);
	const auto numNewModels = generationSize - numEliteModels;
	std::vector<ModelHandle> newModelArr(numNewModels, nullptr);

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
