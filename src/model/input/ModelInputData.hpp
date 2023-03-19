#ifndef MODELINPUTDATA
#define MODELINPUTDATA

#include <memory>
#include <vector>

#include "json/JSONSerializable.hpp"

namespace GeneticModels
{	
	using namespace GeneticJSON;

	class ModelInputData : public JSONSerializable
	{
		public:
			virtual ~ModelInputData() { }
			
			virtual std::unique_ptr<ModelInputData> clone() const = 0;
			
			//Returns a vector representation of the input data
			virtual std::vector<double> getData() = 0;
	};
}

#endif
