set(MODEL_SOURCES
	GeneticModel.cpp
	ConvolutionModel.cpp
	DownSamplingModel.cpp
	ModelInputDataVector.cpp
	#interconnect/InterconnectedModel.cpp
	"LinearGeneticModel.cpp"
	NeuralModel.cpp
	"ModelOutputDataVector.cpp"
	"LogisticRegressionModel.cpp")
	
add_library(GeneticModels ${MODEL_SOURCES})
target_link_libraries(GeneticModels PUBLIC GeneticJSON)
target_include_directories(GeneticModels PUBLIC model)