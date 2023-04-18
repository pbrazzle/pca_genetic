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
	
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
	
add_library(GeneticModels ${MODEL_SOURCES})
add_dependencies(GeneticModels libjpeg-turbo)

if(UNIX)
target_link_libraries(GeneticModels PUBLIC GeneticJSON ${JPEG_LIBNAME} X11 PRIVATE Threads::Threads)
else()
target_link_libraries(GeneticModels PUBLIC GeneticJSON ${JPEG_LIBNAME} PRIVATE Threads::Threads)
endif(UNIX)

target_include_directories(GeneticModels PUBLIC ${CMAKE_SOURCE_DIR}/src model ${CMAKE_SOURCE_DIR}/external ${CMAKE_BINARY_DIR}/libjpeg-turbo/include)

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