#ifndef FITNESS_CALCULATOR
#define FITNESS_CALCULATOR

#include <memory>
#include <vector>

#include "GeneticTypes.hpp"
#include "json/JSONSerializable.hpp"

namespace PCAGenetic
{
	using namespace JSON_IO;
	
	class FitnessCalculator : public JSONSerializable
	{
		public:
			virtual ~FitnessCalculator() { }

			virtual std::unique_ptr<FitnessCalculator> clone() const = 0;

			virtual double calculateFitness(const trainingItem&, const ModelHandle&) const = 0;

			//virtual double calc(const std::vector<double>&, const std::vector<double>&) const;

			virtual JSONObject toJSON() const = 0;
	};
}

#endif
