#ifndef INTERCONNECTED_GENETIC_MODEL
#define INTERCONNECTED_GENETIC_MODEL

#include "model/GeneticModel.hpp"
#include <memory>

//TODO: All models should be moved to the GeneticModels namespace
using PCAGenetic::GeneticModel;
using PCAGenetic::ModelOutputData;
using PCAGenetic::ModelInputData;

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
		public:
			std::unique_ptr<GeneticModel> clone() const;

			std::unique_ptr<ModelOutputData> evaluate(ModelInputData&);

			std::vector<double> getParameters() const;
			void setParameters(std::vector<double>);
	};
}

#endif
