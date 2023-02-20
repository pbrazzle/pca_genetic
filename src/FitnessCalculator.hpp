#ifndef FITNESS_CALCULATOR
#define FITNESS_CALCULATOR

#include <vector>

#include "GeneticTypes.hpp"

namespace PCAGenetic
{
	class FitnessCalculator
	{
		public:
			virtual ~FitnessCalculator() { }

			virtual std::vector<double> calculateFitnesses(const std::vector<trainingItem>&, const std::vector<std::unique_ptr<GeneticModel>>&) = 0;
	};
}

#endif
