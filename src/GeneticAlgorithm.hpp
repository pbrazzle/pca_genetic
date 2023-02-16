#ifndef GENETICALGORITHM
#define GENETICALGORITHM

namespace PCAGenetic
{
	class GeneticAlgorithm
	{
		typedef std::pair<std::unique_ptr<ModelInputData>, std::unique_ptr<ModelOutputData>> trainingItem;
		
		public:
			virtual ~GeneticAlgorithm() = 0;
			
			virtual void train(std::unique_ptr<GeneticModel>, std::vector<trainingItem>, int) = 0;
			virtual void continueTraining(int) = 0;
			
			virtual std::unique_ptr<GeneticModel> getBestModel() = 0;
	};
}

#endif