#ifndef LOGGER
#define LOGGER

#include <string>

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