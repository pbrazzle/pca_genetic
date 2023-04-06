set(ALG_SOURCES 
	GeneticAlgorithm.cpp
	BestFitnessSelector.cpp
	DecisionCalculator.cpp
	DistanceCalculator.cpp
	DistributionSelector.cpp
	FitnessSumSelector.cpp
	RandomCrossingCombiner.cpp
	SingleCrossingCombiner.cpp
	GeneticAlgorithmFactory.cpp)
	
add_library(GeneticAlgorithms STATIC ${ALG_SOURCES})
target_include_directories(GeneticAlgorithms PUBLIC ..)
target_link_libraries(GeneticAlgorithms PUBLIC GeneticModels GeneticJSON)

set(TEST_SOURCES
	GeneticAlgorithm.test.cpp
	BestFitnessSelector.test.cpp
	DecisionCalculator.test.cpp
	DistanceCalculator.test.cpp
	DistributionSelector.test.cpp
	FitnessSumSelector.test.cpp
	RandomCrossingCombiner.test.cpp
	SingleCrossingCombiner.test.cpp)

foreach(TEST ${TEST_SOURCES})
	get_filename_component(TEST_NAME ${TEST} NAME_WE)
	add_executable(${TEST_NAME} ${TEST})
	target_link_libraries(${TEST_NAME} PUBLIC GeneticAlgorithms PRIVATE Catch2::Catch2WithMain)
	catch_discover_tests(${TEST_NAME})
endforeach()