set(JSON_SOURCES
	JSONObject.cpp
	JSONFile.cpp)
	
add_library(GeneticJSON STATIC ${JSON_SOURCES})
target_include_directories(GeneticJSON PUBLIC ..)