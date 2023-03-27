#include "algorithm/selection/best/BestFitnessSelector.hpp"
#include <memory>

using namespace GeneticModels;
using namespace PCAGenetic;

std::unique_ptr<ParentSelector> BestFitnessSelector::clone() const
{
	return std::unique_ptr<ParentSelector>(new BestFitnessSelector());
}

//For now select the best model as a parent every time
//TODO: Should this selector pick the first and second best? Or just the best?
std::pair<ModelHandle, ModelHandle> BestFitnessSelector::selectParents(const std::vector<ModelHandle>& models, const std::vector<double>&)
{
	return std::pair<ModelHandle, ModelHandle>(ModelHandle(models.back()->clone()), ModelHandle(models.back()->clone()));
}

JSONObject BestFitnessSelector::toJSON() const
{
	JSONObject obj;
	obj.addString("typename", "BestFitnessSelector");
	return obj;
}
