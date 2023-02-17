#include "LinearGeneticModel.hpp"

#include "ModelOutputDataVector.hpp"

#include <stdexcept>

using PCAGenetic::LinearGeneticModel;
using PCAGenetic::GeneticModel;
using PCAGenetic::ModelOutputData;
using PCAGenetic::ModelOutputDataVector;

LinearGeneticModel::LinearGeneticModel(int d) : dataLength(d)
{
	parameters = std::vector<double>(dataLength*dataLength, 0);
}

LinearGeneticModel::LinearGeneticModel(int d, std::vector<double> p) : dataLength(d)
{
	if (p.size() != dataLength*dataLength) throw std::invalid_argument("LinearGeneticModel: Incorrect number of parameters");

	parameters = p;
}

std::unique_ptr<GeneticModel> LinearGeneticModel::clone() const
{
	return std::make_unique<LinearGeneticModel>(dataLength, parameters);
}

std::unique_ptr<ModelOutputData> LinearGeneticModel::evaluate(ModelInputData& inputData)
{
	std::vector<double> inputVec = inputData.getData();
	if (inputVec.size()*inputVec.size() != parameters.size()) throw std::invalid_argument("LinearGeneticModel: InputData is incorrect length");

	std::vector<double> result(inputVec.size(), 0);
	for (int i = 0; i < inputVec.size(); i++)
	{
		for (int j = 0; j < inputVec.size(); j++)
		{
			result[i] += inputVec[j]*parameters[i*inputVec.size() + j];
		}	
	}

	return std::make_unique<ModelOutputDataVector>(result);
}

std::vector<double> LinearGeneticModel::getParameters() const { return parameters; }

void LinearGeneticModel::setParameters(std::vector<double> p)
{
	if (parameters.size() != p.size()) throw std::invalid_argument("LinearGeneticModel: Incorrect number of parameters");

	parameters = p;
}
