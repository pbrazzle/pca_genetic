#include "algorithm/fitness/distance/DistanceCalculator.hpp"
#include <memory>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

using PCAGenetic::DistanceCalculator;
using PCAGenetic::FitnessCalculator;

DistanceCalculator::DistanceCalculator() { }

std::unique_ptr<FitnessCalculator> DistanceCalculator::clone() const
{
	return std::unique_ptr<FitnessCalculator>(new DistanceCalculator());
}

double max_distance = 10000;

std::vector<double> DistanceCalculator::calculateFitnesses(const std::vector<trainingItem> &trainingData, const std::vector<std::unique_ptr<GeneticModel>> &models)
{
	std::vector<double> fitnesses(models.size());

	for (int i = 0; i < models.size(); i++)
	{
		double distance = 0.0;
		for (int j = 0; j < trainingData.size(); j++)
		{
			auto result = models[i]->evaluate(*trainingData[j].first);
			distance += result->distance(*trainingData[j].second);
		}
		//Invert value so better models have higher fitness scores
		fitnesses[i] = 1/distance;
	}
	
	/*
	double max = *std::max_element(fitnesses.begin(), fitnesses.end());
	if (max < max_distance) 
	{
		std::cout << "max_distance reduced to " << max << '\n';
		max_distance = max;
	}
	std::transform(fitnesses.begin(), fitnesses.end(), fitnesses.begin(),
			[&](double fitness){ double val = max_distance-fitness; return (val>0)?val:0; });
	*/

	return fitnesses;
}
