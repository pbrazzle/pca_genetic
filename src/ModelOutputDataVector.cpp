#include "ModelOutputDataVector.hpp"

#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <functional>
#include <cmath>
#include <numeric>

using PCAGenetic::ModelOutputDataVector;

ModelOutputDataVector::ModelOutputDataVector(std::vector<double> d) : data(d) { }

double ModelOutputDataVector::distance(ModelOutputData& otherData)
{
	std::vector<double> otherVec = otherData.getData();
	if (otherVec.size() != data.size()) throw std::invalid_argument("ModelOutputDataVector: Data Length is not equal");

	std::vector<double> distances;
	distances.reserve(data.size());

	std::transform(data.begin(), data.end(), otherVec.begin(), std::back_inserter(distances), 
			[](double x, double y)->double { return pow(x-y,2); });

	return pow(std::accumulate(distances.begin(), distances.end(), 0), 0.5);
}

std::vector<double> ModelOutputDataVector::getData() { return data; }
