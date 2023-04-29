#ifndef GENETICALGORITHM
#define GENETICALGORITHM

#include <algorithm>
#include <memory>
#include <vector>

#include "model/ModelInputData.hpp"
#include "model/GeneticModel.hpp"
#include "GeneticTypes.hpp"
#include "Population.hpp"
#include "algorithm/FitnessCalculator.hpp"
#include "algorithm/ParentSelector.hpp"
#include "algorithm/ParentCombiner.hpp"
#include "json/JSONSerializable.hpp"

namespace PCAGenetic
{
	using namespace GeneticModels;
	using namespace JSON_IO;
	
	class GeneticAlgorithm : public JSONSerializable
	{
		private:
			static unsigned int numThreads;

			void readThreadFile();

			std::unique_ptr<FitnessCalculator> fitnessCalc;
			std::unique_ptr<ParentSelector> parentSelect;
			std::unique_ptr<ParentCombiner> parentComb;

			Population population;
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
			GeneticAlgorithm(const GeneticAlgorithm& alg);
		
			GeneticAlgorithm& operator=(const GeneticAlgorithm& other);

			void train(const GeneticModel&, std::vector<trainingItem>&, int);
			void continueTraining(int);
			
			std::unique_ptr<GeneticModel> getBestModel();
			
			void setGenerationSize(const int&);
			void setMutationChance(const double&);
			void setMutationSize(const double&);
			void setParamRange(const double&);
			void setEilitism(const double&);
			
			std::vector<double> getAvgFitnesses() const;
			std::vector<double> getBestFitnesses() const;

			JSONObject toJSON() const;
			void fromJSON(const JSONObject& obj);
	};
}

#endif
