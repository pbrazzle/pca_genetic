set(SIMULATOR_SOURCES
	SimulationFileReader.cpp
	Simulation.cpp 
	../Logger.cpp)
	
add_library(GeneticSimulator STATIC ${SIMULATOR_SOURCES})
target_include_directories(GeneticSimulator PUBLIC ..)
target_link_libraries(GeneticSimulator PUBLIC alg_strategies)

add_executable(GeneticSim GeneticSim.cpp )
target_include_directories(GeneticSim PUBLIC ..)
target_link_libraries(GeneticSim PUBLIC GeneticSimulator)