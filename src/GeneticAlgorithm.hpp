#ifndef GENETICALGORITHM
#define GENETICALGORITHM

#include <memory>
#include <vector>

#include "ModelInputData.hpp"
#include "GeneticModel.hpp"
#include "GeneticTypes.hpp"
#include "FitnessCalculator.hpp"
#include "ParentSelector.hpp"
#include "ParentCombiner.hpp"

namespace PCAGenetic
{
	//GeneticAlgorithm can be composed of several substrategies
	//Fitness calculation
	//Parent selection
	//Parent combination
	//If we compose these strategies, there will be no need for GeneticAlgorithm to be an interface at all
	class GeneticAlgorithm
	{
		private:
			std::unique_ptr<FitnessCalculator> fitnessCalc;
			std::unique_ptr<ParentSelector> parentSelect;
			std::unique_ptr<ParentCombiner> parentComb;

			modelVector models;
			std::vector<double> fitnesses;
			std::vector<trainingItem> trainingData;

			void runGeneration();
			void calculateFitnesses();

		public:
			GeneticAlgorithm(std::unique_ptr<FitnessCalculator>, std::unique_ptr<ParentSelector>, std::unique_ptr<ParentCombiner>);
			virtual ~GeneticAlgorithm() { }
			
			virtual void train(const GeneticModel&, std::vector<trainingItem>, int) = 0;
			virtual void continueTraining(int) = 0;
			
			virtual std::unique_ptr<GeneticModel> getBestModel() = 0;
	};
}

#endif
