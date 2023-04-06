#include "GeneticModelFactory.hpp"

#include "LinearGeneticModel.hpp"

#include "ModelInputDataVector.hpp"
#include "ModelOutputDataVector.hpp"

using namespace GeneticModels;
using namespace JSON_IO;

typenameMap<GeneticModel> modelMap{
	{"LinearGeneticModel", &makeDefaultDerived<GeneticModel, LinearGeneticModel>}
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
