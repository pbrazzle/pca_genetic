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
	
	std::map<std::string, FitCalcFactory> fitCalcMap {
		{"", []() { return std::unique_ptr<FitnessCalculator>(); }},
		{"DistanceCalculator", &makeFitnessCalculator<DistanceCalculator>},
		{"DecisionCalculator", &makeFitnessCalculator<DecisionCalculator>}
	};
	
	std::map<std::string, SelectFactory> selectMap {
		{"", []() { return std::unique_ptr<ParentSelector>(); }},
		{"FitnessSumSelector", &makeParentSelector<FitnessSumSelector>},
		{"BestFitnessSelector", &makeParentSelector<BestFitnessSelector>},
		{"DistributionSelector", &makeParentSelector<DistributionSelector>}
	};
	
	std::map<std::string, CombinerFactory> combinerMap {
		{"", []() { return std::unique_ptr<ParentCombiner>(); }},
		{"SingleCrossingCombiner", &makeParentCombiner<SingleCrossingCombiner>},
		{"RandomCrossingCombiner", &makeParentCombiner<RandomCrossingCombiner>}
	};
}

#endif
