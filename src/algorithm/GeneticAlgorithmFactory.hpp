#ifndef GENETIC_ALGORITHM_FACTORY
#define GENETIC_ALGORITHM_FACTORY

#include "GeneticAlgorithm.hpp"
#include "algorithm/combination/single/SingleCrossingCombiner.hpp"
#include "algorithm/combination/random/RandomCrossingCombiner.hpp"
#include "algorithm/selection/sum/FitnessSumSelector.hpp"
#include "algorithm/selection/best/BestFitnessSelector.hpp"
#include "algorithm/selection/distribution/DistributionSelector.hpp"
#include "algorithm/fitness/distance/DistanceCalculator.hpp"
#include "algorithm/fitness/decision/DecisionCalculator.hpp"

#include "json/AbstractJSONFactory.hpp"

#include <memory>
#include <string>
#include <map>

namespace PCAGenetic 
{
	using FitCalcFactory = std::unique_ptr<FitnessCalculator> (*)();
	using SelectFactory = std::unique_ptr<ParentSelector> (*)();
	using CombinerFactory = std::unique_ptr<ParentCombiner> (*)();
	
	template <typename FitCalc>
	std::unique_ptr<FitnessCalculator> makeFitnessCalculator() { return std::unique_ptr<FitnessCalculator>(new FitCalc()); }
	
	template <typename PSelect>
	std::unique_ptr<ParentSelector> makeParentSelector() { return std::unique_ptr<ParentSelector>(new PSelect()); }
	
	template <typename PComb>
	std::unique_ptr<ParentCombiner> makeParentCombiner() { return std::unique_ptr<ParentCombiner>(new PComb()); }

	using namespace GeneticJSON;

	template <typename Base, typename Derived>
	std::unique_ptr<Base> makeDefaultDerived() { return std::unique_ptr<Base>(new Derived()); }

	typenameMap<FitnessCalculator> fitCalcMap {
		{"DecisionCalculator", &makeDefaultDerived<FitnessCalculator, DecisionCalculator>},
		{"DistanceCalculator", &makeDefaultDerived<FitnessCalculator, DistanceCalculator>}
	};

	std::unique_ptr<FitnessCalculator> FitCalcFromJSON(const JSONObject& obj) 
	{ 
		return makeAbstractFromJSON<FitnessCalculator>(fitCalcMap, obj);
	}

	typenameMap<ParentSelector> selectMap {
		{"FitnessSumSelector", &makeDefaultDerived<ParentSelector, FitnessSumSelector>},
		{"BestFitnessSelector", &makeDefaultDerived<ParentSelector, BestFitnessSelector>},
		{"DistributionSelector", &makeDefaultDerived<ParentSelector, DistributionSelector>}
	};

	std::unique_ptr<ParentSelector> ParentSelectFromJSON(const JSONObject& obj) 
	{ 
		return makeAbstractFromJSON<ParentSelector>(selectMap, obj);
	}
	
	typenameMap<ParentCombiner> combinerMap {
		{"SingleCrossingCombiner", &makeDefaultDerived<ParentCombiner, SingleCrossingCombiner>},
		{"RandomCrossingCombiner", &makeDefaultDerived<ParentCombiner, RandomCrossingCombiner>}
	};

	std::unique_ptr<ParentCombiner> ParentCombFromJSON(const JSONObject& obj) 
	{ 
		return makeAbstractFromJSON<ParentCombiner>(combinerMap, obj);
	}
}

#endif
