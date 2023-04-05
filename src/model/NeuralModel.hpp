#ifndef NEURAL_MODEL
#define NEURAL_MODEL

#include "model/GeneticModel.hpp"

#include <vector>

namespace GeneticModels
{
	class NeuralModel : public GeneticModel
	{
		private:
			std::vector<unsigned int> layerSizes;
			std::vector<double> weights;

		public:
			NeuralModel() = default;
			NeuralModel(std::vector<unsigned int>);
			NeuralModel(std::vector<unsigned int>, std::vector<double>);

			void setLayerSizes(std::vector<unsigned int>);

			std::unique_ptr<GeneticModel> clone() const;
			
			std::unique_ptr<ModelOutputData> evaluate(ModelInputData&);
		
			std::vector<double> getParameters() const;
			void setParameters(std::vector<double>);

			int getInputDataLength() const override;
			int getOutputDataLength() const override;
	};
}

#endif