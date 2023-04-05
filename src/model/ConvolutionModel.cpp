#include "ConvolutionModel.hpp"

using GeneticModels::GeneticModel;
using GeneticModels::ModelOutputData;
using GeneticModels::ConvolutionModel;

std::unique_ptr<GeneticModel> ConvolutionModel::clone() const
{
	return std::unique_ptr<GeneticModel>(new ConvolutionModel());
}
			
std::unique_ptr<ModelOutputData> ConvolutionModel::evaluate(ModelInputData&)
{
	return std::unique_ptr<ModelOutputData>();
}

std::vector<double> ConvolutionModel::getParameters() const
{
	return std::vector<double>();
}

void ConvolutionModel::setParameters(std::vector<double>)
{
	
}

int ConvolutionModel::getInputDataLength() const
{
	return 0;
}

int ConvolutionModel::getOutputDataLength() const
{
	return 0;
}
