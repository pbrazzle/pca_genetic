set(SIMULATOR_SOURCES
	Simulation.cpp 
	../Logger.cpp)
	
add_library(GeneticSimulator STATIC ${SIMULATOR_SOURCES})
target_include_directories(GeneticSimulator PUBLIC ..)
target_link_libraries(GeneticSimulator PUBLIC GeneticAlgorithms)

add_executable(GeneticSim GeneticSim.cpp )
target_include_directories(GeneticSim PUBLIC ..)
target_link_libraries(GeneticSim PUBLIC GeneticSimulator)

set(TEST_SOURCES
	Simulation.test.cpp)
	
foreach(TEST ${TEST_SOURCES})
	get_filename_component(TEST_NAME ${TEST} NAME_WE)
	add_executable(${TEST_NAME} ${TEST})
	target_link_libraries(${TEST_NAME} PUBLIC GeneticSimulator PRIVATE Catch2::Catch2WithMain)
	catch_discover_tests(${TEST_NAME})
endforeach()