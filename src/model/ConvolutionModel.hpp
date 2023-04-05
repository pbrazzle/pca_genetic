#ifndef CONVOLUTION_MODEL
#define CONVOLUTION_MODEL

#include "model/GeneticModel.hpp"

namespace GeneticModels
{
	//TODO implement this
	class ConvolutionModel : public GeneticModel
	{
		public:
			std::unique_ptr<GeneticModel> clone() const;
			
			std::unique_ptr<ModelOutputData> evaluate(ModelInputData&);
		
			std::vector<double> getParameters() const;
			void setParameters(std::vector<double>);

			int getInputDataLength() const;
			int getOutputDataLength() const;
			JSONObject toJSON() const override;
			void fromJSON(const JSONObject& obj) override;
	};
}

#endif