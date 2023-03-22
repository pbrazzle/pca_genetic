#ifndef GENETICALGORITHM
#define GENETICALGORITHM

#include <algorithm>
#include <memory>
#include <vector>

#include "model/input/ModelInputData.hpp"
#include "model/GeneticModel.hpp"
#include "GeneticTypes.hpp"
#include "algorithm/fitness/FitnessCalculator.hpp"
#include "algorithm/selection/ParentSelector.hpp"
#include "algorithm/combination/ParentCombiner.hpp"
#include "json/JSONSerializable.hpp"

#include "GenerationCreator.hpp"
#include "Evaluator.hpp"
#include "Selector.hpp"
#include "Combiner.hpp"
#include "Mutator.hpp"

namespace PCAGenetic
{
	using namespace GeneticModels;
	using namespace GeneticJSON;
	
	class GeneticAlgorithm : public JSONSerializable
	{
		private:
			GenerationCreator creator;
			Evaluator evaluator;
			Selector selector;
			Combiner combiner;
			Mutator mutator;
		
			std::unique_ptr<FitnessCalculator> fitnessCalc;
			std::unique_ptr<ParentSelector> parentSelect;
			std::unique_ptr<ParentCombiner> parentComb;

			std::vector<ModelHandle> models;
			std::vector<double> fitnesses;
			std::vector<trainingItem> trainingData;

			void runGeneration();
			void calculateFitnesses();
			
			double mutationChance, mutationSize;
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
