#ifndef JSON_OBJECT
#define JSON_OBJECT

#include <string>
#include <vector>
#include <map>

namespace GeneticJSON
{
	class JSONObject
	{
		private:
			std::string data;
			std::map<std::string, JSONObject> subObjects;
			
		public:
		
			JSONObject();
			
			//Constructs a JSON string or object
			//If the provided string can be parsed as a JSON object, the JSONObject will be constructed as such
			JSONObject(std::string value);
			
			//Constructs a JSON int
			JSONObject(int value);
			
			//Constructs a JSON bool
			JSONObject(bool value);
			
			//Constructs a JSON double
			JSONObject(double value);
			
			//Constructs a JSON array
			JSONObject(const char* value);
			JSONObject(std::vector<JSONObject> value);
			
			/**Writing**/
			
			void addObject(std::string key, JSONObject obj);
			
			void addInt(std::string key, int val);
			
			void addFloat(std::string key, double val);
			
			void addBool(std::string key, bool val);
			
			void addString(std::string key, std::string val);
			
			void addArray(std::string key, std::vector<JSONObject> arr);
			
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
			
			//Converts object to vector of JSONObjects
			std::vector<JSONObject> asArray() const;
	};
}

#endif