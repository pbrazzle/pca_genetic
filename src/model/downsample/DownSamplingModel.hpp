#ifndef DOWNSAMPLING_MODEL
#define DOWNSAMPLING_MODEL

#include "model/GeneticModel.hpp"

namespace GeneticModels
{
	//TODO implement this
	class DownSamplingModel : public GeneticModel
	{
		public:
			std::unique_ptr<GeneticModel> clone() const;
			
			std::unique_ptr<ModelOutputData> evaluate(ModelInputData&);
		
			std::vector<double> getParameters() const;
			void setParameters(std::vector<double>);
	};
}

#endif