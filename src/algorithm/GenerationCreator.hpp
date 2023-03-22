#ifndef GENERATION_CREATOR
#define GENERATION_CREATOR

#include "model/ModelHandle.hpp"

#include <vector>

namespace PCAGenetic
{
	using namespace GeneticModels;
	
	class GenerationCreator
	{
		private:
			double offsetSize;
			int generationSize;
			
		public:
			GenerationCreator() = default;
			GenerationCreator(double, int);
			
			std::vector<ModelHandle> create(const GeneticModel&);
			
			void setOffsetSize(double);
			void setGenerationSize(int);
	};
}

#endif