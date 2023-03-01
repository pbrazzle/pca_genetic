#ifndef GENETIC_MODEL 
#define GENETIC_MODEL

#include <memory>
#include <vector>

#include "ModelInputData.hpp"
#include "ModelOutputData.hpp"

namespace PCAGenetic
{
	class GeneticModel
	{
		public:
			virtual ~GeneticModel() { }

			virtual std::unique_ptr<GeneticModel> clone() const = 0;
			
			virtual std::unique_ptr<ModelOutputData> evaluate(ModelInputData&) = 0;

			//TODO: Using iterators here would make more sense			
			virtual std::vector<double> getParameters() const = 0;
			virtual void setParameters(std::vector<double>) = 0;
	};
}

#endif
