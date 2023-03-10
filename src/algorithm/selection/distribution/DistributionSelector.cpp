#include "algorithm/selection/distribution/DistributionSelector.hpp"

#include <cmath>

using PCAGenetic::DistributionSelector;
using PCAGenetic::parentPair;
using PCAGenetic::ParentSelector;
using PCAGenetic::modelVector;

DistributionSelector::DistributionSelector()
{
	distribution = [](int rank, int total) 
	{
		double p = 0.5;
		return p*pow(p, rank); 
	};
}

DistributionSelector::DistributionSelector(std::function<double(int, int)> dist) : distribution(dist) { }

std::unique_ptr<ParentSelector> DistributionSelector::clone() const
{
	return std::unique_ptr<ParentSelector>(new DistributionSelector(distribution));
}

size_t DistributionSelector::makeSelection(const modelVector& models) const
{
	size_t i = 0;
	double selection = (double) rand() / RAND_MAX;
	
	selection -= distribution(i, models.size());
	while (selection > 0 && i < models.size())
	{
		selection -= distribution(i, models.size());
		i++;
	}
	
	return i;
}

//Returns a std::pair of GeneticModels to be combined as parents
parentPair DistributionSelector::selectParents(const modelVector& models, const std::vector<double>& fitnesses)
{
	size_t i1 = makeSelection(models), i2 = makeSelection(models);
	return parentPair(models[i1]->clone(), models[i2]->clone());
}
