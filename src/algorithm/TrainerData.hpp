#ifndef TRAINER_DATA
#define TRAINER_DATA

#include "TrainerParameters.hpp"
#include "TrainerModels.hpp"
#include "model/GeneticModel.hpp"
#include "GeneticTypes.hpp"

namespace PCAGenetic
{
	class TrainerData
	{
		private:
			TrainerParameters params;
			TrainerModels models;
			
		public:
			TrainerData(const GeneticModel&, const std::vector<trainingItem>&, const TrainerParameters&);
	};
}

#endif