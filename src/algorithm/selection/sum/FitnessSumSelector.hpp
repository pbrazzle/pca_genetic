#ifndef FITNESS_SUM_SELECTOR
#define FITNESS_SUM_SELECTOR

#include "algorithm/selection/ParentSelector.hpp"
#include <memory>

namespace PCAGenetic
{
	class FitnessSumSelector : public ParentSelector
	{
		public:
			FitnessSumSelector();

			std::unique_ptr<ParentSelector> clone() const;

			std::pair<ModelHandle, ModelHandle> selectParents(const std::vector<ModelHandle>&, const std::vector<double>&);

			JSONObject toJSON() const;
	};
}

#endif
