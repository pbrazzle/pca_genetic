#ifndef JSON_OBJECT
#define JSON_OBJECT

#include <string>
#include <map>

namespace GeneticJSON
{
	//TODO add support for arrays
	class JSONObject
	{
		private:
			std::string data;
			std::map<std::string, JSONObject> subObjects;
			
		public:
		
			JSONObject();
			
			//Constructs a JSONObject from the provided string
			JSONObject(std::string value);
			
			/**Writing**/
			
			void addObject(std::string key, JSONObject obj);
			
			void addInt(std::string key, int val);
			
			void addFloat(std::string key, double val);
			
			void addBool(std::string key, bool val);
			
			void addString(std::string key, std::string val);
			
			//Converts object to JSON string
			std::string asJSON() const;
		
			/**Reading**/
			
			//Get value from object key
			JSONObject operator[](std::string key) const;
			
			//Converts object to int value
			int asInt() const;
			
			//Converts object to floating point value
			double asFloat() const;
			
			//Converts object to boolean value
			bool asBool() const;
			
			//Converts object to string value
			std::string asString() const;
	};
}

#endif