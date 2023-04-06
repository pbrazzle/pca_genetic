#ifndef GENETIC_ALGORITHM_FACTORY
#define GENETIC_ALGORITHM_FACTORY

#include "algorithm/GeneticAlgorithm.hpp"
#include "SingleCrossingCombiner.hpp"
#include "RandomCrossingCombiner.hpp"
#include "FitnessSumSelector.hpp"
#include "BestFitnessSelector.hpp"
#include "DistributionSelector.hpp"
#include "DistanceCalculator.hpp"
#include "DecisionCalculator.hpp"

#include "json/AbstractJSONFactory.hpp"

#include <memory>
#include <string>
#include <map>

namespace PCAGenetic
{
	GeneticAlgorithm makeBasicAlgorithm();

	using namespace JSON_IO;

	std::unique_ptr<FitnessCalculator> FitCalcFromJSON(const JSONObject& obj);
	std::unique_ptr<ParentSelector> ParentSelectFromJSON(const JSONObject& obj);
	std::unique_ptr<ParentCombiner> ParentCombFromJSON(const JSONObject& obj);
}

#endif
