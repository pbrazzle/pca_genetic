#include "algorithm/combination/random/RandomCrossingCombiner.hpp"
#include <memory>

using PCAGenetic::RandomCrossingCombiner;
using PCAGenetic::ParentCombiner;

RandomCrossingCombiner::RandomCrossingCombiner() : RandomCrossingCombiner(0.5) { }

RandomCrossingCombiner::RandomCrossingCombiner(double c) : crossingChance(c) { }

std::unique_ptr<ParentCombiner> RandomCrossingCombiner::clone() const
{
	return std::unique_ptr<ParentCombiner>(new RandomCrossingCombiner());
}

std::vector<double> RandomCrossingCombiner::combineParameters(const std::vector<double>& p1, const std::vector<double>& p2)
{
	std::vector<double> newParams(p1.size());

	bool using1 = true;
	for (int i = 0; i < p1.size(); i++)
	{
		if (using1) newParams[i] = p1[i];
		else newParams[i] = p2[i];

		double randNum = (double) rand() / RAND_MAX;
		if (randNum < crossingChance) using1 = !using1;
	}

	return newParams;
}
