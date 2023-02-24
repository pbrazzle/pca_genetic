#ifndef GENETICALGORITHM
#define GENETICALGORITHM

#include <algorithm>
#include <memory>
#include <vector>

#include "model/ModelInputData.hpp"
#include "model/GeneticModel.hpp"
#include "GeneticTypes.hpp"
#include "algorithm/FitnessCalculator.hpp"
#include "algorithm/ParentSelector.hpp"
#include "algorithm/ParentCombiner.hpp"

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
			
			unsigned int generationSize;
			double mutationChance, mutationSize;
			double paramRange;
			double elitism;
			
			std::vector<double> mutateParams(const std::vector<double>&);
			
			std::vector<double> avgFitnesses;
			std::vector<double> bestFitnesses;

		public:
			GeneticAlgorithm();
			GeneticAlgorithm(std::unique_ptr<FitnessCalculator>, std::unique_ptr<ParentSelector>, std::unique_ptr<ParentCombiner>);
			GeneticAlgorithm(GeneticAlgorithm& alg);

			virtual ~GeneticAlgorithm() { }
		
			GeneticAlgorithm& operator=(const GeneticAlgorithm& other);

			virtual void train(const GeneticModel&, std::vector<trainingItem>&, int);
			virtual void continueTraining(int);
			
			virtual std::unique_ptr<GeneticModel> getBestModel();
			
			void setGenerationSize(const int&);
			void setMutationChance(const double&);
			void setMutationSize(const double&);
			void setParamRange(const double&);
			void setEilitism(const double&);
			
			std::vector<double> getAvgFitnesses() const;
			std::vector<double> getBestFitnesses() const;
	};
}

#endif
