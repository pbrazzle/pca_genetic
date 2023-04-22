#ifndef INTERCONNECTED_GENETIC_MODEL
#define INTERCONNECTED_GENETIC_MODEL

#include "GeneticModel.hpp"
#include <memory>

//TODO: All models should be moved to the GeneticModels namespace
using GeneticModels::GeneticModel;
using GeneticModels::ModelOutputData;
using GeneticModels::ModelInputData;

namespace GeneticModels
{
	//An InterconnectedGeneticModel can form a network of other GeneticModels
	//Each layer of the network contains one or more GeneticModels
	//The first layer processes the input data, and subsequent layers process the output of the previous one
	//If a layer has multiple models, the input data will be split in the order of the vector representation of the data
	//The split will match the datalength of each model in the layer
	
	//TODO implement this
	class InterconnectedGeneticModel : public GeneticModel
	{
	private:
		typedef std::unique_ptr<GeneticModel> ModelPtr;
		typedef std::vector<ModelPtr> ModelLayer;
		typedef std::vector<ModelLayer> LayerArray;

		void checkDataSizes();

		LayerArray layers;
		public:
			InterconnectedGeneticModel() = default;
			InterconnectedGeneticModel(LayerArray&);

			std::unique_ptr<GeneticModel> clone() const;

			std::unique_ptr<ModelOutputData> evaluate(ModelInputData&);

			std::vector<double> getParameters() const;
			void setParameters(std::vector<double>);
			int getInputDataLength() const override;
			int getOutputDataLength() const override;
		JSONObject toJSON() const override;
		void fromJSON(const JSONObject& obj) override;
	};
}

#endif
