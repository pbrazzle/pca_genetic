#ifndef MODEL_HANDLE
#define MODEL_HANDLE

#include "GeneticModel.hpp"

#include <memory>

namespace GeneticModels
{
	class ModelHandle
	{
		private:
			std::unique_ptr<GeneticModel> model;
			
		public:
			ModelHandle(GeneticModel*);
			ModelHandle(const ModelHandle&);
			
			ModelHandle& operator=(const ModelHandle&);
			
			GeneticModel* operator->();
	};
}

#endif