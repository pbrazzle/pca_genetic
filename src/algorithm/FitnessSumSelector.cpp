#include "FitnessSumSelector.hpp"
#include <memory>

using PCAGenetic::FitnessSumSelector;
using PCAGenetic::ParentSelector;
using PCAGenetic::parentPair;

FitnessSumSelector::FitnessSumSelector() { }

std::unique_ptr<ParentSelector> FitnessSumSelector::clone() const
{
	return std::unique_ptr<ParentSelector>(new FitnessSumSelector());
}

parentPair FitnessSumSelector::selectParents(const modelVector &models, const std::vector<double> &fitnesses)
{
	return parentPair();
}
