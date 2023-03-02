#include "algorithm/selection/best/BestFitnessSelector.hpp"
#include <memory>

using PCAGenetic::BestFitnessSelector;
using PCAGenetic::parentPair;
using PCAGenetic::ParentSelector;

std::unique_ptr<ParentSelector> BestFitnessSelector::clone() const
{
	return std::unique_ptr<ParentSelector>(new BestFitnessSelector());
}

//For now select the best model as a parent every time
//TODO: Should this selector pick the first and second best? Or just the best?
parentPair BestFitnessSelector::selectParents(const modelVector& models, const std::vector<double>& fitnesses)
{
	return parentPair(models.back()->clone(), models.back()->clone());
}
