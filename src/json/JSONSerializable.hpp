#ifndef JSON_SERIALIZABLE
#define JSON_SERIALIZABLE

#include "json/JSONObject.hpp"

namespace GeneticJSON
{
	class JSONSerializable
	{
		public:
			virtual JSONObject toJSON() const { return JSONObject(); }
			virtual void fromJSON(const JSONObject& obj) { }
	};
}

#endif