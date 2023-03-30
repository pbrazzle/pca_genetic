set(ALG_SOURCES 
	GeneticAlgorithm.cpp)
	
add_library(GeneticAlgorithms STATIC ${ALG_SOURCES})
target_include_directories(GeneticAlgorithms PUBLIC ..)
target_link_libraries(GeneticAlgorithms PUBLIC GeneticModels GeneticJSON)

add_subdirectory(strategies)

add_executable(GeneticAlgorithm GeneticAlgorithm.test.cpp)
target_include_directories(GeneticAlgorithm PUBLIC ..)
target_link_libraries(GeneticAlgorithm PUBLIC alg_strategies)
add_test(NAME GeneticAlgorithm COMMAND GeneticAlgorithm)