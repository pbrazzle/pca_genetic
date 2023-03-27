#ifndef GENETIC_MODEL 
#define GENETIC_MODEL

#include <memory>
#include <vector>

#include "model/input/ModelInputData.hpp"
#include "model/output/ModelOutputData.hpp"
#include "json/JSONSerializable.hpp"
#include "algorithm/combination/ParentCombiner.hpp"

namespace GeneticModels
{
	using namespace GeneticJSON;
	using namespace PCAGenetic;
	
	class GeneticModel : public JSONSerializable
	{
		public:
			virtual ~GeneticModel() = default;

			virtual std::unique_ptr<GeneticModel> clone() const = 0;
			
			//Combines this model with the given parameter and returns the result
			virtual std::unique_ptr<GeneticModel> combine(const GeneticModel&, ParentCombiner&);
			
			//Creates a copy of this model and adds a random offset to each parameter
			//Params: Maximum offset
			virtual std::unique_ptr<GeneticModel> copyWithOffset(double) const;
			
			virtual std::unique_ptr<ModelOutputData> evaluate(ModelInputData&) = 0;
			
			//Mutate all parameters
			//Params: Mutation chance, mutation size
			virtual void mutate(double, double);

			//TODO: Using iterators here would make more sense			
			virtual std::vector<double> getParameters() const = 0;
			virtual void setParameters(std::vector<double>) = 0;
	};
}

#endif
