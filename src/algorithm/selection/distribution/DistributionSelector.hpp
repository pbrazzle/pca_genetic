#ifndef DISTRIBUTION_SELECTOR
#define DISTRIBUTION_SELECTOR

#include "algorithm/selection/ParentSelector.hpp"

#include <memory>
#include <functional>

namespace PCAGenetic
{
	class DistributionSelector : public ParentSelector
	{
		private:
			//The distribution function takes 2 arguments:
			//The ranking of the model, and the total number of models
			std::function<double(int, int)> distribution;
		
			size_t makeSelection(const std::vector<ModelHandle>&) const;
		
		public:
			//The default distribution is a geometric distribution with p=0.5
			DistributionSelector();

			DistributionSelector(std::function<double(int, int)>);
		
			std::unique_ptr<ParentSelector> clone() const;

			//Returns a std::pair of GeneticModels to be combined as parents
			std::pair<ModelHandle, ModelHandle> selectParents(const std::vector<ModelHandle>&, const std::vector<double>&);

			JSONObject toJSON() const;
	};
}

#endif