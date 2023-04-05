#ifndef DOWNSAMPLING_MODEL
#define DOWNSAMPLING_MODEL

#include "model/GeneticModel.hpp"

namespace GeneticModels
{
	//TODO implement this
	class DownSamplingModel : public GeneticModel
	{
		private:
			std::pair<int, int> pool_size;
			std::pair<int, int> image_size;

			std::vector<std::vector<double>> reorderByPools(const std::vector<double>&);
			std::vector<double> maxPool(const std::vector<std::vector<double>>&);
			std::vector<double> getPool(const std::vector<double>&, int);

		public:
			DownSamplingModel() = default;
			DownSamplingModel(int, int, int, int);
			DownSamplingModel(std::pair<int, int>, std::pair<int, int>);

			std::unique_ptr<GeneticModel> clone() const;
			
			std::unique_ptr<ModelOutputData> evaluate(ModelInputData&);
		
			std::vector<double> getParameters() const;
			void setParameters(std::vector<double>);
			int getInputDataLength() const override;
			int getOutputDataLength() const override;
	};
}

#endif