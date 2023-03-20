#include "TrainerData.hpp"

using namespace PCAGenetic;
using namespace GeneticModels;

TrainerData::TrainerData(const GeneticModel& templateModel, const std::vector<trainingItem>&, const TrainerParameters& p)
{
	params = p;
}