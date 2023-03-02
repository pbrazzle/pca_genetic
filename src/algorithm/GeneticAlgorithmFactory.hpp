#ifndef GENETIC_ALGORITHM_FACTORY
#define GENETIC_ALGORITHM_FACTORY

#include "GeneticAlgorithm.hpp"
#include "algorithm/combination/single/SingleCrossingCombiner.hpp"
#include "algorithm/selection/sum/FitnessSumSelector.hpp"
#include "algorithm/fitness/distance/DistanceCalculator.hpp"

#include <memory>
#include <string>
#include <map>

namespace PCAGenetic 
{
	GeneticAlgorithm makeBasicAlgorithm()
	{
		std::unique_ptr<FitnessCalculator> fc(new DistanceCalculator());
		std::unique_ptr<ParentSelector> ps(new FitnessSumSelector());
		std::unique_ptr<ParentCombiner> pc(new SingleCrossingCombiner());
		GeneticAlgorithm alg(std::move(fc), std::move(ps), std::move(pc));
		return alg;
	}

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
		{"DistanceCalculator", &makeFitnessCalculator<DistanceCalculator>}
	};
	
	std::map<std::string, SelectFactory> selectMap {
		{"FitnessSumSelector", &makeParentSelector<FitnessSumSelector>}
	};
	
	std::map<std::string, CombinerFactory> combinerMap {
		{"SingleCrossingCombiner", &makeParentCombiner<SingleCrossingCombiner>}
	};
}

#endif
