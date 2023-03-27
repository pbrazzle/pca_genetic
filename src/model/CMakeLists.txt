set(MODEL_SOURCES
	GeneticModel.cpp
	convolution/ConvolutionModel.cpp
	downsample/DownSamplingModel.cpp
	input/ModelInputDataVector.cpp
	#interconnect/InterconnectedModel.cpp
	linear/LinearGeneticModel.cpp
	neural/NeuralModel.cpp
	output/ModelOutputDataVector.cpp
	regression/LogisticRegressionModel.cpp)
	
add_library(GeneticModels ${MODEL_SOURCES})
target_link_libraries(GeneticModels PUBLIC GeneticJSON)