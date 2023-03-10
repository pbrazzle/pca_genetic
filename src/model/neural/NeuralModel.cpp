#include "model/neural/NeuralModel.hpp"

using PCAGenetic::GeneticModel;
using PCAGenetic::ModelOutputData;
using PCAGenetic::NeuralModel;

std::unique_ptr<GeneticModel> NeuralModel::clone() const
{
	return std::unique_ptr<GeneticModel>(new NeuralModel());
}
			
std::unique_ptr<ModelOutputData> NeuralModel::evaluate(ModelInputData&)
{
	return std::unique_ptr<ModelOutputData>();
}

std::vector<double> NeuralModel::getParameters() const
{
	return std::vector<double>();
}

void NeuralModel::setParameters(std::vector<double>)
{
	
}