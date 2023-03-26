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

namespace PCAGenetic
{
	using namespace GeneticModels;
	using namespace GeneticJSON;
	
	class GeneticAlgorithm : public JSONSerializable
	{
		private:
			std::unique_ptr<FitnessCalculator> fitnessCalc;
			std::unique_ptr<ParentSelector> parentSelect;
			std::unique_ptr<ParentCombiner> parentComb;

			std::vector<ModelHandle> models;
			std::vector<double> fitnesses;
			std::vector<trainingItem> trainingData;

			void runGeneration();
			void calculateFitnesses();
			
			int generationSize;
			double offsetSize;
			double mutationChance, mutationSize;
			double elitism;
			
			std::vector<double> avgFitnesses;
			std::vector<double> bestFitnesses;

			void copyStrategies(const GeneticAlgorithm& alg);
			void copyData(const GeneticAlgorithm& alg);
			void copySettings(const GeneticAlgorithm& alg);
			void copy(const GeneticAlgorithm& alg);

			void initializeGeneration(const GeneticModel& modelTemplate);

			std::vector<size_t> getSortedFitnessIndices();
			void reorderModels(std::vector<size_t> indices);
			void recordFitness();
			ModelHandle createChildModel();

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
