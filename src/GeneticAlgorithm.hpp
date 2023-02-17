#ifndef GENETICALGORITHM
#define GENETICALGORITHM

#include <memory>
#include <vector>

#include "ModelInputData.hpp"
#include "GeneticModel.hpp"

namespace PCAGenetic
{
	typedef std::pair<std::unique_ptr<ModelInputData>, std::unique_ptr<ModelOutputData>> trainingItem; 
	class GeneticAlgorithm
	{
		public:
			virtual ~GeneticAlgorithm() { }
			
			virtual void train(std::unique_ptr<GeneticModel>, std::vector<trainingItem>, int) = 0;
			virtual void continueTraining(int) = 0;
			
			virtual std::unique_ptr<GeneticModel> getBestModel() = 0;
	};
}

#endif
