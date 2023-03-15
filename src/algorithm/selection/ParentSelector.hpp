#ifndef PARENT_SELECTOR
#define PARENT_SELECTOR

#include "model/GeneticModel.hpp"
#include "GeneticTypes.hpp"
#include "json/JSONSerializable.hpp"

#include <memory>

namespace PCAGenetic
{
	using namespace GeneticJSON;
	
	class ParentSelector : public JSONSerializable
	{
		public:
			virtual ~ParentSelector() { }
	
			virtual std::unique_ptr<ParentSelector> clone() const = 0;

			//Returns a std::pair of GeneticModels to be combined as parents
			virtual parentPair selectParents(const modelVector&, const std::vector<double>&) = 0;
	};
}

#endif
