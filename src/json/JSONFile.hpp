#ifndef JSONFILE
#define JSONFILE

#include <fstream>

#include "json/JSONObject.hpp"

namespace JSON_IO
{
	class JSONFileReader
	{
		private:
			std::ifstream inFile;
			
		public:
			JSONFileReader(std::string filename);
			JSONObject read();
	};
	
	class JSONFileWriter
	{
		private:
			std::ofstream outFile;
			
		public:
			JSONFileWriter(std::string filename);
			void write(const JSONObject& obj);
	};
}

#endif