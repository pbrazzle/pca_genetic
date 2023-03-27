cmake_minimum_required(VERSION 3.10)

project(pca_genetic)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib)
enable_testing()

set(JSON_SOURCES
	src/json/JSONObject.cpp
	src/json/JSONFile.cpp)
	
add_library(GeneticJSON STATIC ${JSON_SOURCES})
target_include_directories(GeneticJSON PUBLIC src)

add_subdirectory(src/model)

add_subdirectory(src/algorithm)

set(SIMULATOR_SOURCES
	src/simulator/SimulationFileReader.cpp
	src/simulator/Simulation.cpp 
	src/Logger.cpp)
	
add_library(GeneticSimulator STATIC ${SIMULATOR_SOURCES})
target_include_directories(GeneticSimulator PUBLIC src)
target_link_libraries(GeneticSimulator PUBLIC GeneticAlgorithms)

add_executable(GeneticSim src/simulator/GeneticSim.cpp )
target_include_directories(GeneticSim PUBLIC src)
target_link_libraries(GeneticSim PUBLIC GeneticSimulator)

set(ALL_LIBS
	GeneticModels
	GeneticAlgorithms
	GeneticSimulator
	GeneticJSON)
	
set(TEST_SOURCES
	src/algorithm/GeneticAlgorithm.test.cpp
	src/json/JSONObject.test.cpp
	src/simulator/Simulation.test.cpp
	src/model/neural/NeuralModel.test.cpp
	src/model/downsample/DownSamplingModel.test.cpp)
	
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