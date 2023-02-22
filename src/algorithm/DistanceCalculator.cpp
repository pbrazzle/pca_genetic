#include "DistanceCalculator.hpp"
#include <memory>
#include <vector>

using PCAGenetic::DistanceCalculator;
using PCAGenetic::FitnessCalculator;

DistanceCalculator::DistanceCalculator() { }

std::unique_ptr<FitnessCalculator> DistanceCalculator::clone() const
{
	return std::unique_ptr<FitnessCalculator>(new DistanceCalculator());
}

std::vector<double> DistanceCalculator::calculateFitnesses(const std::vector<trainingItem> &trainingData, const std::vector<std::unique_ptr<GeneticModel>> &models)
{
	return std::vector<double>();
}
