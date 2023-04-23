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

LinearGeneticModel::LinearGeneticModel(int d) : dataLength(d), inputSize(d), outputSize(d)
{
	parameters = std::vector<double>(dataLength*dataLength, 0);
}

LinearGeneticModel::LinearGeneticModel(int i, int o) : dataLength(i), inputSize(i), outputSize(o), parameters(i*o, 0.0)
{
}

LinearGeneticModel::LinearGeneticModel(int i, int o, std::vector<double> p) : dataLength(i), inputSize(i), outputSize(o), parameters(p)
{
	if (p.size() != i * o) throw std::invalid_argument("LinearGeneticModel: Incorrect number of parameters");
}

LinearGeneticModel::LinearGeneticModel(int d, std::vector<double> p) : dataLength(d), inputSize(d), outputSize(d)
{
	if (p.size() != dataLength*dataLength) throw std::invalid_argument("LinearGeneticModel: Incorrect number of parameters");

	parameters = p;
}

std::unique_ptr<GeneticModel> LinearGeneticModel::clone() const
{
	return std::make_unique<LinearGeneticModel>(inputSize, outputSize, parameters);
}

std::unique_ptr<ModelOutputData> LinearGeneticModel::evaluate(ModelInputData& inputData)
{
	std::vector<double> inputVec = inputData.getData();
	if (inputVec.size() != dataLength) throw std::invalid_argument("LinearGeneticModel: InputData is incorrect length");

	std::vector<double> result(outputSize, 0);
	for (int i = 0; i < outputSize; i++)
	{
		for (int j = 0; j < inputSize; j++)
		{
			result[i] += inputVec[j]*parameters[i*inputSize + j];
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
	for (int i = 0; i < inputSize; i++)
	{
		matrixString += "[";
		for (int j = 0; j < outputSize; j++)
		{
			matrixString += std::to_string(parameters[outputSize*i + j]) + ", ";
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
	dataObj.addInt("inputSize", inputSize);
	dataObj.addInt("outputSize", outputSize);

	obj.addObject("data", dataObj);
	
	return obj;
}

void LinearGeneticModel::fromJSON(const JSONObject& obj)
{
	auto params = obj["parameters"].asArray();

	std::vector<double> newParams;
	for (auto jsonParam : params) newParams.push_back(jsonParam.asFloat());

	parameters = newParams;

	inputSize = obj["inputSize"].asInt();
	outputSize = obj["outputSize"].asInt();
	dataLength = inputSize;
}

int LinearGeneticModel::getInputDataLength() const
{
	return inputSize;
}

int LinearGeneticModel::getOutputDataLength() const
{
	return outputSize;
}
