#ifndef LOGGER
#define LOGGER

#include <string>

//TODO I need to add more log messages in general - Add more TODOs to add log messages in each class
namespace GeneticLogger
{
	enum class Level
	{
		Fatal,
		Error,
		Warning,
		Info,
		Debug
	};
	
	void log(std::string message, Level level);
}

#endif