set(ALG_SOURCES 
	GeneticAlgorithm.cpp 
	GeneticAlgorithmParameters.cpp
	GeneticTrainer.cpp
	TrainerData.cpp
	TrainerParameters.cpp
	TrainerModels.cpp
	fitness/distance/DistanceCalculator.cpp 
	fitness/decision/DecisionCalculator.cpp
	combination/single/SingleCrossingCombiner.cpp 
	combination/random/RandomCrossingCombiner.cpp
	selection/sum/FitnessSumSelector.cpp
	selection/best/BestFitnessSelector.cpp
	selection/distribution/DistributionSelector.cpp)
	
add_library(GeneticAlgorithms STATIC ${ALG_SOURCES})
target_include_directories(GeneticAlgorithms PUBLIC src/model fitness combination selection)
target_link_libraries(GeneticAlgorithms PUBLIC GeneticModels GeneticJSON)