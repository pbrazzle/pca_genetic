#ifndef PARENT_COMBINER
#define PARENT_COMBINER

#include "json/JSONSerializable.hpp"

#include <memory>
#include <vector>

namespace PCAGenetic
{
	using namespace GeneticJSON;
	
	class ParentCombiner : public JSONSerializable
	{
		public:
			virtual ~ParentCombiner() { }

			virtual std::unique_ptr<ParentCombiner> clone() const = 0;

			//Combines parameters from 2 parent models to create a child model
			//Does not perform mutations
			virtual std::vector<double> combineParameters(const std::vector<double>& p1, const std::vector<double>& p2) = 0;
	};
}

#endif
