set(MODEL_SOURCES
	GeneticModel.cpp
	ConvolutionModel.cpp
	DownSamplingModel.cpp
	ModelInputDataVector.cpp
	InterconnectedGeneticModel.cpp
	"LinearGeneticModel.cpp"
	NeuralModel.cpp
	"ModelOutputDataVector.cpp"
	GeneticModelFactory.cpp
	ModelInputImage.cpp)
	
add_library(GeneticModels ${MODEL_SOURCES})
target_link_libraries(GeneticModels PUBLIC GeneticJSON)
target_include_directories(GeneticModels PUBLIC model ${CMAKE_SRC_DIR}/../external)

set(TEST_SOURCES
	LinearGeneticModel.test.cpp
	ConvolutionModel.test.cpp
	DownSamplingModel.test.cpp
	NeuralModel.test.cpp
	ModelInputDataVector.test.cpp
	ModelOutputDataVector.test.cpp
	InterconnectedGeneticModel.test.cpp)
	
foreach(TEST ${TEST_SOURCES})
	get_filename_component(TEST_NAME ${TEST} NAME_WE)
	add_executable(${TEST_NAME} ${TEST})
	target_link_libraries(${TEST_NAME} PUBLIC GeneticModels PRIVATE Catch2::Catch2WithMain)
	catch_discover_tests(${TEST_NAME})
endforeach()