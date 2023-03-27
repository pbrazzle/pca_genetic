#ifndef PARENT_SELECTOR
#define PARENT_SELECTOR

#include "GeneticTypes.hpp"
#include "json/JSONSerializable.hpp"

#include <memory>

namespace PCAGenetic
{
	using namespace GeneticJSON;
	using namespace GeneticModels;
	
	class ParentSelector : public JSONSerializable
	{
		public:
			virtual ~ParentSelector() { }
	
			virtual std::unique_ptr<ParentSelector> clone() const = 0;

			//Returns a std::pair of GeneticModels to be combined as parents
			virtual std::pair<ModelHandle, ModelHandle> selectParents(const std::vector<ModelHandle>&, const std::vector<double>&) = 0;

			virtual JSONObject toJSON() const = 0;
	};
}

#endif
