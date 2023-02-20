#ifndef BASIC_GENETIC_ALGORITHM
#define BASIC_GENETIC_ALGORITHM

#include <vector>

#include "GeneticAlgorithm.hpp"

namespace PCAGenetic
{
	class BasicGeneticAlgorithm
	{
		private:
			std::vector<std::unique_ptr<GeneticModel>> models;
			std::vector<double> fitnesses;
			std::vector<trainingItem> trainingData;

			void calculateFitnesses();
			std::vector<double> combineParameters(std::vector<double>, std::vector<double>);
			std::pair<std::unique_ptr<GeneticModel>, std::unique_ptr<GeneticModel>> selectParents();
			void runGeneration();	
			
		public:
			BasicGeneticAlgorithm();

			void train(const GeneticModel&, std::vector<trainingItem>, int);
			void continueTraining(int);

			std::unique_ptr<GeneticModel> getBestModel();
	};
}

#endif
