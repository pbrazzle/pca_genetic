cmake_minimum_required(VERSION 3.10)

project(pca_genetic)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib)
enable_testing()

set(MODEL_SOURCES 
	src/model/linear/LinearGeneticModel.cpp 
	src/model/input/ModelInputDataVector.cpp 
	src/model/output/ModelOutputDataVector.cpp
	src/model/convolution/ConvolutionModel.cpp
	src/model/downsample/DownSamplingModel.cpp
	src/model/neural/NeuralModel.cpp
	src/model/regression/LogisticRegressionModel.cpp)
	
add_library(GeneticModels STATIC ${MODEL_SOURCES})
target_include_directories(GeneticModels PUBLIC src src/model)

set(ALG_SOURCES 
	src/algorithm/GeneticAlgorithm.cpp 
	src/algorithm/GeneticAlgorithmParameters.cpp
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

set(JSON_SOURCES
	src/json/JSONObject.cpp
	src/json/JSONFile.cpp)
	
add_library(GeneticJSON STATIC ${JSON_SOURCES})
target_include_directories(GeneticJSON PUBLIC src)

set(SIMULATOR_SOURCES 
	src/simulator/GeneticSim.cpp 
	src/simulator/SimulationFileReader.cpp
	src/simulator/Simulation.cpp 
	src/Logger.cpp)

add_executable(GeneticSim ${SIMULATOR_SOURCES})
target_include_directories(GeneticSim PUBLIC src)
target_link_libraries(GeneticSim PUBLIC GeneticAlgorithms GeneticModels)

set(ALL_LIBS
	GeneticModels
	GeneticAlgorithms
	GeneticJSON)
	
set(TEST_SOURCES
	src/json/JSONTest.cpp
	test/basicTests.cpp
	src/algorithm/ParamJSONTest.cpp)
	
foreach(testSrc ${TEST_SOURCES})
	get_filename_component(testName ${testSrc} NAME_WE)
	add_executable(${testName} ${testSrc})
	
	target_include_directories(${testName} PUBLIC src)
	target_link_libraries(${testName} PUBLIC ${ALL_LIBS})
	set_target_properties(${testName} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin/tests)
		
	add_test(NAME ${testName}
			COMMAND $<TARGET_FILE:${testName}>
			)
endforeach(testSrc)