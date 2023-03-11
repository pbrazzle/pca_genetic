#ifndef JSON_OBJECT
#define JSON_OBJECT

#include <string>

namespace GeneticJSON
{
	class JSONObject
	{
		public:
			
			//Constructs a JSONObject from the provided string
			JSONObject(std::string value);
			
			/**Writing**/
			
			//Converts object to JSON string
			std::string asJSON() const;
		
			/**Reading**/
			
			//Get value from object key
			JSONObject operator[](std::string key) const;
			
			//Converts object to int value
			int asInt() const;
			
			//Converts object to floating point value
			long asFloat() const;
			
			//Converts object to boolean value
			bool asBool() const;
			
			//Converts object to string value
			std::string asString const;
	};
}

#endif