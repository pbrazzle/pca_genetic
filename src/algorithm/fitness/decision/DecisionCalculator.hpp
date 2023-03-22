#ifndef DECISION_CALCULATOR
#define DECISION_CALCULATOR

#include "algorithm/fitness/FitnessCalculator.hpp"

namespace PCAGenetic
{
	class DecisionCalculator : public FitnessCalculator
	{
		public:
			DecisionCalculator();
		
			std::unique_ptr<FitnessCalculator> clone() const;

			std::vector<double> calculateFitnesses(const std::vector<trainingItem>&, const std::vector<std::unique_ptr<GeneticModel>>&);
			
			std::vector<double> calculateFitnesses(const std::vector<trainingItem>&, const std::vector<ModelHandle>&);
	};
}

#endif