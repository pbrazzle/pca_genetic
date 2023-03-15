#ifndef GENETIC_MODEL 
#define GENETIC_MODEL

#include <memory>
#include <vector>

#include "model/input/ModelInputData.hpp"
#include "model/output/ModelOutputData.hpp"

namespace GeneticModels
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
