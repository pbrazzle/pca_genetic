#ifndef GENETIC_TYPES
#define GENETIC_TYPES

#include "model/input/ModelInputData.hpp"
#include "model/output/ModelOutputData.hpp"
#include "model/GeneticModel.hpp"
#include "CloneableHandle.hpp"

namespace PCAGenetic
{
	using namespace GeneticModels;
	
	typedef std::pair<std::unique_ptr<ModelInputData>, std::unique_ptr<ModelOutputData>> trainingItem;
	typedef std::vector<std::unique_ptr<GeneticModel>> modelVector;
	typedef std::pair<std::unique_ptr<GeneticModel>, std::unique_ptr<GeneticModel>> parentPair;

	typedef CloneableHandle<GeneticModel> ModelHandle;
}

#endif
