#ifndef BEST_SELECTOR
#define BEST_SELECTOR

#include "algorithm/selection/ParentSelector.hpp"
#include <memory>

namespace PCAGenetic
{
	class BestFitnessSelector : public ParentSelector
	{
		public:
			std::unique_ptr<ParentSelector> clone() const;
			parentPair selectParents(const modelVector&, const std::vector<double>&);
	};
}

#endif
