#include "SingleCrossingCombiner.hpp"
#include <memory>

using PCAGenetic::SingleCrossingCombiner;
using PCAGenetic::ParentCombiner;
using namespace JSON_IO;

SingleCrossingCombiner::SingleCrossingCombiner() { }

std::unique_ptr<ParentCombiner> SingleCrossingCombiner::clone() const
{
	return std::unique_ptr<ParentCombiner>(new SingleCrossingCombiner());
}

std::vector<double> SingleCrossingCombiner::combineParameters(const std::vector<double> &p1, const std::vector<double> &p2)
{
	size_t crossingIndex = rand() % p1.size();

	std::vector<double> newParams;
	newParams.reserve(p1.size());
	newParams.insert(newParams.end(), p1.begin(), p1.begin()+crossingIndex);
	newParams.insert(newParams.end(), p2.begin()+crossingIndex, p2.end());

	return newParams;
}

JSONObject SingleCrossingCombiner::toJSON() const
{
	JSONObject obj;
	obj.addString("typename", "SingleCrossingCombiner");
	return obj;
}
