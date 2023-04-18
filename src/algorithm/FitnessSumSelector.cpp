#include "FitnessSumSelector.hpp"
#include <memory>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>

using namespace GeneticModels;
using namespace PCAGenetic;

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

std::pair<ModelHandle, ModelHandle> FitnessSumSelector::selectParents(const std::vector<ModelHandle>& models, const std::vector<double>& fitnesses)
{
	double sum = std::accumulate(fitnesses.begin(), fitnesses.end(), 0.0);
	double p = 0.0;

	std::vector<double> probDensity(fitnesses.size());
	std::transform(fitnesses.begin(), fitnesses.end(), probDensity.begin(),
		[&](double fitness){ p += fitness / sum; return p;});

	size_t i1 = probDensitySelect(probDensity), i2 = probDensitySelect(probDensity);
	return std::pair<ModelHandle, ModelHandle>(models[i1], models[i2]);
}

JSONObject FitnessSumSelector::toJSON() const
{
	JSONObject obj;
	obj.addString("typename", "FitnessSumSelector");
	return obj;
}
