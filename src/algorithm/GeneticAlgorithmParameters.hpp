#ifndef GENETIC_ALGORITHM_PARAMS
#define GENETIC_ALGORITHM_PARAMS

#include <memory>
#include <string>

#include "json/JSONSerializable.hpp"
#include "algorithm/fitness/FitnessCalculator.hpp"
#include "algorithm/combination/ParentCombiner.hpp"
#include "algorithm/selection/ParentSelector.hpp"

namespace PCAGenetic
{
	using GeneticJSON::JSONObject;
	
	class GeneticAlgorithmParameters : public GeneticJSON::JSONSerializable
	{
		private:
			std::string modelType, calcType, selectType, combType;
			
		public:
			std::unique_ptr<FitnessCalculator> fitnessCalc;
			std::unique_ptr<ParentSelector> parentSelect;
			std::unique_ptr<ParentCombiner> parentComb;
			std::unique_ptr<GeneticModel> modelTemplate;
			
			unsigned int generationSize;
			double mutationChance, mutationSize;
			double paramRange;
			double elitism;
			
			GeneticAlgorithmParameters();
			
			JSONObject toJSON() const;
			void fromJSON(const JSONObject& obj);
	};
}

#endif