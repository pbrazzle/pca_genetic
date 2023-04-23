#include "NeuralModel.hpp"
#include "ModelOutputDataVector.hpp"

#include <stdexcept>
#include <algorithm>
#include <iostream>

using GeneticModels::GeneticModel;
using GeneticModels::ModelOutputData;
using GeneticModels::NeuralModel;

NeuralModel::NeuralModel(std::vector<unsigned int> l) : layerSizes(l)
{
	int totalWeights = 0;
	for (int i = 1; i < layerSizes.size(); i++)
	{
		totalWeights += layerSizes[i] * layerSizes[i - 1];
	}
	weights = std::vector<double>(totalWeights, 1.0);
}

NeuralModel::NeuralModel(std::vector<unsigned int> l, std::vector<double> w) : layerSizes(l), weights(w)
{
	int totalWeights = 0;
	for (int i = 1; i < layerSizes.size(); i++)
	{
		totalWeights += layerSizes[i] * layerSizes[i - 1];
	}
	if (totalWeights != weights.size()) throw std::invalid_argument("NeuralModel: Invalid number of weights");
}

void NeuralModel::setLayerSizes(std::vector<unsigned int> newLayers)
{
	layerSizes = newLayers;
	int totalWeights = 0;
	for (int i = 1; i < layerSizes.size(); i++)
	{
		totalWeights += layerSizes[i] * layerSizes[i - 1];
	}
	weights = std::vector<double>(totalWeights, 1.0);
}

std::unique_ptr<GeneticModel> NeuralModel::clone() const
{
	return std::make_unique<NeuralModel>(layerSizes, weights);
}

std::unique_ptr<ModelOutputData> NeuralModel::evaluate(ModelInputData& input)
{
	if (layerSizes.size() == 0) throw std::logic_error("Model has no layers to evaluate data");
	if (input.getData().size() != layerSizes[0]) throw std::invalid_argument("Invalid input data size");

	int largestLayer = *std::max_element(layerSizes.begin(), layerSizes.end());
	double* inputLayerArr = new double[largestLayer];
	double* resultArr = new double[largestLayer];

	unsigned int* layerSizeArr = new unsigned int[layerSizes.size()];
	for (int i = 0; i < layerSizes.size(); i++) layerSizeArr[i] = layerSizes[i];

	std::vector<double> inputVec = input.getData();
	for (int i = 0; i < inputVec.size(); i++) resultArr[i] = inputVec[i];

	int weightOffset = 0;
	double* weightArr = &weights[0];
	for (int i = 1; i < layerSizes.size(); i++)
	{
		for (int j = 0; j < layerSizeArr[i]; j++)
		{
			double sum = 0;
			for (int k = 0; k < layerSizeArr[i - 1]; k++)
			{
				sum += resultArr[k] * weightArr[k + weightOffset];
			}
			//Apply ReLu
			inputLayerArr[j] = (sum < 0) ? 0 : sum;
			weightOffset += layerSizeArr[i - 1];
		}
		for (int j = 0; j < layerSizeArr[i]; j++) resultArr[j] = inputLayerArr[j];
	}

	std::vector<double> finalResult;
	finalResult.insert(finalResult.end(), &resultArr[0], &resultArr[layerSizeArr[layerSizes.size() - 1]]);
	delete[] resultArr;
	delete[] inputLayerArr;
	delete[] layerSizeArr;
	return std::make_unique<ModelOutputDataVector>(finalResult);
}

std::vector<double> NeuralModel::getParameters() const
{
	return weights;
}

void NeuralModel::setParameters(std::vector<double> newWeights)
{
	if (newWeights.size() != weights.size()) throw std::invalid_argument("Invalid number of weights");
	weights = newWeights;
}

int NeuralModel::getInputDataLength() const
{
	if (layerSizes.size() == 0) throw std::logic_error("Model has no layers to evaluate data");
	return layerSizes.front();
}

int NeuralModel::getOutputDataLength() const
{
	if (layerSizes.size() == 0) throw std::logic_error("Model has no layers to evaluate data");
	return layerSizes.back();
}

JSON_IO::JSONObject NeuralModel::toJSON() const
{
	JSONObject obj;

	obj.addString("typename", "NeuralModel");

	JSONObject dataObj;

	std::vector<JSONObject> layerJSON;
	for (int size : layerSizes) layerJSON.push_back(JSONObject(size));
	dataObj.addArray("layer_sizes", layerJSON);

	std::vector<JSONObject> weightJSON;
	for (double weight : weights) weightJSON.push_back(JSONObject(weight));
	dataObj.addArray("weights", weightJSON);

	obj.addObject("data", dataObj);

	return obj;
}

void NeuralModel::fromJSON(const JSONObject& obj)
{
	layerSizes.clear();
	weights.clear();

	auto layerJSON = obj["layer_sizes"].asArray();
	for (auto layerObj : layerJSON) layerSizes.push_back(layerObj.asInt());

	auto weightJSON = obj["weights"].asArray();
	for (auto weightObj : weightJSON) weights.push_back(weightObj.asFloat());
}
