#ifndef GENERATION
#define GENERATION

#include "FitnessCalculator.hpp"
#include "FitnessScores.hpp"
#include "ParentSelector.hpp"
#include "Population.hpp"

namespace PCAGenetic
{
	class Generation
	{
	private:
		FitnessScores scores;
		Population population;

	public:
		Generation() = default;
		Generation(const int& generationSize, const double& offsetSize, const GeneticModel& modelTemplate);

		//Scores each model in the population and sorts them in ascending order
		void score(const std::vector<trainingItem>& trainingData, const FitnessCalculator& fitCalc, const int& numThreads);

		//Advances the population to the next generation
		void advance(const double& elitism, ParentSelector& parentSelect, ParentCombiner& parentComb, const int& numThreads, const double& mutationChance, const double& mutationSize);

		double bestScore() const;
		double avgScore() const;

		const GeneticModel& getBestModel() const;
	};
}

#endif
