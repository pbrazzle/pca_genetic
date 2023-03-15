#include "model/downsample/DownSamplingModel.hpp"

using GeneticModels::GeneticModel;
using GeneticModels::ModelOutputData;
using GeneticModels::DownSamplingModel;

std::unique_ptr<GeneticModel> DownSamplingModel::clone() const
{
	return std::unique_ptr<GeneticModel>(new DownSamplingModel());
}
			
std::unique_ptr<ModelOutputData> DownSamplingModel::evaluate(ModelInputData&)
{
	return std::unique_ptr<ModelOutputData>();
}

std::vector<double> DownSamplingModel::getParameters() const
{
	return std::vector<double>();
}

void DownSamplingModel::setParameters(std::vector<double>)
{
	
}