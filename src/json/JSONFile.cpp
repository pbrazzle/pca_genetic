#include "JSONFile.hpp"

#include <sstream>
#include <filesystem>
#include <iostream>

using namespace JSON_IO;

JSONFileReader::JSONFileReader(std::string filename)
{
	inFile.open(filename);
}

JSONObject JSONFileReader::read() 
{
	std::stringstream ss;
	ss << inFile.rdbuf();
	auto contents = ss.str();

	return JSONObject(contents); 
}

JSONFileWriter::JSONFileWriter(std::string filename) : outFile(filename) { }
void JSONFileWriter::write(const JSONObject& obj) { outFile << obj.asJSON(); }