#ifndef PARENT_SELECTOR
#define PARENT_SELECTOR

#include "GeneticModel.hpp"
#include "GeneticTypes.hpp"

namespace PCAGenetic
{
	class ParentSelector
	{
		public:
			virtual ~ParentSelector() { }
	
			//Returns a std::pair of GeneticModels to be combined as parents
			virtual parentPair selectParents(const modelVector&, const std::vector<double>&);
	};
}

#endif
