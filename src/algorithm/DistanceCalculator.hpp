#ifndef DISTANCE_CALCULATOR
#define DISTANCE_CALCULATOR

#include "algorithm/FitnessCalculator.hpp"

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
			
			std::vector<double> calculateFitnesses(const std::vector<trainingItem>&, const std::vector<ModelHandle>&);

			double calculateFitness(const trainingItem&, const ModelHandle&) const override;

			JSONObject toJSON() const;
	};
}

#endif
