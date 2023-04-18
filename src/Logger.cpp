#include "Logger.hpp"

#include <fstream>

namespace GeneticLogger
{
	std::ofstream logFile;
	
	namespace
	{
		void openLog()
		{
			logFile.open("pca_genetic.log");
			logFile << "Initialized Log...\n";
		}
		
		std::string levelToString(Level level)
		{
			switch (level)
			{
				case Level::Fatal:
					return "FATAL: ";
				case Level::Error:
					return "ERROR: ";
				case Level::Warning:
					return "WARNING: ";
				case Level::Info:
					return "INFO: ";
				case Level::Debug:
					return "DEBUG: ";
			}
			return "";
		}
	}
	
	void log(std::string message, Level level)
	{
		if (!logFile.is_open()) openLog();
		logFile << levelToString(level) << message;
	}
};