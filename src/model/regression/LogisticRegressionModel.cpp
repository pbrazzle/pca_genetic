#include "model/regression/LogisticRegressionModel.hpp"

using PCAGenetic::GeneticModel;
using PCAGenetic::ModelOutputData;
using PCAGenetic::LogisticRegressionModel;

std::unique_ptr<GeneticModel> LogisticRegressionModel::clone() const
{
	return std::unique_ptr<GeneticModel>(new LogisticRegressionModel());
}
			
std::unique_ptr<ModelOutputData> LogisticRegressionModel::evaluate(ModelInputData&)
{
	return std::unique_ptr<ModelOutputData>();
}

std::vector<double> LogisticRegressionModel::getParameters() const
{
	return std::vector<double>();
}

void LogisticRegressionModel::setParameters(std::vector<double>)
{
	
}