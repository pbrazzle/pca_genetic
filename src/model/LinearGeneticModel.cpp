#include "LinearGeneticModel.hpp"

#include "ModelOutputDataVector.hpp"

#include <stdexcept>
#include <iostream>
#include <math.h>

using GeneticModels::LinearGeneticModel;
using GeneticModels::GeneticModel;
using GeneticModels::ModelOutputData;
using GeneticModels::ModelOutputDataVector;
using namespace JSON_IO;

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
	if (inputVec.size() != dataLength) throw std::invalid_argument("LinearGeneticModel: InputData is incorrect length");

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

std::string LinearGeneticModel::printMatrix() const
{
	std::string matrixString;
	for (int i = 0; i < dataLength; i++)
	{
		matrixString += "[";
		for (int j = 0; j < dataLength; j++)
		{
			matrixString += std::to_string(parameters[dataLength*i + j]) + ", ";
		}
		matrixString += "]\n";
	}
	return matrixString;
}

JSONObject LinearGeneticModel::toJSON() const
{
	JSONObject obj;
	obj.addString("typename", "LinearGeneticModel");
	
	std::vector<JSONObject> paramJSON;
	for (double d : parameters) paramJSON.push_back(JSONObject(d));
	JSONObject dataObj;
	dataObj.addArray("parameters", paramJSON);

	obj.addObject("data", dataObj);
	
	return obj;
}

void LinearGeneticModel::fromJSON(const JSONObject& obj)
{
	auto params = obj["parameters"].asArray();

	std::vector<double> newParams;
	for (auto jsonParam : params) newParams.push_back(jsonParam.asFloat());

	parameters = newParams;
	dataLength = (int) sqrt(parameters.size());
}

int LinearGeneticModel::getInputDataLength() const
{
	return dataLength;
}

int LinearGeneticModel::getOutputDataLength() const
{
	return dataLength;
}
