#include "InterconnectedGeneticModel.hpp"
#include "GeneticModelFactory.hpp"

#include "ModelInputDataVector.hpp"
#include "ModelOutputDataVector.hpp"

GeneticModels::InterconnectedGeneticModel::InterconnectedGeneticModel(LayerArray& models) : layers(std::move(models))
{
}

std::unique_ptr<GeneticModel> GeneticModels::InterconnectedGeneticModel::clone() const
{
	LayerArray clonedArray;
	for (int i = 0; i < layers.size(); i++)
	{
		ModelLayer clonedLayer;
		for (int j = 0; j < layers[i].size(); j++) clonedLayer.push_back(layers[i][j]->clone());
		clonedArray.emplace_back(std::move(clonedLayer));
	}
	return std::make_unique<InterconnectedGeneticModel>(clonedArray);
}

std::unique_ptr<ModelOutputData> GeneticModels::InterconnectedGeneticModel::evaluate(ModelInputData& input)
{
	auto inputData = input.getData();

	std::vector<double> layerResult;
	for (int i = 0; i < layers.size(); i++)
	{
		layerResult.clear();
		for (int j = 0; j < layers[i].size(); j++)
		{
			const std::vector<double> modelInputData(inputData.begin(), inputData.begin() + layers[i][j]->getInputDataLength());
			inputData.erase(inputData.begin(), inputData.begin() + layers[i][j]->getInputDataLength());
			ModelInputDataVector modelInput(modelInputData);
			auto result = layers[i][j]->evaluate(modelInput)->getData();
			layerResult.insert(layerResult.end(), result.begin(), result.end());
		}
		inputData = layerResult;
	}

	return std::make_unique<ModelOutputDataVector>(layerResult);
}

std::vector<double> GeneticModels::InterconnectedGeneticModel::getParameters() const
{
	std::vector<double> allParams;

	for (int i = 0; i < layers.size(); i++)
	{
		for (int j = 0; j < layers[i].size(); j++)
		{
			auto modelParams = layers[i][j]->getParameters();
			allParams.insert(allParams.end(), modelParams.begin(), modelParams.end());
		}
	}

	return allParams;
}

void GeneticModels::InterconnectedGeneticModel::setParameters(std::vector<double> newParams)
{
	for (int i = 0; i < layers.size(); i++)
	{
		for (int j = 0; j < layers[i].size(); j++)
		{
			std::vector<double> modelParams;
			modelParams.insert(modelParams.end(), newParams.begin(), newParams.begin() + layers[i][j]->getParameterLength());
			newParams.erase(newParams.begin(), newParams.begin() + layers[i][j]->getParameterLength());
			layers[i][j]->setParameters(modelParams);
		}
	}
}

int GeneticModels::InterconnectedGeneticModel::getInputDataLength() const
{
	if (layers.empty()) return 0;
	int totalInputLength = 0;
	for (int i = 0; i < layers.front().size(); i++) totalInputLength += layers.front()[i]->getInputDataLength();
	return totalInputLength;
}

int GeneticModels::InterconnectedGeneticModel::getOutputDataLength() const
{
	if (layers.empty()) return 0;
	int totalOutputLength = 0;
	for (int i = 0; i < layers.back().size(); i++) totalOutputLength += layers.back()[i]->getOutputDataLength();
	return totalOutputLength;
}

JSON_IO::JSONObject GeneticModels::InterconnectedGeneticModel::toJSON() const
{
	JSONObject obj;
	obj.addString("typename", "InterconnectedGeneticModel");

	JSONObject dataObj;
	std::vector<JSONObject> allLayers;

	for (int i = 0; i < layers.size(); i++)
	{
		std::vector<JSONObject> layerArr;
		for (int j = 0; j < layers[i].size(); j++) layerArr.push_back(layers[i][j]->toJSON());
		allLayers.push_back(JSONObject(layerArr));
	}
	dataObj.addArray("layers", allLayers);
	obj.addObject("data", dataObj);

	return obj;
}

void GeneticModels::InterconnectedGeneticModel::fromJSON(const JSONObject& obj)
{
	layers.clear();
	std::vector<JSONObject> allLayers = obj["layers"].asArray();

	for (auto layerArr : allLayers)
	{
		auto layerObjs = layerArr.asArray();

		ModelLayer newLayer;
		for (auto modelObj : layerObjs)
		{
			newLayer.emplace_back(ModelFromJSON(modelObj));
		}
		layers.emplace_back(std::move(newLayer));
	}
}
