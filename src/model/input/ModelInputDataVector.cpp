#include "model/input/ModelInputDataVector.hpp"
#include <memory>

using GeneticModels::ModelInputDataVector;
using GeneticModels::ModelInputData;

ModelInputDataVector::ModelInputDataVector(std::vector<double> d) : data(d) { }

std::unique_ptr<ModelInputData> ModelInputDataVector::clone() const
{
	return std::unique_ptr<ModelInputData>(new ModelInputDataVector(data));
}

std::vector<double> ModelInputDataVector::getData() { return data; }
