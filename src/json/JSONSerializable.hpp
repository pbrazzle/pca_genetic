#ifndef JSON_SERIALIZABLE
#define JSON_SERIALIZABLE

#include "JSONObject.hpp"

namespace JSON_IO
{
	class JSONSerializable
	{
		public:
			virtual JSONObject toJSON() const { return JSONObject(); }
			virtual void fromJSON(const JSONObject& obj) { }
	};
}

#endif