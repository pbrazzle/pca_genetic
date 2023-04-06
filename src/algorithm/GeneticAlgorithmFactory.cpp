#include "GeneticAlgorithmFactory.hpp"

using namespace PCAGenetic;

GeneticAlgorithm PCAGenetic::makeBasicAlgorithm()
{
	std::unique_ptr<FitnessCalculator> fc(new DistanceCalculator());
	std::unique_ptr<ParentSelector> ps(new FitnessSumSelector());
	std::unique_ptr<ParentCombiner> pc(new SingleCrossingCombiner());

	return { std::move(fc), std::move(ps), std::move(pc) };
};

typenameMap<FitnessCalculator> fitCalcMap{
	{"DecisionCalculator", &makeDefaultDerived<FitnessCalculator, DecisionCalculator>},
	{"DistanceCalculator", &makeDefaultDerived<FitnessCalculator, DistanceCalculator>}
};

std::unique_ptr<FitnessCalculator> PCAGenetic::FitCalcFromJSON(const JSONObject& obj)
{
	return makeAbstractFromJSON<FitnessCalculator>(fitCalcMap, obj);
}

typenameMap<ParentSelector> selectMap{
	{"FitnessSumSelector", &makeDefaultDerived<ParentSelector, FitnessSumSelector>},
	{"BestFitnessSelector", &makeDefaultDerived<ParentSelector, BestFitnessSelector>},
	{"DistributionSelector", &makeDefaultDerived<ParentSelector, DistributionSelector>}
};

std::unique_ptr<ParentSelector> PCAGenetic::ParentSelectFromJSON(const JSONObject& obj)
{
	return makeAbstractFromJSON<ParentSelector>(selectMap, obj);
}

typenameMap<ParentCombiner> combinerMap{
	{"SingleCrossingCombiner", &makeDefaultDerived<ParentCombiner, SingleCrossingCombiner>},
	{"RandomCrossingCombiner", &makeDefaultDerived<ParentCombiner, RandomCrossingCombiner>}
};

std::unique_ptr<ParentCombiner> PCAGenetic::ParentCombFromJSON(const JSONObject& obj)
{
	return makeAbstractFromJSON<ParentCombiner>(combinerMap, obj);
}
