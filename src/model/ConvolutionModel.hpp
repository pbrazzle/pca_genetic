#ifndef CONVOLUTION_MODEL
#define CONVOLUTION_MODEL

#include "GeneticModel.hpp"

namespace GeneticModels
{
	//TODO implement this
	class ConvolutionModel : public GeneticModel
	{
	private:
		int image_width, image_height;
		int kernel_width, kernel_height;
		std::vector<double> kernel_weights;

		public:
			ConvolutionModel() = default;
			ConvolutionModel(int, int, int, int);
			ConvolutionModel(int, int, int, int, std::vector<double>);

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