#include "GeneticModel.hpp"

using namespace GeneticModels;
using namespace PCAGenetic;

std::unique_ptr<GeneticModel> GeneticModel::combine(const GeneticModel& spouse, ParentCombiner& combiner)
{
	auto newParams = combiner.combineParameters(getParameters(), spouse.getParameters());
	
	std::unique_ptr<GeneticModel> child = clone();
	child->setParameters(newParams);
	return std::move(child);
}

std::unique_ptr<GeneticModel> GeneticModel::copyWithOffset(double maxOffset) const
{
	std::unique_ptr<GeneticModel> copy = clone();
	auto params = copy->getParameters();
	
	for (int i = 0; i < params.size(); i++)
	{
		params[i] += maxOffset*(2*(rand() % 2) - 1);
	}
	
	copy->setParameters(params);
	
	return std::move(copy);
}

void GeneticModel::mutate(double mutChance, double mutSize)
{
	auto params = getParameters();
	
	for (int i = 0; i < params.size(); i++)
	{
		if (((double) rand() / RAND_MAX) < mutChance)
		{
			params[i] += mutSize*params[i]*(2*(rand() % 2) - 1);
		}
	}
	
	setParameters(params);
}