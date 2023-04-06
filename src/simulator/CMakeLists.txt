set(SIMULATOR_SOURCES
	Simulation.cpp 
	../Logger.cpp)
	
add_library(GeneticSimulator STATIC ${SIMULATOR_SOURCES})
target_include_directories(GeneticSimulator PUBLIC ..)
target_link_libraries(GeneticSimulator PUBLIC GeneticAlgorithms)

add_executable(GeneticSim GeneticSim.cpp )
target_include_directories(GeneticSim PUBLIC ..)
target_link_libraries(GeneticSim PUBLIC GeneticSimulator)

add_executable(SimTest Simulation.test.cpp)
target_include_directories(SimTest PUBLIC ..)
target_link_libraries(SimTest PUBLIC GeneticSimulator)