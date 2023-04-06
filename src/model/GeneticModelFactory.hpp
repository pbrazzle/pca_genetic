#ifndef GENETIC_ALGORITHM_FACTORY
#define GENETIC_ALGORITHM_FACTORY

#include "GeneticModel.hpp"
#include "ModelInputData.hpp"
#include "ModelOutputData.hpp"

#include "json/AbstractJSONFactory.hpp"

namespace GeneticModels
{
	using namespace JSON_IO;

	std::unique_ptr<GeneticModel> ModelFromJSON(const JSONObject& obj);
	std::unique_ptr<ModelInputData> InputDataFromJSON(const JSONObject& obj);
	std::unique_ptr<ModelOutputData> OutputDataFromJSON(const JSONObject& obj);
}

#endif
