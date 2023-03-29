#include "JSONFile.hpp"

#include <sstream>

using namespace JSON_IO;

JSONFileReader::JSONFileReader(std::string filename) : inFile(filename) { }
JSONObject JSONFileReader::read() 
{
	std::stringstream ss;
	ss << inFile.rdbuf();
	return JSONObject(ss.str()); 
}

JSONFileWriter::JSONFileWriter(std::string filename) : outFile(filename) { }
void JSONFileWriter::write(const JSONObject& obj) { outFile << obj.asJSON(); }