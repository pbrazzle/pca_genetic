#ifndef GENETIC_ALGORITHM_FACTORY
#define GENETIC_ALGORITHM_FACTORY

#include "GeneticAlgorithm.hpp"
#include "SingleCrossingCombiner.hpp"
#include "FitnessSumSelector.hpp"
#include "DistanceCalculator.hpp"
#include <memory>

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
}

#endif
