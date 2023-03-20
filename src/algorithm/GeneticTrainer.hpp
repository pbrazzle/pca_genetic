#ifndef GENETIC_TRAINER
#define GENETIC_TRAINER

#include "TrainerData.hpp"

namespace PCAGenetic
{
	class GeneticTrainer
	{
		private:
			TrainerData data;
			
		public:
			void train(const GeneticModel&, const std::vector<trainingItem>&, const TrainerParameters&);
			void continueTraining(const int&);
			/*
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
			*/
	};
}

#endif