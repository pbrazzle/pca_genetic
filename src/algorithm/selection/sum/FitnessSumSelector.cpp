#include "algorithm/selection/sum/FitnessSumSelector.hpp"
#include <memory>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>

using PCAGenetic::FitnessSumSelector;
using PCAGenetic::ParentSelector;
using PCAGenetic::parentPair;

FitnessSumSelector::FitnessSumSelector() { }

std::unique_ptr<ParentSelector> FitnessSumSelector::clone() const
{
	return std::unique_ptr<ParentSelector>(new FitnessSumSelector());
}

size_t probDensitySelect(const std::vector<double>& probDensity)
{
	double selection = (double) rand() / RAND_MAX;
	
	size_t i = 0;
	while (selection > probDensity[i] && i < probDensity.size()-1) i++;
	return i;
}

parentPair FitnessSumSelector::selectParents(const modelVector &models, const std::vector<double> &fitnesses)
{
	double sum = std::accumulate(fitnesses.begin(), fitnesses.end(), 0.0);
	double p = 0.0;

	std::vector<double> probDensity(fitnesses.size());
	std::transform(fitnesses.begin(), fitnesses.end(), probDensity.begin(),
		[&](double fitness){ p += fitness / sum; return p;});

	size_t i1 = probDensitySelect(probDensity), i2 = probDensitySelect(probDensity);
	return parentPair(models[i1]->clone(), models[i2]->clone());
}
