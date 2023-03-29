set(ALG_STRATEGY_SOURCES
	BestFitnessSelector.cpp
	DecisionCalculator.cpp
	DistanceCalculator.cpp
	DistributionSelector.cpp
	FitnessSumSelector.cpp
	RandomCrossingCombiner.cpp
	SingleCrossingCombiner.cpp)

add_library(alg_strategies ${ALG_STRATEGY_SOURCES})
target_include_directories(alg_strategies PUBLIC algorithm src/algorithm/strategies)
target_link_libraries(alg_strategies PUBLIC GeneticAlgorithms)
