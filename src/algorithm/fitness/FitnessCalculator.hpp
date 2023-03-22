#ifndef FITNESS_CALCULATOR
#define FITNESS_CALCULATOR

#include <memory>
#include <vector>
#include <xstddef>

#include "GeneticTypes.hpp"
#include "json/JSONSerializable.hpp"
#include "model/ModelHandle.hpp"

namespace PCAGenetic
{
	using namespace GeneticJSON;
	
	class FitnessCalculator : public JSONSerializable
	{
		public:
			virtual ~FitnessCalculator() { }

			virtual std::unique_ptr<FitnessCalculator> clone() const = 0;

			virtual std::vector<double> calculateFitnesses(const std::vector<trainingItem>&, const std::vector<std::unique_ptr<GeneticModel>>&) = 0;
			
			virtual std::vector<double> calculateFitnesses(const std::vector<trainingItem>&, const std::vector<ModelHandle>&) = 0;
	};
}

#endif
