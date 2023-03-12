#ifndef NEURAL_MODEL
#define NEURAL_MODEL

#include "model/GeneticModel.hpp"

namespace PCAGenetic
{
	//TODO implement this
	class NeuralModel : public GeneticModel
	{
		public:
			std::unique_ptr<GeneticModel> clone() const;
			
			std::unique_ptr<ModelOutputData> evaluate(ModelInputData&);
		
			std::vector<double> getParameters() const;
			void setParameters(std::vector<double>);
	};
}

#endif