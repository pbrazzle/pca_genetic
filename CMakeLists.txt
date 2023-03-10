cmake_minimum_required(VERSION 3.10)

project(pca_genetic)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib)

set(MODEL_SOURCES 
	src/model/linear/LinearGeneticModel.cpp 
	src/model/input/ModelInputDataVector.cpp 
	src/model/output/ModelOutputDataVector.cpp)
add_library(GeneticModels STATIC ${MODEL_SOURCES})
target_include_directories(GeneticModels PUBLIC src src/model)

set(ALG_SOURCES 
	src/algorithm/GeneticAlgorithm.cpp 
	src/algorithm/fitness/distance/DistanceCalculator.cpp 
	src/algorithm/fitness/decision/DecisionCalculator.cpp
	src/algorithm/combination/single/SingleCrossingCombiner.cpp 
	src/algorithm/combination/random/RandomCrossingCombiner.cpp
	src/algorithm/selection/sum/FitnessSumSelector.cpp
	src/algorithm/selection/best/BestFitnessSelector.cpp
	src/algorithm/selection/distribution/DistributionSelector.cpp)

add_library(GeneticAlgorithms STATIC ${ALG_SOURCES})
target_include_directories(GeneticAlgorithms PUBLIC src src/model src/algorithm)
target_link_libraries(GeneticAlgorithms PUBLIC GeneticModels)

set(SIMULATOR_SOURCES 
	src/simulator/GeneticSim.cpp 
	src/simulator/SimulationFileReader.cpp
	src/simulator/Simulation.cpp 
	src/Logger.cpp)

add_executable(GeneticSim ${SIMULATOR_SOURCES})
target_include_directories(GeneticSim PUBLIC src)
target_link_libraries(GeneticSim PUBLIC GeneticAlgorithms GeneticModels)

add_executable(basicTests test/basicTests.cpp)
target_include_directories(basicTests PUBLIC src src/model src/algorithm)
target_link_libraries(basicTests PUBLIC GeneticModels GeneticAlgorithms)
