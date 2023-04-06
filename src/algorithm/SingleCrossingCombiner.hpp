#ifndef SINGLE_CROSSING_COMBINER
#define SINGLE_CROSSING_COMBINER

#include "algorithm/ParentCombiner.hpp"
#include <memory>
#include <vector>

namespace PCAGenetic
{
	using namespace JSON_IO;

	class SingleCrossingCombiner : public ParentCombiner
	{
		public:
			SingleCrossingCombiner();

			std::unique_ptr<ParentCombiner> clone() const;

			std::vector<double> combineParameters(const std::vector<double>& p1, const std::vector<double>& p2);

			JSONObject toJSON() const;
	};
}

#endif
