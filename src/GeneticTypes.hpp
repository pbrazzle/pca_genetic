#ifndef GENETIC_TYPES
#define GENETIC_TYPES

#include "model/ModelInputData.hpp"
#include "model/ModelOutputData.hpp"
#include "model/GeneticModel.hpp"

namespace PCAGenetic
{
	typedef std::pair<std::unique_ptr<ModelInputData>, std::unique_ptr<ModelOutputData>> trainingItem;
	typedef std::vector<std::unique_ptr<GeneticModel>> modelVector;
	typedef std::pair<std::unique_ptr<GeneticModel>, std::unique_ptr<GeneticModel>> parentPair;
}

#endif
