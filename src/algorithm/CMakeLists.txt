set(ALG_SOURCES 
	GeneticAlgorithm.cpp)
	
add_library(GeneticAlgorithms STATIC ${ALG_SOURCES})
target_include_directories(GeneticAlgorithms PUBLIC model)
target_link_libraries(GeneticAlgorithms PUBLIC GeneticModels GeneticJSON)

add_subdirectory(strategies)