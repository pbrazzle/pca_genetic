#ifndef RANDOM_COMBINER
#define RANDOM_COMBINER

#include "algorithm/ParentCombiner.hpp"
#include <memory>

namespace PCAGenetic
{
	using namespace JSON_IO;
	
	class RandomCrossingCombiner : public ParentCombiner
	{
		private:
			double crossingChance;

		public:
			RandomCrossingCombiner();
			RandomCrossingCombiner(double);

			std::unique_ptr<ParentCombiner> clone() const;

			std::vector<double> combineParameters(const std::vector<double>& p1, const std::vector<double>& p2);

			JSONObject toJSON() const;
	};
}

#endif
