#ifndef DISTANCE_CALCULATOR
#define DISTANCE_CALCULATOR

#include "algorithm/fitness/FitnessCalculator.hpp"

#include <memory>
#include <vector>

namespace PCAGenetic 
{
	class DistanceCalculator : public FitnessCalculator
	{	
		public:
			DistanceCalculator();

			std::unique_ptr<FitnessCalculator> clone() const;

			std::vector<double> calculateFitnesses(const std::vector<trainingItem>& trainingData, const std::vector<std::unique_ptr<GeneticModel>>& models);
	};
}

#endif
