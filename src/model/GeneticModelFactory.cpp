#include "GeneticModelFactory.hpp"

#include "ConvolutionModel.hpp"
#include "InterconnectedGeneticModel.hpp"
#include "LinearGeneticModel.hpp"
#include "NeuralModel.hpp"

#include "ModelInputDataVector.hpp"
#include "ModelOutputDataVector.hpp"

using namespace GeneticModels;
using namespace JSON_IO;

typenameMap<GeneticModel> modelMap{
	{"LinearGeneticModel", &makeDefaultDerived<GeneticModel, LinearGeneticModel>},
	{"NeuralModel", &makeDefaultDerived<GeneticModel, NeuralModel>},
	{"InterconnectedGeneticModel",& makeDefaultDerived<GeneticModel, InterconnectedGeneticModel> },
	{"ConvolutionModel", &makeDefaultDerived<GeneticModel, ConvolutionModel>}
};

std::unique_ptr<GeneticModel> GeneticModels::ModelFromJSON(const JSONObject& obj)
{
	return makeAbstractFromJSON<GeneticModel>(modelMap, obj);
}

typenameMap<ModelInputData> inDataMap{
	{"ModelInputDataVector", &makeDefaultDerived<ModelInputData, ModelInputDataVector>}
};

std::unique_ptr<ModelInputData> GeneticModels::InputDataFromJSON(const JSONObject& obj)
{
	return makeAbstractFromJSON<ModelInputData>(inDataMap, obj);
}

typenameMap<ModelOutputData> outDataMap{
	{"ModelOutputDataVector", &makeDefaultDerived<ModelOutputData, ModelOutputDataVector>}
};

std::unique_ptr<ModelOutputData> GeneticModels::OutputDataFromJSON(const JSONObject& obj)
{
	return makeAbstractFromJSON<ModelOutputData>(outDataMap, obj);
}
