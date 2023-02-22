cmake_minimum_required(VERSION 3.10)

project(pca_genetic)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib)

set(MODEL_SOURCES src/model/LinearGeneticModel.cpp src/model/ModelInputDataVector.cpp src/model/ModelOutputDataVector.cpp)
add_library(GeneticModels STATIC ${MODEL_SOURCES})
target_include_directories(GeneticModels PUBLIC src src/model)

set(ALG_SOURCES src/algorithm/GeneticAlgorithm.cpp src/algorithm/DistanceCalculator.cpp src/algorithm/SingleCrossingCombiner.cpp src/algorithm/FitnessSumSelector.cpp)
add_library(GeneticAlgorithms STATIC ${ALG_SOURCES})
target_include_directories(GeneticAlgorithms PUBLIC src src/model src/algorithm)
target_link_libraries(GeneticAlgorithms PUBLIC GeneticModels)

add_executable(basicTests test/basicTests.cpp)
target_include_directories(basicTests PUBLIC src src/model src/algorithm)
target_link_libraries(basicTests PUBLIC GeneticModels GeneticAlgorithms)
