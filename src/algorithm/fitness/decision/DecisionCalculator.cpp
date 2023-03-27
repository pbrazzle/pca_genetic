#include "algorithm/fitness/decision/DecisionCalculator.hpp"

#include <iterator>
#include <algorithm>

using PCAGenetic::DecisionCalculator;
using PCAGenetic::FitnessCalculator;
using PCAGenetic::trainingItem;
using PCAGenetic::GeneticModel;

using namespace GeneticJSON;

DecisionCalculator::DecisionCalculator() { }

std::unique_ptr<FitnessCalculator> DecisionCalculator::clone() const
{
	return std::unique_ptr<FitnessCalculator>(new DecisionCalculator());
}

std::vector<double> DecisionCalculator::calculateFitnesses(const std::vector<trainingItem>& trainingData, const std::vector<std::unique_ptr<GeneticModel>>& models)
{
	std::vector<double> fitnesses;
	fitnesses.reserve(models.size());
	
	for (int i = 0; i < models.size(); i++)
	{
		double fitness = 0;
		for (int j = 0; j < trainingData.size(); j++)
		{
			auto result = models[i]->evaluate(*trainingData[j].first);
			auto resultData = result->getData();
			auto expectedData = trainingData[j].second->getData();
			
			//Get index of max element (max element is the 'decision' of the model)
			auto resultDecision = std::distance(resultData.begin(), std::max_element(resultData.begin(), resultData.end()));
			auto expectedDecision = std::distance(expectedData.begin(), std::max_element(expectedData.begin(), expectedData.end()));
			
			if (resultDecision == expectedDecision) fitness += 1.0 / trainingData.size();
		}
		fitnesses.push_back(fitness);
	}
	
	return fitnesses;
}

std::vector<double> DecisionCalculator::calculateFitnesses(const std::vector<trainingItem>& trainingData, const std::vector<ModelHandle>& models)
{
	std::vector<double> fitnesses;
	fitnesses.reserve(models.size());
	
	for (int i = 0; i < models.size(); i++)
	{
		double fitness = 0;
		for (int j = 0; j < trainingData.size(); j++)
		{
			auto result = models[i]->evaluate(*trainingData[j].first);
			auto resultData = result->getData();
			auto expectedData = trainingData[j].second->getData();
			
			//Get index of max element (max element is the 'decision' of the model)
			auto resultDecision = std::distance(resultData.begin(), std::max_element(resultData.begin(), resultData.end()));
			auto expectedDecision = std::distance(expectedData.begin(), std::max_element(expectedData.begin(), expectedData.end()));
			
			if (resultDecision == expectedDecision) fitness += 1.0 / trainingData.size();
		}
		fitnesses.push_back(fitness);
	}
	
	return fitnesses;
}

JSONObject DecisionCalculator::toJSON() const
{
	JSONObject obj;

	obj.addString("typename", "DistanceCalculator");

	return obj;
}