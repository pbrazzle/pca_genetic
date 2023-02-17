cmake_minimum_required(VERSION 3.10)

project(pca_genetic)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)

add_executable(basicTests test/basicTests.cpp src/BasicGeneticAlgorithm.cpp src/LinearGeneticModel.cpp src/ModelInputDataVector.cpp src/ModelOutputDataVector.cpp)
target_include_directories(basicTests PUBLIC src)
