#include "NeuralModel.hpp"
#include "ModelOutputDataVector.hpp"

#include <stdexcept>
#include <algorithm>

using GeneticModels::GeneticModel;
using GeneticModels::ModelOutputData;
using GeneticModels::NeuralModel;

NeuralModel::NeuralModel(std::vector<unsigned int> l) : layerSizes(l)
{
	for (int i = 0; i < layerSizes.size() - 1; i++)
	{
		int s1 = layerSizes[i], s2 = layerSizes[i + 1];
		std::vector<double> layerWeights(s1 * s2, 1.0);
		weights.insert(weights.end(), layerWeights.begin(), layerWeights.end());
	}
}

NeuralModel::NeuralModel(std::vector<unsigned int> l, std::vector<double> w) : layerSizes(l), weights(w)
{
}

void NeuralModel::setLayerSizes(std::vector<unsigned int> newLayers)
{
	layerSizes = newLayers;
	weights.clear();
	for (int i = 0; i < layerSizes.size() - 1; i++)
	{
		int s1 = layerSizes[i], s2 = layerSizes[i + 1];
		std::vector<double> layerWeights(s1 * s2, 1.0);
		weights.insert(weights.end(), layerWeights.begin(), layerWeights.end());
	}
}

std::unique_ptr<GeneticModel> NeuralModel::clone() const
{
	return std::make_unique<NeuralModel>(layerSizes, weights);
}

std::unique_ptr<ModelOutputData> NeuralModel::evaluate(ModelInputData& input)
{
	if (layerSizes.size() == 0) throw std::logic_error("Model has no layers to evaluate data");
	if (input.getData().size() != layerSizes[0]) throw std::invalid_argument("Invalid input data size");

	std::vector<double> result = input.getData();

	int weightOffset = 0;
	for (int i = 1; i < layerSizes.size(); i++)
	{
		std::vector<double> layerResult(layerSizes[i], 0);

		for (int j = 0; j < layerSizes[i]; j++)
		{
			double sum = 0;
			for (int k = 0; k < layerSizes[i - 1]; k++)
			{
				sum += result[k] * weights[k + weightOffset];
			}
			//Apply ReLu
			layerResult[j] = (sum < 0) ? 0 : sum;
			weightOffset += layerSizes[i - 1];
		}
		result = layerResult;
	}

	return std::make_unique<ModelOutputDataVector>(result);
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
