#include "SingleCrossingCombiner.hpp"
#include <memory>

using PCAGenetic::SingleCrossingCombiner;
using PCAGenetic::ParentCombiner;

SingleCrossingCombiner::SingleCrossingCombiner() { }

std::unique_ptr<ParentCombiner> SingleCrossingCombiner::clone() const
{
	return std::unique_ptr<ParentCombiner>(new SingleCrossingCombiner());
}

std::vector<double> SingleCrossingCombiner::combineParameters(const std::vector<double> &p1, const std::vector<double> &p2)
{
	return p1;
}
