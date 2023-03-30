set(MODEL_SOURCES
	GeneticModel.cpp
	ConvolutionModel.cpp
	DownSamplingModel.cpp
	ModelInputDataVector.cpp
	#interconnect/InterconnectedModel.cpp
	"LinearGeneticModel.cpp"
	NeuralModel.cpp
	"ModelOutputDataVector.cpp")
	
add_library(GeneticModels ${MODEL_SOURCES})
target_link_libraries(GeneticModels PUBLIC GeneticJSON)
target_include_directories(GeneticModels PUBLIC model)

set(TEST_SOURCES
	LinearGeneticModel.test.cpp
	ConvolutionModel.test.cpp
	DownSamplingModel.test.cpp
	NeuralModel.test.cpp)
	
foreach(TEST ${TEST_SOURCES})
	get_filename_component(TEST_NAME ${TEST} NAME_WE)
	add_executable(${TEST_NAME} ${TEST})
	target_link_libraries(${TEST_NAME} PUBLIC GeneticModels PRIVATE Catch2::Catch2WithMain)
	catch_discover_tests(${TEST_NAME})
endforeach()