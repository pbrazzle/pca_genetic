#ifndef JSON_SERIALIZABLE
#define JSON_SERIALIZABLE

#include "json/JSONObject.hpp"

namespace GeneticJSON
{
	class JSONSerializable
	{
		public:
			virtual JSONObject toJSON() const = 0;
			virtual void fromJSON(const JSONObject& obj) = 0;
	};
}

#endif