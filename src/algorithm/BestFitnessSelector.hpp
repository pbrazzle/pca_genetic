#ifndef BEST_SELECTOR
#define BEST_SELECTOR

#include "algorithm/ParentSelector.hpp"
#include <memory>

namespace PCAGenetic
{
	class BestFitnessSelector : public ParentSelector
	{
		public:
			std::unique_ptr<ParentSelector> clone() const;

			std::pair<ModelHandle, ModelHandle> selectParents(const std::vector<ModelHandle>&, const std::vector<double>&);

			JSONObject toJSON() const;
	};
}

#endif
