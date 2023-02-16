#ifndef GENETIC_MODEL 
#define GENETIC_MODEL

#include <memory>
#include <vector>

#include "ModelInputData.hpp"
#include "ModelOutputData.hpp"
#include "ModelParameters.hpp"

namespace PCAGenetic
{
	class GeneticModel
	{
		public:
			virtual ~GeneticModel() = 0;
			
			virtual std::unique_ptr<ModelOutputData> evaluate(ModelInputData&) = 0;
			
			virtual std::unique_ptr<ModelParameters> getParameters() const = 0;
			virtual void setParameters(ModelParameters&) = 0;
	};
}

#endif